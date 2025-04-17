#ifndef DATA_H
#define DATA_H
#include <stdio.h>
#define TABLE_SIZE 10

struct Book{
    char Name[100], Author[100];
    int Have;   
};
typedef struct Book Book;
struct Node{
    Book data;
    struct Node *left, *right;
};
typedef struct Node Node;
extern Node *Table[TABLE_SIZE]; 
// Bảng băm, biến toàn cục - chỉ được định nghĩa 1 lần duy nhất 
// đang được định nghĩa trong hàm main.c


#endif