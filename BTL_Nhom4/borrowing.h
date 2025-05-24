#ifndef BORROWING_H
#define BORROWING_H


#include <time.h>
#include "data.h"           
#include "AVL_Tree.h"       

// Khai báo biến toàn cục (đã được định nghĩa trong main.c và khai báo trong data.h)
extern AVLNode *HashTableBorrowing[TABLE_SIZE];

// Hàm khởi tạo bảng băm và cây AVL cho phiếu mượn
void initBorrowing();

// Hàm tạo phiếu mượn mới
// Tham số: identifyID (CCCD bạn đọc), title (tiêu đề sách), author (tác giả sách)
void createBorrowingTicket(char* identifyID, char* title, char* author);

// Hàm tìm phiếu mượn theo mã
// Trả về nút AVL chứa thông tin phiếu mượn, hoặc NULL nếu không tìm thấy
struct AVLNode* searchBorrowingTicket(char* code);

// Hàm kiểm tra phiếu mượn có quá hạn không (hạn mượn 3 tháng)
// Trả về 1 nếu quá hạn, 0 nếu không
int isBorrowingOverdue(struct AVLNode* node);

// Hàm xóa phiếu mượn và thêm vào file returned.csv
// Tham số: code (mã phiếu mượn)
void deleteBorrowingTicket(char* code);

#endif
