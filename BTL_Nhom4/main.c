#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Data.h"
#include "AVL_Tree.h"
#include "Libarary_Service.h"

/*
Lưu ý khi kết nối các modul: 
gcc <Tên file>.c -o <Tên file>.exe -xc++ -lstdc++ -shared-libgcc
*/ 

// định nghĩa biến toàn cục
AVLNode *HashTableBook[TABLE_SIZE] = {NULL};
AVLNode *HashTableMember[TABLE_SIZE] = {NULL};
AVLNode *HashTableBorrowing[TABLE_SIZE] = {NULL};
// Hàm so sánh xâu
int compareString(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}
// Chỗ này cần có thêm hàm xử lý xâu để so sánh, với Book thì key = <Title>_<Author>
int main() {
    Option();
    // Xóa AVL sẽ tùy trường hợp của bảng băm -> hàm deleteAVL không cần 
    //-> sử dụng hàm searchAVL để xử lý với tùy bảng băm
    /*
    Thủ tục insertAVL 
    insertAVL(<cây AVL>, <đối tượng>, <hàm so sánh>);
    Nếu đối tượng đã tồn tại trong cây AVL thì sẽ trả về vị trí của nó trong cây
    Nếu không thì sẽ thêm vào cây AVL và trả về NULL
    Hàm so sánh hiện đang dùng chung hàm compareString
    */
    // Ví dụ
    // Khởi tạo sách
    // Book *book = (Book *)malloc(sizeof(Book));
    // strcpy(book->Title, "C Programming Language");
    // strcpy(book->Author, "Brian W. Kernighan and Dennis M. Ritchie");
    // book->Quantity = 5;
    // Thêm sách vào bảng băm
    // HashTableBook[0] = insertAVL(HashTableBook[0],book, compareString);

    // -------------------------------------------------------------------------

    /*
    Thủ tục searchAVL
    searchAVL(<cây AVL>, <đối tượng>, <hàm so sánh>);
    Nếu đối tượng đã tồn tại trong cây AVL thì sẽ trả về vị trí của nó trong cây
    Nếu không thì sẽ trả về NULL
    */
    // Ví dụ
    // Khởi tạo sách
    // Book *book = (Book *)malloc(sizeof(Book));
    // strcpy(book->Title, "C Programming Language");
    // strcpy(book->Author, "Brian W. Kernighan and Dennis M. Ritchie");
    // book->Quantity = 5;
    // Tìm kiếm sách trong bảng băm
    // AVLNode *result = searchAVL(HashTableBook[0], book, compareString);
    // if (result != NULL) {
    //     printf("Sách đã tồn tại trong bảng băm\n");
    // } else {
    //     printf("Sách không tồn tại trong bảng băm\n");
    // }
    // free(book); // Giải phóng bộ nhớ đã cấp phát cho sách
    return 0;
}
