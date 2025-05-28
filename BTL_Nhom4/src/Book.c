#include "Book.h"
#include "AVL_Tree.h"
#include "hash.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Hàm chuyển về các ký tự thường
void tolowerCase(char *str) {
    for (; *str; ++str) *str = tolower(*str);
}

// Hàm trim chuẩn hóa chuỗi (xóa khoảng trắng đầu/cuối)
void trim(char *str) {
    char *start = str;
    while (isspace((unsigned char)*start)) start++;
    if (start != str) memmove(str, start, strlen(start) + 1);

    char *end = str + strlen(str) - 1;
    while (end >= str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}

// Tạo key tạm thời từ title và author: title_author (chuẩn hóa trước khi nối)
void generateKey(char *key, const char *title, const char *author) {
    char t[100], a[100];
    strncpy(t, title, sizeof(t) - 1); t[sizeof(t) - 1] = '\0';
    strncpy(a, author, sizeof(a) - 1); a[sizeof(a) - 1] = '\0';
    trim(t); trim(a);
    tolowerCase(t); tolowerCase(a);
    snprintf(key, 201, "%s_%s", t, a);
}

// Thêm sách vào hệ thống
void insertBook(Book book) {
    trim(book.Title);
    trim(book.Author);
    tolowerCase(book.Title);
    tolowerCase(book.Author);

    char key[201];
    generateKey(key, book.Title, book.Author);
    int index = hash(key);

    // printf("DEBUG: Thêm sách với key = '%s', index = %d\n", key, index);

    // Tìm xem đã có sách này chưa
    AVLNode *found = searchAVL(HashTableBook[index], key, compareString);
    if (!found) {
        Book *newBook = (Book *)malloc(sizeof(Book));
        if (newBook) {
            *newBook = book;
            char *keyCopy = strdup(key); // Đảm bảo key tồn tại suốt đời node
            HashTableBook[index] = insertAVL(HashTableBook[index], newBook, keyCopy, compareString);
        }
    } else {
        Book *exist = (Book *)found->data;
        exist->Quantity += book.Quantity;
    }
}

// Tìm kiếm sách
Book* searchBook(const char *title, const char *author) {
    char key[201];
    generateKey(key, title, author);
    int index = hash(key);

    //printf("DEBUG: Tìm sách với key = '%s', index = %d\n", key, index);

    AVLNode *found = searchAVL(HashTableBook[index], key, compareString);
    if (found) return (Book *)found->data;
    return NULL;
}

// Hàm xóa sách
void deleteBook(const char *title, const char *author) {
    char key[201];
    generateKey(key, title, author);
    int index = hash(key);
    HashTableBook[index] = deleteAVL(HashTableBook[index], key, compareString);
}

// Hàm duyệt AVL để hiển thị sách
void printBook(Book *book) {
    printf("%-30s | %-20s | %d\n", book->Title, book->Author, book->Quantity);
}

void traverseAVL(AVLNode *root, void (*visit)(Book *)) {
    if (!root) return;
    traverseAVL(root->left, visit);
    visit((Book *)root->data);
    traverseAVL(root->right, visit);
}

// Hàm hiển thị tất cả sách
void displayAllBooks() {
    printf("%-30s | %-20s | %s\n", "Tiêu đề", "Tác giả", "Số lượng");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < TABLE_SIZE; ++i) {
        traverseAVL(HashTableBook[i], printBook);
    }
}

void loadBooksFromFile(const char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (!f) {
        printf("Không thể mở file %s\n", fileName);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        // Nếu dòng chỉ chứa ký tự newline (dòng trống)
        if (strcmp(line, "\n") == 0)
            continue;
        line[strcspn(line, "\n")] = '\0';
        Book book;
        char *token = strtok(line, ";");
        if (!token) continue;
        strncpy(book.Title, token, sizeof(book.Title) - 1); book.Title[sizeof(book.Title) - 1] = '\0';

        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(book.Author, token, sizeof(book.Author) - 1); book.Author[sizeof(book.Author) - 1] = '\0';

        token = strtok(NULL, ";");
        if (!token) continue;
        book.Quantity = atoi(token);

        insertBook(book);
    }
    fclose(f);
}

void saveBookToFileHelper(AVLNode *root, FILE *f) {
    if (!root) return;
    saveBookToFileHelper(root->left, f);
    Book *book = (Book *)root->data;
    fprintf(f, "%s,%s,%d\n", book->Title, book->Author, book->Quantity);
    saveBookToFileHelper(root->right, f);
}

void saveToFile(const char *fileName) {
    FILE *f = fopen(fileName, "w");
    if (!f) {
        printf("Không thể mở file %s để ghi!\n", fileName);
        return;
    }
    for (int i = 0; i < TABLE_SIZE; ++i) {
        saveBookToFileHelper(HashTableBook[i], f);
    }
    fclose(f);
}
