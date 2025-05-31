#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Member.h"
#include "Book.h"
#include "Borrowing.h"
#include "Queue.h"
#include "Library_Service.h"

/* KHAI BÁO HÀM */
void Tra_Cuu_Sach(char* title, char* author);
void Muon_Sach(char* id, char* title, char* author);
void Tra_Cuu_Hang_Doi(char* title, char* author);
void Dang_Ky_Hang_Doi(char* id,char* title,char* author);
void Dang_Ky_Thanh_Vien(char* id);
void Tra_Sach(char* code);

/* HÀM GIAO DIỆN NGƯỜI DÙNG */
void UserUI() {
    int choice;
    char id[13], title[200], author[200], code[7];
    time_t t = time(NULL);
    struct tm now = *localtime(&t);

    do {
        ClearScreen();
        printf("========== NGUOI DUNG ==========\n");
        printf("1. Xem toan bo sach\n");
        printf("2. Tra cuu sach\n");
        printf("3. Dang ky muon sach\n");
        printf("4. Dang ky vao hang doi\n"); // QueueQueue
        printf("5. Tra cuu trang thai muon\n");
        printf("6. Xem hang doi muon sach\n");
        printf("7. Dang ky thanh vien\n");
        printf("8. Tra sach\n");
        printf("0. Quay lai\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                displayAllBooks();
                break;
            case 2: 
                Tra_Cuu_Sach(title, author);
                break;
            case 3:
                Muon_Sach(id, title, author);
                break;
            case 4:
                Dang_Ky_Hang_Doi(id, title, author);
                break;
            case 5:
                printf("Nhap ma phieu muon: ");
                fgets(code, 7, stdin); code[strcspn(code, "\n")] = '\0';
                AVLNode *node = searchBorrowingTicket(code);
                if (node) {
                    Borrowing *b = (Borrowing *)node->data;
                    printf("CCCD: %s | Sach: %s - %s | Ngay muon: %02d/%02d/%04d\n", 
                           b->IdentifyID, b->Title, b->Author,
                           b->Start.tm_mday, b->Start.tm_mon + 1, b->Start.tm_year + 1900);
                } else {
                    printf("Khong tim thay phieu.\n");
                }
                system("PAUSE");
                break;
            case 6:
                Tra_Cuu_Hang_Doi(title,author);
                break;
            case 7:
                Dang_Ky_Thanh_Vien(id);
                break;
            case 8:
                Tra_Sach(code);
                break;
            case 0:
                return;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (choice != 0);
}

/* TRA CỨU SÁCH */
void Tra_Cuu_Sach(char* title, char* author){
    char c = '\0';
    do{
        if (c != '\0')
            getchar();
        ClearScreen();
        printf("========== TRA CUU SACH ==========\n");
        printf("Nhap tieu de sach: "); fgets(title, 200, stdin); title[strcspn(title, "\n")] = '\0';
        printf("Nhap ten tac gia: "); fgets(author, 200, stdin); author[strcspn(author, "\n")] = '\0';
        Book* book = searchBook(title,author);
        if (book == NULL){
            printf("Khong tim thay sach\n");
        }
        else{
            printf("Da tim thay sach:\n");
            printf("Ten sach: %s\nTen tac gia: %s\n",
            book->Title, book->Author);
        }
        printf("Ban co muon tiep tuc Tra Cuu Sach ?\n(Nhap Y/y de tiep tuc, ky tu bat ky de thoat): ");
        scanf("%c",&c);
    }while(c == 'Y' || c == 'y');
}

/* ĐĂNG KÝ MƯỢN SÁCH */
void Muon_Sach(char* id, char* title, char* author) {
    ClearScreen();
    printf("========== DANG KY MUON SACH ==========\n");
    printf("Nhap CCCD: "); fgets(id, 13, stdin); id[strcspn(id, "\n")] = '\0';
    getchar();
    Member* member = SearchMember(id);

    // Kiểm tra thành viên có tồn tại hay không 
    if (member == NULL){
        printf("Ban chua dang ky thanh vien, vui long dang ky thanh vien de co the muon sach\n");
        system("PAUSE");
        return;
    }
    // Kiểm tra số lượng sách đang  mượn 
    if (member->CurrentQuantity == 10)
    {
        printf("So luong sach ban muon da toi muc cho phep (10 cuon)\nVui long tra sach de co the muon them\n");
        system("PAUSE");
        return;
    }
    
    printf("Nhap tieu de sach: "); fgets(title, 200, stdin); title[strcspn(title, "\n")] = '\0';
    printf("Nhap ten tac gia: "); fgets(author, 200, stdin); author[strcspn(author, "\n")] = '\0';
    Book* book = searchBook(title,author);

    // Kiểm tra sach có tồn tại hay không
    if (book == NULL){
        printf("Sach ban dang tim khong ton tai, vui long tra cuu ky truoc khi muon\n");
        system("PAUSE");
        return;
    }
    // Kiểm tra có ai trong hàng đợi đã được ấn định mà chưa đến lấy sau 3 ngày 
    Queue* queue = getfront(book); // Lấy thông tin người đầu tiên trong hàng đợi
    if (queue != NULL){
        time_t t = time(NULL);
        // Xóa những người quá hạn đến lấy (7 ngày)
        do{
            struct tm decidedorrow = queue->DecideBorrow;
            time_t t1 = mktime(&decidedorrow);
            double seconds = difftime(t, t1);
            if ((int)seconds/(60 * 60 * 24) >= 7){
                book->Quantity++;
                deleteNode(book); // Xóa người quá hạn đến lấy ra khỏi hàng đợi 
                queue = getfront(book);
            }
            else break;
        }while(queue != NULL);
    }
    // Kiểm tra lại trong hàng đợi có ai chưa có sách được ấn đinh không
    if (book->Quantity > 0){
        time_t t = time(NULL);
        struct tm t2 = *localtime(&t);
        queue = book->queue1;
        while(queue != NULL && book->Quantity > 0){
            if (queue->DecideBorrow.tm_year == 0){
                book->Quantity--;
                queue->DecideBorrow = t2; // Lấy ngày hiện tại 
            }
            queue = queue->next;
        }
        queue = book->queue0;
        while(queue != NULL && book->Quantity > 0){
            if (queue->DecideBorrow.tm_year == 0){
                book->Quantity--;
                queue->DecideBorrow = t2; // Lấy ngày hiện tại 
            }
            queue = queue->next;
        }
    }
    // Kiểm tra số lượng sách còn lại
    if (book->Quantity == 0){
        printf("Hien thu vien da het dau sach nay\nNeu ban muon dang ky hang doi, vui long chọn 'Dang ky vao hang doi' o giao dien");
        system("PAUSE");
        return;
    }
    
    struct tm now;
    printf("Nhap ngay, thang, nam dang ky muon sach:\n(Yeu cau nhap dung theo cau truc ngay/thang/nam)\n");
    scanf("%d/%d/%d", &now.tm_mday, &now.tm_mon, &now.tm_year);
    now.tm_mon = now.tm_mon -1;
    now.tm_year = now.tm_year - 1900;
    createBorrowingTicket(id, title, author, now);
    printf("Ban da muon sach thanh cong!!\n");
    printf("Ma muon sach cua ban la: %s\n",currentCode);
    system("PAUSE");
    return;
}

/* TRA CỨU HÀNG ĐỢI */
void Tra_Cuu_Hang_Doi(char* title, char* author){
    char c = '\0';
    do{
        if (c != '\0')
            getchar();
        ClearScreen();
        printf("========== TRA CUU HANG DOI ==========\n");
        printf("Nhap tieu de sach: "); fgets(title, 200, stdin); title[strcspn(title, "\n")] = '\0';
        printf("Nhap ten tac gia: "); fgets(author, 200, stdin); author[strcspn(author, "\n")] = '\0';
        Book* book = searchBook(title,author);
        if (book == NULL){
            printf("Khong tim thay sach\n");
        }
        else{
            printf("Da tim thay sach:\n");
            printf("Ten sach: %s\nTen tac gia: %s\n",
            book->Title, book->Author);
            traverse(title, author);
        }
        printf("Ban co muon tiep tuc Tra Cuu Hang Doi?\n(Nhap Y/y de tiep tuc, ky tu bat ky de thoat): ");
        scanf("%c",&c);
    }while(c == 'Y' || c == 'y');
}

/* ĐĂNG KÝ VAO HÀNG ĐỢI */
void Dang_Ky_Hang_Doi(char* id,char* title,char* author){
    ClearScreen();
    printf("========== DANG KY HANG DOI ==========\n");
    printf("Nhap CCCD: "); fgets(id, 13, stdin); id[strcspn(id, "\n")] = '\0';
    getchar();
    Member* member = SearchMember(id);

    // Kiểm tra thành viên có tồn tại hay không 
    if (member == NULL){
        printf("Ban chua dang ky thanh vien, vui long dang ký thanh vien de co the muon sach\n");
        system("PAUSE");
        return;
    }

    printf("Nhap tieu de sach: "); fgets(title, 200, stdin); title[strcspn(title, "\n")] = '\0';
    printf("Nhap ten tac gia: "); fgets(author, 200, stdin); author[strcspn(author, "\n")] = '\0';
    
    Book* book = searchBook(title,author);
    if (book == NULL){
        printf("Khong tim thay sach. Vui long tra cuu ky lai dau sach truoc ky dang ky\n");
        system("PAUSE");
        return;
    }
    if (book->Quantity > 0){
        printf("Sach van con, vui long chuyen qua dich vu muon sach\n");
        system("PAUSE");
        return;
    }
    printf("Ban co muon vao hang doi uu tien khong?\n");
    printf("(Nhap Y/y de xac nhan, ky tu bat ky de khong xac nhan)\n");
    char c;
    scanf("%c", &c);
    bool order;
    if (c == 'Y' || c == 'y')
        order = 1;
    else 
        order = 0;
    insertNode(id, title, author, order);
    printf("Ban da duoc them vao hang doi thanh cong\n");
    system("PAUSE");
    return;
}

/* ĐĂNG KÝ THÀNH VIÊN */
void Dang_Ky_Thanh_Vien(char* id){
    ClearScreen();
    printf("========== DANG KY THANH VIEN ==========\n");
    printf("Nhap CCCD: "); fgets(id, 13, stdin); id[strcspn(id, "\n")] = '\0';
    getchar();
    Member* member = SearchMember(id);

    // Kiểm tra thành viên có tồn tại hay không 
    if (member != NULL){
        printf("Ban da dang ky thanh vien, vui long chon dich vu khac\n");
        system("PAUSE");
        return;
    }
    member = (Member*)malloc(sizeof(Member)); // Cấp bộ nhớ 
    strcpy(member->IdentifyID, id);
    
    printf("Nhap Ho va Ten: ");
    fgets(member->Name,199,stdin); id[strcspn(id, "\n")] = '\0';
    
    InputMember(member);
    printf("Da them thanh vien thanh cong\n");
    system("PAUSE");
    return;
}

/* TRẢ SÁCH */
void Tra_Sach(char* code){
    ClearScreen();
    printf("========== TRA SACH ==========\n");
    printf("Nhap ma phieu muon: ");
    fgets(code, 7, stdin); code[strcspn(code, "\n")] = '\0';
    AVLNode *node = searchBorrowingTicket(code);

    if (node == NULL){
        printf("Khong tim thay ma muon\n");
        system("PAUSE");
        return;
    }
    Borrowing* borrow = (Borrowing*)node->data;
    Book* book = searchBook(borrow->Title,borrow->Author);

    // Xóa mã mượn và đưa vào returned.csv 
    deleteBorrowingTicket(code);
    
    // Kiểm tra còn ai trong hàng đợi ko để ấn định sách 
    Queue* queue = getfront(book); // Lấy thông tin người đầu tiên trong hàng đợi
    time_t t = time(NULL);
    if (queue != NULL){
        // Xóa những người quá hạn đến lấy (7 ngày)
        do{
            struct tm decidedorrow = queue->DecideBorrow;
            time_t t1 = mktime(&decidedorrow);
            double seconds = difftime(t, t1);
            if ((int)seconds/(60 * 60 * 24) >= 7){
                book->Quantity++;
                deleteNode(book); // Xóa người quá hạn đến lấy ra khỏi hàng đợi 
                queue = getfront(book);
            }
            else break;
        }while(queue != NULL);
    }
    // Kiểm tra lại tỏng hàng đợi có ai chưa có sách được ấn đinh không
    if (book->Quantity > 0){
        struct tm t2 = *localtime(&t);
        queue = book->queue1;
        while(queue != NULL && book->Quantity > 0){
            if (queue->DecideBorrow.tm_year == 0){
                book->Quantity--;
                queue->DecideBorrow = t2; // Lấy ngày hiện tại 
            }
            queue = queue->next;
        }
        queue = book->queue0;
        while(queue != NULL && book->Quantity > 0){
            if (queue->DecideBorrow.tm_year == 0){
                book->Quantity--;
                queue->DecideBorrow = t2; // Lấy ngày hiện tại 
            }
            queue = queue->next;
        }
    }
    system("PAUSE");
}