
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include "borrowing.h"
#include "AVL_Tree.h"
#include "Data.h"
#include "hash.h"
#include "Book.h"
#include "Member.h"

// Biến toàn cục để lưu mã phiếu mượn hiện tại với giá trị mặc định
static char currentCode[6] = "000000";

//Hàm thêm phiếu mượn vào bảng băm bằng cách tạo nút và chèn vào AVL
void InputBorrowing(Borrowing *newBorrowing) {
    char *key = newBorrowing->Code; // Lấy Code làm khóa
    AVLNode *newNode = createNode(newBorrowing,key); // Tạo nút mới cho thành viên
    HashTableBorrowing[hash(key)] = insertAVL(HashTableBorrowing[hash(key)], newNode, key, compareString); // Thêm vào bảng băm
}

// Đọc từ file csv và thêm vào bảng băm
void ReadBorrowing(const char *filename) {
    FILE *file = fopen(filename, "r");
    //Kiểm tra nếu lỗi
    if (file == NULL) {
        printf("Khong the mo file! %s\n", filename);
        return;
    }
    char line[256];
    // Đọc dòng đầu tiên để lấy mã hiện tại
    if (fgets(line, sizeof(line), file)) {
        sscanf(line, "%5s", currentCode);
    }
    //Đọc các dòng dữ liệu của phiếu mượn
    while (fgets(line, sizeof(line), file)) {
        Borrowing *newBorrowing = (Borrowing*)malloc(sizeof(Borrowing));//Cấp phát động
        //Kiểm tra bộ nhớ
        if (newBorrowing == NULL) {
            printf("Khong du bo nho de cap phat!\n");
            fclose(file);
            return;
        }
        time_t startTime;
        // đọc các trường 
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%ld",
                   newBorrowing->Code, newBorrowing->IdentifyID,
                   newBorrowing->Title, newBorrowing->Author, &startTime) != 5) {
            free(newBorrowing);
            continue; // Bỏ qua dòng không hợp lệ
        }
        newBorrowing->Start = *localtime(&startTime); // Chuyển đổi thời gian
        InputBorrowing(newBorrowing); // Thêm vào bảng băm
    }
    fclose(file);

}

// Hàm tạo mã phiếu mượn --- Viet lai
void generateCode(char* code) {
    int num;
    sscanf(currentCode, "%d", &num); // Chuyển mã hiện tại thành số
    num++; 
    sprintf(currentCode, "%06d", num); // Đảm bảo chuỗi 6 chữ số
    strcpy(code, currentCode);
}
// // Tạo nút Borrowing mới
// Borrowing* newNode(char IdentifyID[12],char Title[100],char Author[100],  time_t now){
//     Borrowing *newBorrowing = (Borrowing*)malloc(sizeof(Borrowing));
//     strcpy(newBorrowing->IdentifyID, IdentifyID);
//     strcpy(newBorrowing->Title, Title);
//     strcpy(newBorrowing->Author, Author);

//     // Tạo mã phiếu mượn
//     generateCode(newBorrowing->Code);

//     // Thoi gian la nhap
//    newBorrowing->Start = *localtime(&now);
//     return newBorrowing;
// }

// // Tạo dữ liệu
// Borrowing* CreateNode(char IdentifyID[12],char Title[100],char Author[100], time_t now){
//     Borrowing* newBorrowing;
//     strcpy(newBorrowing->IdentifyID, IdentifyID);
//     strcpy(newBorrowing->Title, Title);
//     strcpy(newBorrowing->Author, Author);
//     return newBorrowing;
//     // Tạo mã phiếu mượn
//     generateCode(newBorrowing->Code);

//     // Lấy thời gian hiện tại (thời nhập chứu không lấy dữ liệu từ máy nữa)
//     newBorrowing->Start = *localtime(&now);
// }

//Kết hợp newnode và creatnewnode để đồng bộ vì mục đích là tạo nút borrowing mới
Borrowing* createBorrowingNode(char IdentifyID[12], char Title[100], char Author[100], time_t now) {
    Borrowing *newBorrowing = (Borrowing*)malloc(sizeof(Borrowing));//Cấp phát động
    //Kiểm tra cấp phát
    if (newBorrowing == NULL) {
        printf("Khong du bo nho de cap phat!\n");
        return NULL;
    }
    strcpy(newBorrowing->IdentifyID, IdentifyID);
    strcpy(newBorrowing->Title, Title);
    strcpy(newBorrowing->Author, Author);
    generateCode(newBorrowing->Code);//Tạo mã mới
    newBorrowing->Start = *localtime(&now);//Gán thời gian hiện tại
    return newBorrowing;
}

