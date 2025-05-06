#include "Change_Data.h"
#include "Manipulate.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "Data.h"


void ReadDataFromFile(const char *filename){
    FILE *f;
    f=fopen(filename,"r"); // Mở file
    if (f == NULL) {
        printf("Khong mo duoc file\n");
        return;
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
}