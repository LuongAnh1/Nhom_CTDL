#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hash.h"
#include "Data.h"
#include "Manipulate.h"
#include <windows.h> // Thư viện cho hàm system("cls")

Node *Table[TABLE_SIZE] = {NULL}; // Khai báo bảng băm toàn cục
int main() {
    FILE *f;
    f=fopen("english_books.csv","r"); // Mở file
    if (f == NULL) {
        printf("Khong mo duoc file\n");
        return 1;
    }
   
    // Đọc file và chèn sách vào bảng băm
    char line[100];
    while (fgets(line, sizeof(line), f)) { // Đọc từng dòng trong file
        Book book;
        sscanf(line, "%[^,],%[^,],%d", book.Name, book.Author, &book.Have); // Phân tích cú pháp dòng
        Insert(book); // Chèn sách vào bảng băm - hàm đã được định nghĩa ở file Manipulate.c
    }
    fclose(f); // Đóng file
    printf("Tai du lieu thanh cong\n");
    system("pause"); // Tạm dừng chương trình
    system("cls");
    return 0;
}
