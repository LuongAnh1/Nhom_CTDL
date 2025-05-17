#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Data.h"
#include "AVL_Tree.h"
#include "Library_Service.h"
#include "book.h"
#include <windows.h>


/*
Lưu ý khi kết nối các modul: thie
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

    SetConsoleOutputCP(65001);
    int choice;
    char title[100], author[100], fileName[100];
    int quantity;
    Book book;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Thêm sách\n");
        printf("2. Hiển thị tất cả sách\n");
        printf("3. Tìm kiếm sách\n");
        printf("4. Xóa sách\n");
        printf("5. Lưu sách ra file\n");
        printf("6. Đọc sách từ file\n");
        printf("0. Thoát\n");
        printf("Chọn chức năng: ");
        scanf("%d", &choice);
        getchar(); // Xóa ký tự '\n' sau scanf

        switch (choice) {
            case 1:
                printf("Nhập tiêu đề sách: ");
                fgets(title, sizeof(title), stdin); title[strcspn(title, "\n")] = 0;
                printf("Nhập tác giả: ");
                fgets(author, sizeof(author), stdin); author[strcspn(author, "\n")] = 0;
                printf("Nhập số lượng: ");
                scanf("%d", &quantity); getchar();
                strcpy(book.Title, title);
                strcpy(book.Author, author);
                book.Quantity = quantity;
                insertBook(book);
                printf("Đã thêm sách!\n");
                break;
            case 2:
                printf("== Danh sách sách ==\n");
                displayAllBooks();
                break;
            case 3:
                printf("Nhập tiêu đề sách cần tìm: ");
                fgets(title, sizeof(title), stdin); title[strcspn(title, "\n")] = 0;
                printf("Nhập tác giả: ");
                fgets(author, sizeof(author), stdin); author[strcspn(author, "\n")] = 0;
                Book *found = searchBook(title, author);
                if (found) {
                    printf("Tìm thấy: %s | %s | %d\n", found->Title, found->Author, found->Quantity);
                } else {
                    printf("Không tìm thấy sách!\n");
                }
                break;
            case 4:
                printf("Nhập tiêu đề sách cần xóa: ");
                fgets(title, sizeof(title), stdin); title[strcspn(title, "\n")] = 0;
                printf("Nhập tác giả: ");
                fgets(author, sizeof(author), stdin); author[strcspn(author, "\n")] = 0;
                deleteBook(title, author);
                printf("Đã xóa (nếu tồn tại)!\n");
                break;
            case 5:
                printf("Nhập tên file để lưu: ");
                fgets(fileName, sizeof(fileName), stdin); fileName[strcspn(fileName, "\n")] = 0;
                saveToFile(fileName);
                break;
            case 6:
                printf("Nhập tên file để đọc: ");
                fgets(fileName, sizeof(fileName), stdin); fileName[strcspn(fileName, "\n")] = 0;
                loadBooksFromFile(fileName);
                printf("Đã đọc sách từ file!\n");
                break;
            case 0:
                printf("Thoát chương trình.\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ!\n");
        }
    } while (choice != 0);

    return 0;
}
