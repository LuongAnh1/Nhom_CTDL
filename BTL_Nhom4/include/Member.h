#ifndef MEMBER_H
#define MEMBER_H
#include "Data.h"

//Thêm thành viên
void InputMember(Member *newMember);
// Đọc từ file csv
void ReadMember(const char *filename);
//Tìm kiếm thành viên
Member* SearchMember(char *IdentifyID);    
//Xóa thành viên
void DeleteMember();
// Ghi vaof file CSV 
void StoreMember(const char *filename );
// Hàm duyệt cây AVL 
void inorderWriteMember(FILE *file, AVLNode *node);
#endif