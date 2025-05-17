#ifndef DATA_H
#define DATA_H
#include <stdio.h>
#include <time.h>
#define TABLE_SIZE 10

// Định nghĩa cấu trúc đối tượng 
struct Book{
    char Title[100], Author[100], key[201];
    int Quantity;   
    Queue* queue; // con trỏ queue để lưu trữ thông tin hàng đợi
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
    char Code[6], IdentifyID[12], Title[100], Author[100];
    struct tm Start;
    // Ví dụ về cách sử dụng struct tm để lưu trữ thời gian
    // struct tm *local;
    // time_t t;
    // t = time(NULL); // Lấy thời gian hiện tại
    // local = localtime(&t); // Chuyển đổi sang cấu trúc tm
    // printf("Thoi gian hien tai: %02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);
    // printf("Ngay hien tai: %02d/%02d/%04d\n", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
};
typedef struct Borrowing Borrowing;
// Cấu trúc Borrowing - dùng để lưu trữ thông tin mượn sách

struct Queue{
    char IdentifyID[12], Title[100], Author[100];
    struct tm DecideBorrow; // Thời gian sách đã về và ấn định cho người này
    // Nếu thời gian người này đến lấy sách trễ hơn thời gian này 3 ngày thì sẽ không được mượn sách
    int Order;
    struct Queue *next; // con trỏ next để lưu trữ thông tin hàng đợi
};
typedef struct Queue Queue;
// Cấu trúc queue - dùng để lưu trữ thông tin hàng đợi mượn sách

/*----------------------------------------------------------------------------------------*/

//Cấu trúc cây AVL tổng quát
struct AVLNode{
    void *data; // Dữ liệu của nút tự định nghĩa kiểu dữ liệu
    struct AVLNode *left, *right; // Con trái và con phải của nút
    int height; // Chiều cao của nút
};
typedef struct AVLNode AVLNode;

// Khai báo biến toàn cục cho bảng băm, được định nghĩa ở main.c
extern AVLNode *HashTableBook[TABLE_SIZE]; // Bảng băm cho sách
extern AVLNode *HashTableMember[TABLE_SIZE]; // Bảng băm cho thành viên
extern AVLNode *HashTableBorrowing[TABLE_SIZE]; // Bảng băm cho thông tin mượn sách

#endif