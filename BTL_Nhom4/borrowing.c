#include <stdio.h>
#include <string.h>
#include <time.h>
#include "borrowing.h"
#include "Libarary_Service.h"
#include "AVL_Tree.h"
#include "Data.h"          
#include "hash.h"

void InputBorrowing(Borrowing *newBorrowing) {
    char *key = newBorrowing->Code; // Lấy Code làm khóa
    AVLNode *newNode = createNode(Borrowing,key); // Tạo nút mới cho thành viên
    HashTableBorrowing[hash(key)] = InsertAVL(HashTableBorrowing[hash(key)], newNode, key, compareString); // Thêm vào bảng băm
}
// Đọc từ file csv
void ReadBorrowing(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file! %s\n", filename);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)){
        Borrowing *newBorrowing = (Borrowing*)malloc(sizeof(Borrowing));
        sscanf(line, "%[^,],%[^,],%[^,],%[^,]", newBorrowing->Code, newBorrowing->IdentifyID, newBorrowing->Title, newBorrowing->Author, newBorrowing->Start);

        InputBorrowing(newBorrowing); // Thêm thành viên vào bảng băm
    }
    fclose(file);

}


// Hàm tạo mã phiếu mượn --- Viet lai
void generateCode(char Code[6]){

}
// Taoj nuts Borrowing mới
Borrowing* newNode(char IdentifyID[12],char Title[100],char Author[100], struct tm now){
    Borrowing *newBorrowing;
    strcpy(newBorrowing->IdentifyID, IdentifyID);
    strcpy(newBorrowing->Title, Title);
    strcpy(newBorrowing->Author, Author);

    // Tạo mã phiếu mượn
    generateCode(newBorrowing->Code);

    // Thoi gian la nhap
    newBorrowing->Start = now;
}

// Hàm tạo phiếu mượn mới
void createBorrowingTicket(char IdentifyID[12],char Title[100],char Author[100], struct tm now) {
    Borrowing* newBorrowing = newNode(IdentifyID,Title,Author, now);
    // Kiểm tra số lượng sách đang mượn của bạn đọc (tối đa 3)
    if (getCurrentQuantity(IdentifyID) >= 3) {
        printf("Ban doc da muon toi da 3 sach!\n");
        return;
    }

    // Kiểm tra sách có sẵn không
    if (!isBookAvailable(title, author)) {
        printf("Sach khong con trong kho, them vao hang doi!\n");
        return;
    }

    // Tính chỉ số bảng băm dựa trên mã phiếu mượn
    int index = (newBorrowing.Code[0] - '0') % TABLE_SIZE;

    // Thêm vào bảng băm và cây AVL
    AVLNode* newNode = createNode(&newBorrowing);
    HashTableBorrowing[index] = insertAVL(HashTableBorrowing[index], &newBorrowing, compareString);

    // Cập nhật số lượng sách trong book.csv
    decreaseBookQuantity(title, author);

    // Cập nhật số lượng sách mượn của bạn đọc
    incrementCurrentQuantity(identifyID);

    // Ghi vào file borrowing.csv
    FILE* file = fopen("borrowing.csv", "a");
    if (file) {
        fprintf(file, "%s,%s,%s,%s,%ld\n", newBorrowing.Code, newBorrowing.IdentifyID,
                newBorrowing.Title, newBorrowing.Author, mktime(&newBorrowing.Start));
        fclose(file);
    }
}

// Hàm tìm phiếu mượn theo mã
struct AVLNode* searchBorrowingTicket(char* code) {
    // Tính chỉ số bảng băm dựa trên ký tự đầu của mã
    int index = (code[0] - '0') % TABLE_SIZE;
    return searchAVL(HashTableBorrowing[index], code, compareString);
}

// Hàm kiểm tra phiếu mượn có quá hạn không (hạn mượn 3 tháng)
int isBorrowingOverdue(struct AVLNode* node) {
    if (node == NULL) return 0;

    struct Borrowing* borrow = (struct Borrowing*)node->data;
    time_t now = time(NULL);
    double seconds = difftime(now, mktime(&borrow->Start));
    double months = seconds / (30 * 24 * 60 * 60); // Ước lượng 1 tháng = 30 ngày
    return months > 3; // Quá hạn nếu hơn 3 tháng
}

// Hàm xóa phiếu mượn và thêm vào file returned.csv
void deleteBorrowingTicket(char* code) {
    // Tính chỉ số bảng băm dựa trên ký tự đầu của mã
    int index = (code[0] - '0') % TABLE_SIZE;

    struct AVLNode* node = searchBorrowingTicket(code);
    if (node == NULL) {
        printf("Khong tim thay phieu muon!\n");
        return;
    }

    struct Borrowing* borrow = (struct Borrowing*)node->data;
    // Kiểm tra và xử lý quá hạn
    int overdue = isBorrowingOverdue(node);
    time_t now = time(NULL);
    struct tm end = *localtime(&now);

    // Ghi vào file returned.csv
    FILE* file = fopen("returned.csv", "a");
    if (file) {
        fprintf(file, "%s,%s,%s,%s,%ld,%ld\n", borrow->Code, borrow->IdentifyID,
                borrow->Title, borrow->Author, mktime(&borrow->Start), mktime(&end));
        fclose(file);
    }

    // Cập nhật số lượng sách trong book.csv
    increaseBookQuantity(borrow->Title, borrow->Author);

    // Cập nhật số lượng sách mượn của bạn đọc
    decrementCurrentQuantity(borrow->IdentifyID);

    // Xóa khỏi cây AVL
    HashTableBorrowing[index] = deleteAVL(HashTableBorrowing[index], code, compareString);

    // Cập nhật file borrowing.csv (xóa thủ công hoặc viết hàm riêng để xử lý)
    printf("Da xoa phieu muon va cap nhat vao returned.csv%s\n", overdue ? " (qua han)" : "");
}