// Hàm tạo phiếu mượn mới
void createBorrowingTicket(char IdentifyID[12],char Title[100],char Author[100], time_t now) {
// Kiểm tra số lượng sách mượn của bạn đọc
    Member *member = SearchMember(IdentifyID);
    if (member == NULL) {
        printf("Khong tim thay ban doc voi CCCD: %s\n", IdentifyID);
        return;
    }
    if (member->CurrentQuantity >= 3) {
        printf("Ban doc da muon toi da 3 sach!\n");
        return;
    }

    // Kiểm tra sách có sẵn không
    Book *book = searchBook(Title, Author);
    if (book == NULL) {
        printf("Khong tim thay sach: %s - %s\n", Title, Author);
        return;
    }
    if (book->Quantity <= 0) {
        printf("Sach da het, them vao hang doi!\n");
        addToQueue(IdentifyID, Title, Author, now);
        return;
    }

    // Tạo phiếu mượn mới
    Borrowing *newBorrowing = createBorrowingNode(IdentifyID, Title, Author, now);
    InputBorrowing(newBorrowing);

    // Trừ số lượng sách trong thư viện
    book->Quantity--;

    // Tăng số lượng sách mượn của bạn đọc
    member->CurrentQuantity++;

    // Ghi vào file borrowing.csv
    FILE *file = fopen("borrowing.csv", "a");
    if (file) {
        fprintf(file, "%s,%s,%s,%s,%ld\n", newBorrowing->Code, newBorrowing->IdentifyID,
                newBorrowing->Title, newBorrowing->Author, mktime(&newBorrowing->Start));
        fclose(file);
    } else {
        printf("Loi khong mo duoc file borrowing.csv\n");
    }


}

// Thêm bạn đọc vào hàng đợi nếu sách không còn
void addToQueue(char IdentifyID[12], char Title[100], char Author[100], time_t now) {
    Book *book = searchBook(Title, Author);
    if (book == NULL) {
        printf("Khong tim thay sach: %s - %s\n", Title, Author);
        return;
    }

    Queue *newQueueNode = (Queue*)malloc(sizeof(Queue));
    strcpy(newQueueNode->IdentifyID, IdentifyID);
    strcpy(newQueueNode->Title, Title);
    strcpy(newQueueNode->Author, Author);
    newQueueNode->DecideBorrow = *localtime(&now);
    newQueueNode->Order = false; // Mặc định không ưu tiên
    newQueueNode->next = NULL;

    // Thêm vào hàng đợi (ưu tiên hoặc không ưu tiên)
    if (newQueueNode->Order) {
        if (book->queue1 == NULL) {
            book->queue1 = newQueueNode;
        } else {
            Queue *current = book->queue1;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newQueueNode;
        }
    } else {
        if (book->queue0 == NULL) {
            book->queue0 = newQueueNode;
        } else {
            Queue *current = book->queue0;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newQueueNode;
        }
    }
}

