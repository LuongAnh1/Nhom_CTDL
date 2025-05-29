#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>   /* _getch() – dùng khi biên dịch trên Windows */
#include <ctype.h>

#include "Member.h"
#include "Data.h"
#include "AVL_Tree.h"
#include "Borrowing.h"
#include "Library_Service.h"
#include "hash.h"
#include "Book.h"
#include "Queue.h"


/* =============================================================
   KHAI BÁO HÀM (PROTOTYPE)
   ============================================================= */
void   Start();
void   ClearScreen();
void   QuayLai();

/* menu khách & quản lý */
void   ThaoTacKhachHang();
void   ThaoTacQuanLy();

/* nghiệp vụ sách */
void   TraCuuSach(int action);   /* action: 1 = khách, 2 = quản lý */
void   MuonSach(int action);     /* action: 1 = đã có thông tin sách, 2 = chưa chọn sách */
void   TraSach  (int action);

/* hàm kiểm tra/giả lập dữ liệu – hiện trả về true hoặc giá trị cố định */
bool   TimSach(const char *key1, const char *key2);
int    SoLuongSach(); /* giả lập số lượng sách còn trong thư viện */
bool   KiemTraThanhVien(const char *id);
int    GetCurrentQuantity(const char *id);
bool   KiemTraMatKhau(const char *pass);
bool   KiemTraMaMuon(const char *borrowId);
bool   KiemTraThuocThuVien();
void   addMember();

/* quản lý kho sách */
void   ThemDauSach();
void   XoaDauSach();
void   BaoCaoHoatDong();
void   ThongTinSach();
/* ============================================================= */

/* -------------------- HÀM TIỆN ÍCH -------------------------- */
void ClearScreen() {
    printf("\033[H\033[J");
}

void QuayLai() {
    printf("\nNhan phim bat ky de quay lai...");
    _getch();
}

/* -------------------- HÀM KIỂM TRA GIẢ LẬP ------------------ */
bool KiemTraMatKhau(const char *pass)       { return strcmp(pass, "2701") == 0; }
bool TimSach(char *key1, char *key2){
    Book* book = searchBook(key1, key2);
    if (book == NULL) return false;
    else return true;
}
int  SoLuongSach(/*Member* member*/)                          { /*return member->CurrentQuantity;*/return 0;   }
bool KiemTraThanhVien(char* IdentifyID) { 
    Member *member = SearchMember(IdentifyID);
    if (member != NULL)
        return true; // Thành viên đã tồn tại
    else 
        return false; // Thành viên không tồn tại 
}
int  GetCurrentQuantity(char *id){
    Member* member = SearchMember(id);
    return member->CurrentQuantity;
}
bool KiemTraMaMuon(const char *borrowId)    { (void)borrowId; return true; }
bool KiemTraThuocThuVien()                   { return true; }
void addMember() {
    ClearScreen();
    puts("---------- THEM THANH VIEN ----------");
    puts("Nhap Can cuoc cong dan: ");
    char IdentifyID[13];
    scanf("%s", IdentifyID); getchar();
    // Kiểm tra có nhập cccd đúng không
    while(sizeof(IdentifyID)!=12){
        ClearScreen();
        puts("---------- THEM THANH VIEN ----------");
        puts("Nhap lai can cuoc cong dan, nhap 0 de thoat");
        puts("Nhap Can cuoc cong dan: ");
        char IdentifyID[13];
        scanf("%s", IdentifyID); getchar();
        if(*IdentifyID == '0') return;
    }
    
    puts("Nhap ho ten: ");
    char Name[200];
    fgets(Name, sizeof Name, stdin);
    Name[strcspn(Name, "\n")] = '\0';
    trim(Name);

    Member *newMember = (Member*)malloc(sizeof(Member));
    strcpy(newMember->IdentifyID, IdentifyID);
    strcpy(newMember->Name, Name);
    newMember->CurrentQuantity = 0; /* Giả lập số lượng sách đã mượn là 0 */
    InputMember(newMember); /* Giả lập thêm thành viên vào danh sách */
    
    puts("Them thanh vien moi thanh cong!"); 
}

