#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Library_Service.h"
#include "Book.h"
#include "Member.h"
#include "Borrowing.h"

void menuBooks();
void menuMembers();
void menuBorrowing();

void AdminUI() {
    int choice;
    do {
        ClearScreen();
        printf("=========== CHUONG TRINH QUAN LY THU VIEN CHO ADMIN ===========\n");
        printf("1. Quan ly sach\n");
        printf("2. Quan ly thanh vien\n");
        printf("3. Quan ly muon/tra sach\n");
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1:
                menuBooks();
                break;
            case 2:
                menuMembers();
                break;
            case 3:
                menuBorrowing();
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai!\n");
                system("pause");
        }
    } while (choice != 0);
}

/* QUẢN LÝ SÁCH */
void menuBooks() {
    int choice;
    char title[200], author[200];
    Book book;

    do {
        ClearScreen();
        printf("========== QUAN LY SACH ==========\n");
        printf("1. Them sach\n");
        printf("2. Tim sach\n");
        printf("3. Xoa sach\n");
        printf("4. Hien thi toan bo sach\n");
        printf("0. Quay lai\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Nhap tieu de: "); fgets(book.Title, 200, stdin); book.Title[strcspn(book.Title, "\n")] = '\0';
                printf("Nhap tac gia: "); fgets(book.Author, 200, stdin); book.Author[strcspn(book.Author, "\n")] = '\0';
                printf("Nhap so luong: "); scanf("%d", &book.Quantity); getchar();
                book.queue0 = book.queue1 = NULL;
                insertBook(book);
                printf("Da them sach.\n");
                break;
            case 2:
                printf("Nhap tieu de: "); fgets(title, 200, stdin); title[strcspn(title, "\n")] = '\0';
                printf("Nhap tac gia: "); fgets(author, 200, stdin); author[strcspn(author, "\n")] = '\0';
                Book *found = searchBook(title, author);
                if (found) printBook(found);
                else printf("Khong tim thay sach.\n");
                break;
            case 3:
                printf("Nhap tieu de: "); fgets(title, 200, stdin); title[strcspn(title, "\n")] = '\0';
                printf("Nhap tac gia: "); fgets(author, 200, stdin); author[strcspn(author, "\n")] = '\0';
                Book* book = searchBook(title,author);
                if (book == NULL)
                    printf("Sach khong ton tai\n");
                else if (book->queue0 != NULL || book->queue1 != NULL)
                    printf("Hang doi van con nguoi, khong the xoa sach\n");
                else{
                    deleteBook(title, author);
                    printf("Da xoa sach\n");
                }
                break;
            case 4:
                displayAllBooks();
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le.\n");
        }
        system("PAUSE");
    } while (choice != 0);
}

/* QUẢN LÝ THÀNH VIÊN */
void menuMembers() {
    int choice;
    Member member;

    do {
        ClearScreen();
        printf("========== QUAN LY THANH VIEN ==========\n");
        printf("1. Them thanh vien\n");
        printf("2. Tim thanh vien\n");
        printf("3. Xoa thanh vien\n");
        printf("0. Quay lai\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Nhap CCCD: "); fgets(member.IdentifyID, 13, stdin); member.IdentifyID[strcspn(member.IdentifyID, "\n")] = '\0';
                printf("Nhap ten: "); fgets(member.Name, 100, stdin); member.Name[strcspn(member.Name, "\n")] = '\0';
                member.CurrentQuantity = 0;
                InputMember(&member);
                printf("Da them thanh vien.\n");
                break;
            case 2:
                printf("Nhap CCCD: ");
                char id[13];
                fgets(id, 13, stdin); id[strcspn(id, "\n")] = '\0';
                Member *found = SearchMember(id);
                if (found)
                    printf("Ho ten: %s | So sach dang muon: %d\n", found->Name, found->CurrentQuantity);
                else
                    printf("Khong tim thay thanh vien.\n");
                break;
            case 3:
                DeleteMember();
                printf("Da xoa thanh vien (neu ton tai).\n");
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le.\n");
        }
        system("pause");
    } while (choice != 0);
}

/* QUẢN LÝ MƯỢN SÁCH */
void menuBorrowing() {
    int choice;
    char code[7], id[13], title[200], author[200];
    time_t t = time(NULL);
    struct tm now = *localtime(&t);

    do {
        ClearScreen();
        printf("========== QUAN LY MUON/TRA SACH ==========\n");
        printf("1. Danh sach muon\n");
        printf("2. Cac sach da duoc tra\n");
        printf("0. Quay lai\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                displayAllBorrowing();
                break;
            case 2:
                FILE *f = fopen("data/returned.csv","r");
                if (!f) {
                    printf("Khong the mo file returned.csv de doc!\n");
                    return;
                }
                char line[500];
                printf("%s | %s | %s | %s | %s | %s\n",
                "Code", "CCCD", "Tieu de", "Tac gia", "Ngay muon", "Ngay tra");
                while (fgets(line, sizeof(line), f)){
                    char *p = line;
                    while (*p) {
                        if (*p == ';') *p = '|';
                        p++;
                    }
                    printf("%s\n", line);
                }
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le.\n");
        }
        system("pause");
    } while (choice != 0);
}
