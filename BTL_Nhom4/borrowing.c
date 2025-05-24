#include <stdio.h>
#include <string.h>
#include <time.h>
#include "borrowing.h"
#include "Libarary_Service.h"
#include "AVL_Tree.h"
#include "Data.h"          
int getCurrentQuantity(const char* identifyID);
int isBookAvailable(const char* title, const char* author);
void decreaseBookQuantity(const char* title, const char* author);
void increaseBookQuantity(const char* title, const char* author);
void incrementCurrentQuantity(const char* identifyID);
void decrementCurrentQuantity(const char* identifyID);

int compareString(const void* a, const void* b); // Nếu dùng cho AVL Tree


// Bảng băm toàn cục (đã được khai báo trong data.h và định nghĩa trong main.c)
extern AVLNode *HashTableBorrowing[TABLE_SIZE];

// Hàm khởi tạo bảng băm và cây AVL
void initBorrowing() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashTableBorrowing[i] = NULL; // Đảm bảo bảng băm rỗng
    }
}

// Hàm tạo mã phiếu mượn ngẫu nhiên (6 ký tự: số đến chữ)
void generateCode(char* code) {
    for (int i = 0; i < 6; i++) {
        code[i] = (rand() % 36 < 10) ? ('0' + rand() % 10) : ('A' + rand() % 26);
    }
    code[6] = '\0';
}

// Hàm tạo phiếu mượn mới
void createBorrowingTicket(char* identifyID, char* title, char* author) {
    struct Borrowing newBorrowing;
    strcpy(newBorrowing.IdentifyID, identifyID);
    strcpy(newBorrowing.Title, title);
    strcpy(newBorrowing.Author, author);

    // Tạo mã phiếu mượn
    generateCode(newBorrowing.Code);

    // Lấy thời gian hiện tại
    time_t now = time(NULL);
    newBorrowing.Start = *localtime(&now);

    // Kiểm tra số lượng sách đang mượn của bạn đọc (tối đa 3)
    if (getCurrentQuantity(identifyID) >= 3) {
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