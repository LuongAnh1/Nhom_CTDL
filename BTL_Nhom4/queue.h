#ifndef QUEUE_H
#define QUEUE_H

#include "data.h"
//Chèn node
void insertNode(char IdentifyID[12], char Title[100], char Author[100], bool order);
//Lấy thông tin người đầu tiên và xóa
Queue* getfront(Book *book);
void deleteNode(Book *book);

//Duyệt danh sách người mượn
void traverse(char Titlee[100], char Author[100]);

//Tìm kiếm người mượn
Queue* searching(Book* book, char IdentifyyID[12]);

#endif
