#include <stdio.h>
#include <string.h>
#include <time.h>
#include "borrowing.h"
#include "Libarary_Service.h"
#include "AVL_Tree.h"
#include "Data.h"          
#include "hash.h"
#include <bool.h>
#include "Book.h"
#include "Member.h"

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
        sscanf(line, "%[^,],%[^,],%[^,],%ld", newBorrowing->Code, newBorrowing->IdentifyID, newBorrowing->Title, newBorrowing->Author, newBorrowing->Start);

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
    // Thêm vào bảng băm
    InputBorrowing(newBorrowing);
    // Trừ số lượng sách hiện có trong thư viên
    Book* tmp=searchBook(Title,Author);
    tmp->Quantity --;
}

// Hàm tìm phiếu mượn theo mã
AVLNode* searchBorrowingTicket(char code[6]) {
    // Tính chỉ số bảng băm dựa trên ký tự đầu của mã
    int index = hash(code);
    return searchAVL(HashTableBorrowing[index], code, compareString);
}

// Hàm kiểm tra phiếu mượn có quá hạn không (hạn mượn 3 tháng)
bool isBorrowingOverdue(AVLNode* node) {
    Borrowing* borrow = (struct Borrowing*)node->data;
    time_t now = time(NULL);
    double seconds = difftime(now, mktime(&borrow->Start));
    double months = seconds / (30 * 24 * 60 * 60); // Ước lượng 1 tháng = 30 ngày
    return (months > 3); // Quá hạn nếu hơn 3 tháng
}

// Ghi vào file return.csv
void WriteReturn(const char *filename, Borrowing* borrow){
    // Ghi vào file returned.csv
    FILE* file = fopen(filename, "a");
    if (file) {
        fprintf(file, "%s,%s,%s,%s,%ld,%ld\n", borrow->Code, borrow->IdentifyID, borrow->Title, borrow->Author, mktime(&borrow->Start), mktime(&end));
        fclose(file);
    }
    else 
        printf("Loi khong mo duoc file");
}
// Hàm xóa phiếu mượn và thêm vào file returned.csv
void deleteBorrowingTicket(char code[6]) {
    // Tính chỉ số bảng băm dựa trên ký tự đầu của mã
    int index = hash(code);

    AVLNode* node = searchBorrowingTicket(code);
    if (node == NULL) {
        printf("Khong tim thay phieu muon!\n");
        return;
    }

    Borrowing* borrow = (struct Borrowing*)node->data;
    // Kiểm tra và xử lý quá hạn
    bool overdue = isBorrowingOverdue(node);
    if (overdue == true)
        printf("Muon qua han, xin hay nop tien phat\n");
    time_t now = time(NULL);
    struct tm end = *localtime(&now);
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
}