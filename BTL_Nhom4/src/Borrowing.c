#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Borrowing.h"
#include "AVL_Tree.h"
#include "hash.h"
#include "Book.h"
#include "Member.h"

// Biến toàn cục để lưu mã phiếu mượn hiện tại với giá trị mặc định
char currentCode[6] = "000000";

//Hàm thêm phiếu mượn vào bảng băm bằng cách tạo nút và chèn vào AVL
void InputBorrowing(Borrowing *newBorrowing) {
    char *key = newBorrowing->Code; // Lấy Code làm khóa
    HashTableBorrowing[hash(key)] = insertAVL(HashTableBorrowing[hash(key)], newBorrowing, key, compareString); // Thêm vào bảng băm
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
    if (fgets(line, sizeof(line), file)) 
        sscanf(line, "%6s", currentCode);

    //Đọc các dòng dữ liệu của phiếu mượn
    while (fgets(line, sizeof(line), file)) {
        // Nếu dòng chỉ chứa ký tự newline (dòng trống)
        if (strcmp(line, "\n") == 0)
            continue;
        line[strcspn(line, "\n")] = '\0';
        Borrowing *newBorrowing = (Borrowing*)malloc(sizeof(Borrowing));//Cấp phát động
        //Kiểm tra bộ nhớ
        if (newBorrowing == NULL) {
            printf("Khong du bo nho de cap phat!\n");
            fclose(file);
            return;
        }
        // đọc các trường 
        sscanf(line, "%[^,];%[^,];%[^,];%[^,];%d/%d/%d",
            newBorrowing->Code, newBorrowing->IdentifyID,
            newBorrowing->Title, newBorrowing->Author,
            &newBorrowing->Start.tm_mday,
            &newBorrowing->Start.tm_mon,
            &newBorrowing->Start.tm_year);
        newBorrowing->Start.tm_mon = newBorrowing->Start.tm_mon - 1;
        newBorrowing->Start.tm_year = newBorrowing->Start.tm_year -1900;
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

// Tạo nút Borrowing mới 
Borrowing* createBorrowingNode(char* IdentifyID, char* Title, char* Author, struct tm now) {
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
    newBorrowing->Start.tm_mday = now.tm_mday;//Gán thời gian hiện tại
    newBorrowing->Start.tm_mon = now.tm_mon;
    newBorrowing->Start.tm_year = now.tm_year;
    return newBorrowing;
}

// Hàm tạo phiếu mượn mới
void createBorrowingTicket(char* IdentifyID, char* Title, char* Author, struct tm now) {
    Member *member = SearchMember(IdentifyID);
    Book *book = searchBook(Title, Author);

    // Tạo phiếu mượn mới
    Borrowing *newBorrowing = createBorrowingNode(IdentifyID, Title, Author, now);
    InputBorrowing(newBorrowing);

    // Trừ số lượng sách trong thư viện
    book->Quantity--;

    // Tăng số lượng sách mượn của bạn đọc
    member->CurrentQuantity++;
}

// Hàm tìm phiếu mượn theo mã
AVLNode* searchBorrowingTicket(char* code) {
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
        fprintf(file, "%s;%s;%s;%s;%d/%d/%d;%d/%d/%d\n", borrow->Code, 
            borrow->IdentifyID, borrow->Title, borrow->Author, 
            borrow->Start.tm_mday, borrow->Start.tm_mon + 1,
            borrow->Start.tm_year + 1900,
            end.tm_mday, end.tm_mon + 1, end.tm_year + 1900);//Ghi dữ liệu
    }
    else 
        printf("Loi khong mo duoc file");
    fclose(file);
    return;
}

// Hàm xóa phiếu mượn và thêm vào file returned.csv
void deleteBorrowingTicket(char* code) {
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
        system("PAUSE");
    }
    // Ghi vao file returned.csv
    WriteReturn("data/returned.csv", borrow);
    // Cập nhật số lượng sách trong book.csv
    Book* tmp=searchBook(borrow->Title,borrow->Author);
    tmp->Quantity ++; 

    // Cập nhật số lượng sách đang mượn của bạn đọc
    Member* tmp1=SearchMember(borrow->IdentifyID);
    tmp1->CurrentQuantity--;

    // Xóa khỏi cây AVL
    HashTableBorrowing[index] = deleteAVL(HashTableBorrowing[index], code, compareString);
    printf("Tra sach thanh cong\n");
}
// Hàm duyệt AVL để hiển thị danh sách mượn 
void printBorrowing(Borrowing* borrow) {
    printf("%-7s | %-13s | %-40s | %-40s | %02d/%02d/%d\n",borrow->Code ,borrow->IdentifyID
        ,borrow->Title, borrow->Author
        ,borrow->Start.tm_mday, borrow->Start.tm_mon + 1, borrow->Start.tm_year + 1900);
}

void traverseAVLBorrowing(AVLNode *root, void (*visit)(Borrowing *)) {
    if (!root) return;
    traverseAVLBorrowing(root->left, visit);
    visit((Borrowing *)root->data);
    traverseAVLBorrowing(root->right, visit);
}
// Hàm hiển thị tất cả phiếu mượn 
void displayAllBorrowing() {
    printf("%-7s | %-13s | %-40s | %-40s | %-13s\n", "Code", "CCCD", "Tieu de", "Tac gia", "Ngay muon");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < TABLE_SIZE; ++i) {
        traverseAVLBorrowing(HashTableBorrowing[i], printBorrowing);
    }
}
// Duyệt và ghi dữ liệu bảng băm vào file borrowing.csv theo chiều rộng 
typedef struct queue{
    AVLNode* node;
    struct queue *next;
} queue;
queue* createNodequeueBorrowing(AVLNode *node){
    queue* newNode = (queue*)malloc(sizeof(queue));
    newNode->node = node;
    newNode->next = NULL;
    return newNode;
}
// Ghi dữ liệu theo chiều rộng 
void inorderWriteBorrowing(FILE *file, AVLNode *node) {
    if (node == NULL) return;

    queue* head = createNodequeueBorrowing(node);
    queue* tail = head;

    while (head != NULL) {
        if (head->node->left != NULL) {
            tail->next = createNodequeueBorrowing(head->node->left);
            tail = tail->next;
        }
        if (head->node->right != NULL) {
            tail->next = createNodequeueBorrowing(head->node->right);
            tail = tail->next;
        }

        Borrowing* borrow = head->node->data;
        fprintf(file, "%s;%s;%s;%s;%d/%d/%d\n", borrow->Code, 
        borrow->IdentifyID,borrow->Title, borrow->Author, 
        borrow->Start.tm_mday,borrow->Start.tm_mon,borrow->Start.tm_year);//Ghi dữ liệu

        queue* tmp = head;
        head = head->next;
        free(tmp);
    }
}

//Hàm ghi toàn bộ dữ liệu bảng băm vào file borrowing.csv
void storeBorrowing(const char *filename) {
    //Mở file ở chế độ ghi đè
    FILE *file = fopen(filename, "w");
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