/* -------------------- MENU GỐC ------------------------------ */
void Start() {
    ClearScreen();
    puts("Chao mung ban da den voi thu vien ABC");
    puts("---------------------------------------");
    puts("Ban muon truy cap voi tu cach la?");
    puts("1. Khach hang");
    puts("2. Nguoi quan ly");
    puts("3. Thoat chuong trinh");
    printf("Nhap lua chon: ");

    int user;
    scanf("%d", &user);
    getchar(); /* xóa ký tự '\n' còn lại trong bộ đệm */

    switch (user) {
        case 1: ThaoTacKhachHang(); break;
        case 2: {
            char pass[32];
            printf("Nhap mat khau: ");
            fgets(pass, sizeof pass, stdin);
            pass[strcspn(pass, "\n")] = '\0';
            if (KiemTraMatKhau(pass)) ThaoTacQuanLy();
            else { puts("Sai mat khau!"); QuayLai(); Start(); }
            break;
        }
        case 3:{
            // Tải dữ liệu về file .csv và thoát chương trình
        }
        default:
            puts("Lua chon khong hop le!");
            QuayLai();
            Start(); // Quay lại Start 
    }
}

/* -------------------- MENU KHÁCH HÀNG ----------------------- */
void ThaoTacKhachHang() {
    int action;
    while (1) {
        ClearScreen();
        puts("----- MENU KHACH HANG -----");
        puts("1. Tra cuu sach");
        puts("2. Muon sach");
        puts("3. Tra sach");
        puts("0. Quay lai");
        printf("Nhap lua chon: ");

        if (scanf("%d", &action) != 1) { fflush(stdin); continue; }
        getchar();

        switch (action) {
            case 1: TraCuuSach(1); break;
            case 2: MuonSach(2);   break;
            case 3: TraSach(1);    break;
            case 0: Start();       /* Quay lai Start() */
            default: puts("Lua chon khong hop le!"); QuayLai(); break;
        }
    }
}

/* -------------------- MENU QUẢN LÝ -------------------------- */
void ThaoTacQuanLy() {
    int action;
    while (1) {
        ClearScreen();
        puts("----- MENU QUAN LY -----");
        puts("1. Them dau sach");
        puts("2. Xoa dau sach");
        puts("3. Bao cao hoat dong");
        puts("4. Tra cuu sach");
        puts("5. Thong tin sach toan bo thu vien");
        puts("0. Quay lai");
        printf("Nhap lua chon: ");

        if (scanf("%d", &action) != 1) { fflush(stdin); continue; }
        getchar();

        switch (action) {
            case 1: ThemDauSach();      break;
            case 2: XoaDauSach();       break;
            case 3: BaoCaoHoatDong();   break;
            case 4: TraCuuSach(2);      break;
            case 5: ThongTinSach();     break;
            case 0: Start();            /* Quay lai Start() */
            default: puts("Lua chon khong hop le!"); QuayLai(); break;
        }
    }
}

/* -------------------- TRA CỨU SÁCH (CHUNG) ------------------ */
void TraCuuSach(int action) {
    ClearScreen();
    puts("---------- TRA CUU SACH ----------");
    char TenSach[200], TacGia[200];
    printf("Nhap ten sach : ");
    fgets(TenSach, sizeof TenSach, stdin);
    TenSach[strcspn(TenSach, "\n")] = '\0';
    trim(TenSach); // Xóa ký tự trắng đầu và cuối

    printf("Nhap ten tac gia: ");
    fgets(TacGia, sizeof TacGia, stdin);
    TacGia[strcspn(TacGia, "\n")] = '\0';
    trim(TacGia); // Xóa ký tự trắng đầu và cuối

    if (!TimSach(TenSach, TacGia)) {
        puts("Khong tim thay sach!");
        QuayLai();
        return;
    }

    /* Hiển thị thông tin sách */
    ClearScreen();
    printf("Tim thay sach\n");
    Book* book = searchBook(TenSach, TacGia);
    printf("Ten sach: %s\nTen tac gia: %s\nSo luong con lai: %d\n",
            book->Title, book->Author, book->Quantity);
    
    /* Nếu là khách hàng (action==1) hỏi có muốn mượn không */
    if (action == 1) {
        char choice;
        printf("Ban co muon muon sach khong? (Y/N): ");
        scanf(" %c", &choice);
        getchar();
        if (choice == 'Y' || choice == 'y') { 
            MuonSach(1);
            return;
        }
    }
    QuayLai();
}

