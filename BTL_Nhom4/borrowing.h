#ifndef BORROWING_H
#define BORROWING_H

#include <time.h>
#include <stdbool.h>
#include "data.h"
#include "AVL_Tree.h"

// Hàm thêm phiếu mượn vào bảng băm
void InputBorrowing(Borrowing *newBorrowing);

// Đọc từ file csv và thêm vào bảng băm
void ReadBorrowing(const char *filename);

// Tạo mã phiếu mượn
void generateCode(char* code);

// Tạo phiếu mượn mới
// Tham số: identifyID (CCCD bạn đọc), title (tiêu đề sách), author (tác giả sách), now (thời gian mượn)
void createBorrowingTicket(char IdentifyID[12], char Title[100], char Author[100], time_t now);

// Thêm bạn đọc vào hàng đợi nếu sách không còn
void addToQueue(char IdentifyID[12], char Title[100], char Author[100], time_t now);

// Xử lý mượn sách từ hàng đợi
void borrowFromQueue(char IdentifyID[12], char Title[100], char Author[100], time_t now);

// Tìm phiếu mượn theo mã
// Trả về nút AVL chứa thông tin phiếu mượn, hoặc NULL nếu không tìm thấy
AVLNode* searchBorrowingTicket(char* code);

// Kiểm tra phiếu mượn có quá hạn không (hạn mượn 3 tháng)
// Trả về true nếu quá hạn, false nếu không
bool isBorrowingOverdue(struct AVLNode* node);

// Xóa phiếu mượn và thêm vào file returned.csv
void deleteBorrowingTicket(char* code);

// Ghi dữ liệu bảng băm vào file borrowing.csv
void storeBorrowing();

#endif