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
        printf("=========== CHUONG TRINH QUAN LY THU VIEN ===========\n");
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
                deleteBook(title, author);
                printf("Da xoa sach (neu ton tai).\n");
                break;
            case 4:
                displayAllBooks();
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le.\n");
        }
        system("pause");
    } while (choice != 0);
}

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

void menuBorrowing() {
    int choice;
    char code[7], id[13], title[200], author[200];
    time_t t = time(NULL);
    struct tm now = *localtime(&t);

    do {
        ClearScreen();
        printf("========== QUAN LY MUON/TRA SACH ==========\n");
        printf("1. Tao phieu muon\n");
        printf("2. Tim phieu muon\n");
        printf("3. Tra sach\n");
        printf("0. Quay lai\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Nhap CCCD: "); fgets(id, 13, stdin); id[strcspn(id, "\n")] = '\0';
                printf("Nhap tieu de: "); fgets(title, 200, stdin); title[strcspn(title, "\n")] = '\0';
                printf("Nhap tac gia: "); fgets(author, 200, stdin); author[strcspn(author, "\n")] = '\0';
                createBorrowingTicket(id, title, author, now);
                printf("Da tao phieu muon.\n");
                break;
            case 2:
                printf("Nhap ma phieu: "); fgets(code, 7, stdin); code[strcspn(code, "\n")] = '\0';
                AVLNode *ticket = searchBorrowingTicket(code);
                if (ticket) {
                    Borrowing *b = (Borrowing *)ticket->data;
                    printf("Ma: %s | CCCD: %s | Sach: %s - %s\n", b->Code, b->IdentifyID, b->Title, b->Author);
                } else {
                    printf("Khong tim thay phieu muon.\n");
                }
                break;
            case 3:
                printf("Nhap ma phieu muon: "); fgets(code, 7, stdin); code[strcspn(code, "\n")] = '\0';
                deleteBorrowingTicket(code);
                printf("Da tra sach.\n");
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le.\n");
        }
        system("pause");
    } while (choice != 0);
}
