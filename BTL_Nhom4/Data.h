#ifndef DATA_H
#define DATA_H
#include <stdio.h>
#include <time.h>
#define TABLE_SIZE 10

// Dinh nghia cau truc cac doi tuongtuong
struct Book{
    char Tittle[100], Author[100];
    int Quantity;   
};
typedef struct Book Book;
// Cấu trúc Book - dùng để lưu trữ thông tin sách

struct Member{
    char IdentifyID[12], Name[100];
    int CurrentQuantity;
};
typedef struct Member Member;
// Cấu trúc Member - dùng để lưu trữ thông tin thành viên

struct Borrowing{
    char Code[6], IdentifyID[12], Tittle[100], Author[100];
    struct tm Start;
};
typedef struct Borrowing Borrowing;
// Cấu trúc Borrowing - dùng để lưu trữ thông tin mượn sách

struct Queue{
    char IdentifyID[12], Tittle[100], Author[100];
    int Order;
};
typedef struct Queue Queue;
// Cấu trúc queue - dùng để lưu trữ thông tin hàng đợi mượn sách

/*----------------------------------------------------------------------------------------*/

// Bảng băm, biến toàn cục - chỉ được định nghĩa 1 lần duy nhất 
// đang được định nghĩa trong hàm main.c
// Bảng băm này sẽ được sử dụng để lưu trữ thông tin sách
struct AVLBook{
    Book data;
    char key[200];
    struct AVLBook *left, *right;
    int height;
    Queue *head;
};
typedef struct AVLBook AVLBook;
extern AVLBook *HashTableBook[TABLE_SIZE]; 

// Bảng băm này sẽ được sử dụng để lưu trữ thông tin thành viên
struct AVLMember{
    Member data;
    struct AVLMember *left, *right;
    int height;
};
typedef struct AVLMember AVLMember;
extern AVLMember *HashTableMember[TABLE_SIZE];

// Bảng băm này sẽ được sử dụng để lưu trữ thông tin mượn sách
struct AVLBorrowing{
    Borrowing data;
    struct AVLBorrowing *left, *right;
    int height;
}; 
typedef struct AVLBorrowing AVLBorrowing;
extern AVLBorrowing *HashTableBorrowing[TABLE_SIZE];
#endif