// Hàm xử lý mượn sách từ hàng đợi
void borrowFromQueue(char IdentifyID[12], char Title[100], char Author[100], time_t now) {
    Book *book = searchBook(Title, Author); // Tìm sách trong bảng băm
    if (book == NULL) {
        printf("Khong tim thay sach: %s - %s\n", Title, Author);
        return;
    }

    Queue *current = book->queue1 ? book->queue1 : book->queue0; // Lấy hàng đợi ưu tiên hoặc không ưu tiên
    Queue *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->IdentifyID, IdentifyID) == 0) {
            // Kiểm tra thời gian (3 ngày)
            time_t currentTime = now;
            double seconds = difftime(currentTime, mktime(&current->DecideBorrow));
            double days = seconds / (24 * 60 * 60);
            if (days > 3) {
                printf("Da qua 3 ngay, chuyen sang nguoi tiep theo!\n");
                if (prev == NULL) {
                    if (current->Order) {
                        book->queue1 = current->next;
                    } else {
                        book->queue0 = current->next;
                    }
                } else {
                    prev->next = current->next;
                }
                free(current);
                return;
            }

            // Cho mượn sách
            createBorrowingTicket(IdentifyID, Title, Author, now);
            Member *member = SearchMember(IdentifyID);
            if (member) member->CurrentQuantity++; // Cập nhật số lượng sách mượn
            if (prev == NULL) {
                if (current->Order) {
                    book->queue1 = current->next;
                } else {
                    book->queue0 = current->next;
                }
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Khong tim thay ban doc trong hang doi!\n");
}

// Hàm tìm phiếu mượn theo mã
AVLNode* searchBorrowingTicket(char code[6]) {
    // Tính chỉ số bảng băm dựa trên ký tự đầu của mã
    int index = hash(code);
    return searchAVL(HashTableBorrowing[index], code, compareString);//Tìm trong cây AVL
}

// Hàm kiểm tra phiếu mượn có quá hạn không (hạn mượn 3 tháng)
bool isBorrowingOverdue(AVLNode* node) {
     if (node == NULL) return false; // Trả về false nếu nút rỗng
    Borrowing* borrow = (struct Borrowing*)node->data;
    time_t now = time(NULL);//Lấy thời gian hiện tại
    double seconds = difftime(now, mktime(&borrow->Start));//Tính giây
    double months = seconds / (30 * 24 * 60 * 60); // Ước lượng 1 tháng = 30 ngày
    return (months > 3); // Quá hạn nếu hơn 3 tháng
}

// Ghi vào file return.csv
void WriteReturn(const char *filename, Borrowing* borrow){
    time_t now = time(NULL);//Lấy thời gian hiện tại
    struct tm end = *localtime(&now);//Chuyển thanh struct tm
    // Mở file
    FILE* file = fopen(filename, "a");
    if (file) {
        fprintf(file, "%s,%s,%s,%s,%ld,%ld\n", borrow->Code, borrow->IdentifyID, borrow->Title, borrow->Author, mktime(&borrow->Start), mktime(&end));//Ghi dữ liệu
        fclose(file);
    }
    else 
        printf("Loi khong mo duoc file");
}

// Hàm xóa phiếu mượn và thêm vào file returned.csv
void deleteBorrowingTicket(char code[6]) {
    // Tính chỉ số bảng băm dựa trên ký tự đầu của mã
    int index = hash(code);
    AVLNode* node = searchBorrowingTicket(code);//Tìm phiếu mượn
    if (node == NULL) {
        printf("Khong tim thay phieu muon!\n");
        return;
    }

    Borrowing* borrow = (Borrowing*)node->data;
    // Kiểm tra và xử lý quá hạn
    bool overdue = isBorrowingOverdue(node);
    if (overdue) {
        printf("Muon qua han, xin hay nop tien phat\n");
    }
    // Ghi vao file returned.csv
    WriteReturn("return.csv", borrow);
    // Cập nhật số lượng sách trong book.csv
    Book* tmp=searchBook(borrow->Title,borrow->Author);
    tmp->Quantity ++; 

    // Cập nhật số lượng sách mượn của bạn đọc
    Member* tmp1=searchMember(borrow->IdentifyID);
    tmp1->CurrentQuantity ++;

    // Xóa khỏi cây AVL
    HashTableBorrowing[index] = deleteAVL(HashTableBorrowing[index], code, compareString);
    // Cập nhật file borrowing.csv
    storeBorrowing();
}

// Duyệt và ghi dữ liệu bảng băm vào file borrowing.csv (gốc -> trái -> phải)
void inorderWriteBorrowing(FILE *file, AVLNode *node) {
    if (node == NULL) return;
    inorderWriteBorrowing(file, node->left);//Duyệt con trái
    Borrowing *borrow = (Borrowing *)node->data;//Duyệt cha
    fprintf(file, "%s,%s,%s,%s,%ld\n", borrow->Code, borrow->IdentifyID,
            borrow->Title, borrow->Author, mktime(&borrow->Start));//Ghi dữ liệu
    inorderWriteBorrowing(file, node->right);//Duyệt con phải
}

//Hàm ghi toàn bộ dữ liệu bảng băm vào file borrowing.csv
void storeBorrowing() {
    //Mở file ở chế độ ghi đè
    FILE *file = fopen("borrowing.csv", "w");
    if (file == NULL) {
        printf("Loi khong mo duoc file borrowing.csv\n");
        return;
    }
    // Ghi mã hiện tại ở dòng đầu
    fprintf(file, "%s\n", currentCode);
    for (int i = 0; i < TABLE_SIZE; i++) {
        //Ghi dữ liệu từ bảng băm
        inorderWriteBorrowing(file, HashTableBorrowing[i]);
    }
    fclose(file);
}
