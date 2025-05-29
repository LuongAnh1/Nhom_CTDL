#ifndef QUEUE_H
#define QUEUE_H

#include "Data.h"
// Tạo nút Queue 
Queue* makeNode(char IdentifyID[12], char Title[100], char Author[100], struct tm DecideDate, bool Order);
// Thêm nút vào hàng đợi 
void insertNode(const char *IdentifyID, const char *Title, const char *Author, bool Order, struct tm decideDate);
//Lấy thông tin người đầu tiên
Queue* getfront(Book *book);
// Xoá node đầu tiên của cả hai hàng đợi (ưu tiên trước)
void deleteNode(Book *book);
// Duyệt in cả hai hàng đợi
void traverse(char Titlee[100], char Author[100]);
// Tìm người trong queue1 hoặc queue0 của một cuốn sách
Queue* searching(Book* book, char IdentifyyID[12]);
// Lưu từng nhánh hàng đợi vào file 
void saveQueueToFileHelper(FILE *f, Queue *q, const char *title, const char *author);
// Lưu hàng đợi vào file 
void saveQueueOfBookWithFile(Book *book, void *filePtr);
// Dùng cho hàm saveAllQueuesToFile
void traverseAVLWithArg(AVLNode *root, void (*visit)(Book *, void *), void *arg);
// Duyệt toàn bộ sách để lưu hàng đợi 
void saveAllQueuesToFile(const char *fileName);
// Đọc từ file ra 
void loadQueueFromFile(const char *fileName);

#endif