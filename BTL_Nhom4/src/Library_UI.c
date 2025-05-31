#include <stdio.h>
#include <stdlib.h>
#include "Library_Service.h"

void ClearScreen(){
    printf("\033[H\033[J");
}

void LibraryUI() {
    int choice;
    do {
        ClearScreen();
        printf("=========== CHUONG TRINH QUAN LY THU VIEN ===========\n");
        printf("1. Dang nhap voi vai tro NGUOI DUNG\n");
        printf("2. Dang nhap voi vai tro QUAN LY\n");
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1:
                UserUI();
                break;
            case 2:
                AdminUI();
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
