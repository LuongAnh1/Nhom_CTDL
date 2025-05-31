#ifndef BORROWING_H
#define BORROWING_H

#include <time.h>
#include <stdbool.h>
#include "Data.h"
#include "AVL_Tree.h"

// Biến toàn cục
extern char currentCode[6];
// Hàm thêm phiếu mượn vào bảng băm
void InputBorrowing(Borrowing *newBorrowing);

// Đọc từ file csv và thêm vào bảng băm
void ReadBorrowing(const char *filename);

// Tạo mã phiếu mượn
void generateCode(char* code);

// Tạo nút borrowing mới 
Borrowing* createBorrowingNode(char* IdentifyID, char* Title, char* Author, struct tm now);
// Tham số: identifyID (CCCD bạn đọc), title (tiêu đề sách), author (tác giả sách), now (thời gian mượn)
void createBorrowingTicket(char* IdentifyID, char* Title, char* Author, struct tm now);
// Tìm phiếu mượn theo mã
// Trả về nút AVL chứa thông tin phiếu mượn, hoặc NULL nếu không tìm thấy
AVLNode* searchBorrowingTicket(char* code);

// Kiểm tra phiếu mượn có quá hạn không (hạn mượn 3 tháng)
// Trả về true nếu quá hạn, false nếu không
bool isBorrowingOverdue(struct AVLNode* node);
// Ghi vào file return.csv
void WriteReturn(const char *filename, Borrowing* borrow);
// Xóa phiếu mượn và thêm vào file returned.csv
void deleteBorrowingTicket(char* code);
// Duyệt và ghi dữ liệu bảng băm vào file borrowing.csv
void inorderWriteBorrowing(FILE *file, AVLNode *node);
// Ghi dữ liệu bảng băm vào file borrowing.csv
void storeBorrowing(const char *filename);
// Hàm hiển thị tất cả phiếu mượn 
void displayAllBorrowing();

#endif
