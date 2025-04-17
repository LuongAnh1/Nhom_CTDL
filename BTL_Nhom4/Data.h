#ifndef DATA_h
#define DATA_h
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
Node *Table[TABLE_SIZE]; // Bảng băm

#endif