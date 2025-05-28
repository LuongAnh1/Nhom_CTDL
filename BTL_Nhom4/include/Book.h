#ifndef BOOK_H
#define BOOK_H

#include "Data.h"
#include "hash.h"


// Chuẩn hóa chuỗi
void tolowerCase(char *str);
void trim(char *str);

// Sinh key từ title và author
void generateKey(char *key, const char *title, const char *author);

// So sánh key dạng chuỗi
int compareString(void *a, void *b);

// Đọc dữ liệu sách từ file
void loadBooksFromFile(const char *fileName);

// Chèn thủ công
void insertBook(Book book);

// Tìm kiếm sách
Book* searchBook(const char* title, const char* author);

// Xóa sách
void deleteBook(const char* title, const char* author);

// Hiển thị toàn bộ thông tin sách trong thư viện
void displayAllBooks();

// Lưu vào file
void saveToFile(const char *fileName);

// Duyệt AVL để hiển thị sách
void traverseAVL(AVLNode *root, void (*visit)(Book *));
void printBook(Book *book);

#endif