/* -------------------- Mượn Sách ----------------------------- */
void MuonSach(int action) {
    /* action==2 -> chưa có thông tin sách nên tra cứu trước */
    if (action == 2) {
        TraCuuSach(1); /* sau khi tra cứu xong sẽ hỏi mượn luôn */
        return; /* Gọi return sẽ thoát hàm luôn mà không thực hiện các lệnh phía sau*/
    }

    ClearScreen();
    puts("---------- MUON SACH ----------\n");

    char id[13];
    printf("Nhap CCCD: ");
    scanf("%13s", id); getchar();

    if (!KiemTraThanhVien(id)) {
        puts("Khong tim thay thanh vien!");
        char choice;
        printf("Dang ky thanh vien moi? (Y/N): ");
        scanf(" %c", &choice); getchar();
        if (choice == 'Y' || choice == 'y') addMember();
        QuayLai();
        return; 
    }
    /*Nếu tìm thấy thành viên sẽ thực hiện lệnh dưới   */
    if (GetCurrentQuantity(id) >= 10) {
        puts("Ban da muon toi da 10 cuon!");
        printf("Ban co muon tra sach khong? (Y/N): ");
        char choice;
        scanf(" %c", &choice); getchar();
        if (choice == 'Y' || choice == 'y') {
            TraSach(1);
            return;
        } 
        else if (choice == 'N' || choice == 'n') {
            puts("Khong tra sach!");
        }
        else{
            puts("Ky tu khong hop le");
        }
        QuayLai();
        return;
    }

    if (SoLuongSach() == 0) {
        puts("Thu vien da het sach tren!");
        printf("Ban co muon them vao hang doi khong? (Y/N): ");
        char choice;
        scanf(" %c", &choice); getchar();
        if (choice == 'Y' || choice == 'y') {
            puts("Da them vao hang doi!");
            printf("Ban co muon nang muc uu tien khong? (Y/N): ");
            scanf(" %c", &choice); getchar();
            if (choice == 'Y' || choice == 'y') {
                puts("Da nang muc uu tien!");
            } else {
                puts("Khong nang muc uu tien!");
            }
        } else {
            puts("Khong them vao hang doi!");
        }
        QuayLai();
        return;
    }
    /* Giả lập sinh mã mượn sách và cập nhật */
    puts("Muon sach thanh cong!");
    QuayLai();
}

/* -------------------- TRA SÁCH ------------------------------ */
void TraSach(int action) {
    (void)action; /* chưa dùng thêm */
    ClearScreen();
    puts("---------- TRA SACH ----------\n");

    char borrowId[16];
    printf("Nhap ma muon sach: ");
    scanf("%15s", borrowId); getchar();

    if (!KiemTraMaMuon(borrowId)) {
        puts("Ma muon sach khong ton tai!");
        QuayLai();
        return;
    }
    /*Cập nhật thông tin trả sách*/
    if (!KiemTraThuocThuVien()) {
        puts("Sach khong thuoc thu vien!");
        QuayLai();
        return;
    }
    /*Ghi lại dữ liệu*/

    puts("Tra sach thanh cong!");
    QuayLai();
}

/* -------------------- QUẢN LÝ KHO SÁCH ---------------------- */
void ThemDauSach() {
    ClearScreen();
    puts("[Them dau sach] Dang phat trien...");
    QuayLai();
}

void XoaDauSach() {
    ClearScreen();
    puts("[Xoa dau sach] Dang phat trien...");
    QuayLai();
}

void BaoCaoHoatDong() {
    ClearScreen();
    puts("[Bao cao hoat dong] Dang phat trien...");
    QuayLai();
}

void ThongTinSach() {
    ClearScreen();
    puts("[Thong tin sach] Dang phat trien...");
    QuayLai();
}
