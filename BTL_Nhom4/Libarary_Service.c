#include "Libarary_Service.h"
#include <stdio.h>
#include <conio.h> // Thư viện cho hàm _getch()

void ClearScreen(){
    printf("\033[H\033[J");
}
void String(){
    printf("Chao mung ban da den voi thu vien ABC\n");
    printf("1. ...\n2. ...\n3. ....\n4. ...\n");
}
void Option(){
    String();
    printf("Chon dich vu ban can: ");
    char c;
    scanf("%c",&c);
    while(c < '1' || c > '9'){
        ClearScreen();
        String();
        printf("Lua chon cua ban khong hop le, vui long chon lai: ");
        scanf("%c",&c);
    }   
    return;
}
