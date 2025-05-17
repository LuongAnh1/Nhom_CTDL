#ifndef BOOK_H
#define BOOK_H

#include "data.h"
#include "AVL_Tree.h"

//Đọc dữ liệu sách từ file
void loadBooksFromFile(const char *fileName);

//Chèn thủ công
void insertBook(Book book);

//Tìm kiếm sách
Book* searchBook(const char* title, const char* author);

//Xóa sách
void deleteBook(const char* title, const char* author);

//Hiển thị toàn bộ thông tin sách trong thư viện
void displayAllBooks();

//Lưu vào file
void saveToFile(const char *fileName);
#endif
