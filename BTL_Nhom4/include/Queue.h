#ifndef QUEUE_H
#define QUEUE_H

#include "Data.h"
// Tạo nút Queue 
Queue* makeNode(char* IdentifyID, char* Title, char* Author, bool Order);
// Thêm nút vào hàng đợi 
void insertNode(char *IdentifyID, char *Title, char *Author, bool Order);
//Lấy thông tin người đầu tiên
Queue* getfront(Book *book);
// Xoá node đầu tiên của cả hai hàng đợi (ưu tiên trước)
void deleteNode(Book *book);
// Duyệt in cả hai hàng đợi
void traverse(char* Title, char* Author);
// Tìm người trong queue1 hoặc queue0 của một cuốn sách
Queue* searching(Book* book, char* IdentifyyID);
// Lưu từng nhánh hàng đợi vào file 
void saveQueueToFileHelper(FILE *f, Queue *q);
// Lưu hàng đợi vào file 
void saveQueueOfBookWithFile(Book *book, void *filePtr);
// Dùng cho hàm saveAllQueuesToFile
void traverseAVLWithArg(AVLNode *root, void (*visit)(Book *, void *), void *arg);
// Duyệt toàn bộ sách để lưu hàng đợi 
void saveAllQueuesToFile(const char *fileName);
// Đọc từ file ra 
void loadQueueFromFile(const char *fileName);
// Thêm nút vào hàng đợi 
void insertQueueNode(Book *book, Queue *node);

#endif