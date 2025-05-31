#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Data.h"
#include "AVL_Tree.h"
#include "Library_Service.h"
#include "Member.h"
#include "Book.h"
#include "Borrowing.h"
#include "Queue.h"
// #include <windows.h>

/*
Lưu ý khi kết nối các modul: 
gcc -o main.c src/*.c -Iinclude
*/ 

// định nghĩa biến toàn cục
AVLNode *HashTableBook[TABLE_SIZE] = {NULL};
AVLNode *HashTableMember[TABLE_SIZE] = {NULL};
AVLNode *HashTableBorrowing[TABLE_SIZE] = {NULL};

// Chỗ này cần có thêm hàm xử lý xâu để so sánh, với Book thì key = <Title>_<Author>
int main() {
    // Tải dữ liệu lên bảng băm 
    ReadMember("data/member.csv");
    loadBooksFromFile("data/book.csv");
    ReadBorrowing("data/borrowing.csv");
    loadQueueFromFile("data/queue.csv");
    printf("Tai du lieu thanh cong\n");
    system("PAUSE");
    // Chạy giao diện 
    LibraryUI();
    // Tải dữ liệu từ bảng băm về file .csv 
    saveAllQueuesToFile("data/queue.csv"); 
    storeBorrowing("data/borrowing.csv");
    saveToFile("data/book.csv");
    StoreMember("data/member.csv");
    printf("Luu du lieu thanh cong\n");
    system("PAUSE");
    return 0;
}