#ifndef BOOK_H
#define BOOK_H

#include "data.h"
#include "avlTree.h"

void loadBooksFromFile(const char* fileName);

void insertBook(Book book);

Book* searchBook(const char* title, const char* author);

void deleteBook(const char* title, const char* author);

void displayAllBooks();

#endif
