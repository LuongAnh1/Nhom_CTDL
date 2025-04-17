#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hash.h"
#include "Data.h"
#include "Manipulate.h"
#include "Change_Data.h"
#include <windows.h> // Thư viện cho hàm system("cls")

Node *Table[TABLE_SIZE] = {NULL}; // Khai báo bảng băm toàn cục
int main() {
    ReadDataFromFile("english_books.csv"); // Đọc dữ liệu từ file CSV và chèn vào bảng băm
    system("pause"); // Tạm dừng chương trình
    system("cls");
    return 0;
}
