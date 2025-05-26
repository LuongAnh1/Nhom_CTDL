#ifndef BORROWING_H
#define BORROWING_H


#include <time.h>
#include "data.h"           
#include "AVL_Tree.h"       


// Hàm tạo phiếu mượn mới
void generateCode(char* code);

// Đọc từ file và chèn vào bảng băm
void LoadDataBorrowing(const char *filename);
// Tham số: identifyID (CCCD bạn đọc), title (tiêu đề sách), author (tác giả sách)
void createBorrowingTicket(char IdentifyID[12],char Title[100],char Author[100]);

// Hàm tìm phiếu mượn theo mã
// Trả về nút AVL chứa thông tin phiếu mượn, hoặc NULL nếu không tìm thấy
AVLNode* searchBorrowingTicket(char* code);

// Hàm kiểm tra phiếu mượn có quá hạn không (hạn mượn 3 tháng)
// Trả về 1 nếu quá hạn, 0 nếu không
int isBorrowingOverdue(struct AVLNode* node);

// Hàm xóa phiếu mượn và thêm vào file returned.csv
// Tham số: code (mã phiếu mượn)
void deleteBorrowingTicket(char* code);

#endif
