#include "Libarary_Service.h"
#include <stdio.h>
#include <conio.h> // Thư viện cho hàm _getch()

bool KiemTraMatKhau(int n) {
    if (n == ahihi) return 1;
    else return 0;
}
void ClearScreen(){
    printf("\033[H\033[J");
}
void Start(){
    ClearScreen();
    printf("Chao mung ban da den voi thu vien ABC\n");
    printf("-------------------------------\n");
    printf("Ban muon truy cap voi tu cach la?\n ")
    printf("1. Khach hang                   2. Nguoi quan ly");
    printf("Nhap lua chon: ");
    int user;
    scanf("%d", &user); //Biến đại diện cho người dùng
    ClearScreen();
    switch (user) {
        case 1:
            ThaoTacKhachHang();
            break;
        case 2:
            int pass;
            printf("Nhap mat khau: ");
            scanf("%d", &pass);
            if (KiemTraMatKhau(pass)) {
                ThaoTacQuanLy();
            }
            else {
                printf("Mat khau khong dung!\n");
                printf("Nhan phim bat ky de quay lai!");
                _getch(); // Chờ người dùng nhấn phím
                Start();
            }
            break;
        default:
            printf("Lua chon khong hop le!\n");
            printf("Nhan phim bat ky de quay lai!");
            _getch(); // Chờ người dùng nhấn phím
            Start();
    }
}

void ThaoTacKhachHang(){
    int action;
    ClearScreen();
    printf("Chon thao tac thuc hien: \n");
    printf("1. Tra cuu sach\n");
    printf("2. Muon sach\n");
    printf("3. Tra sach \n");
    printf("0. Quay lai!\n");
    printf("Nhap lua chon: "); scanf("%d", &action);
    switch (action) {
        case 1:
            TraCuuSach(action); //Truyền tham số để phân biệt giữa mượn sách và tra cứu
            break;
        case 2:
            MuonSach(action);
            break;
        case 3:
            traSach(action);
            break;
        case 0:
            Start();
            break;
        default:
            {
                printf("Lua chon khong hop le!\n");
                printf("Nhan phim bat ky de quay lai!");
                _getch(); // Chờ người dùng nhấn phím
                ThaoTacKhachHang();
            }
    }    
}        

void TraCuuSach(int *n){
    ClearScreen();
    printf("----------TRA CUU SACH---------\n");
    printf("Ban muon tim sach theo: \n");
    printf("1. Ten sach\n");
    printf("2. Ten tac gia\n");
    printf("0. Quay lai\n");
    int action;
    printf("Nhap lua chon: "); scanf("%d", &action);
    ClearScreen();
    switch (action) {
        case 1:
            TimSachTheoTen(n); //Hàm tìm sách theo tên in ra thông tin sách
            if (n == 1) {    // n = 1 là tới thẳng từ ThaoTacKhachHang, nên hỏi có muốn mượn sách không
                printf("\nBan co muon muon sach khong? (Y/N): ");
                char choice;
                scanf(" %c", &choice);
                if (choice == 'Y' || choice == 'y') {
                    MuonSach(n); // Gọi hàm mượn sách với n = 1
                }
                else {
                    printf("Ban da huy muon sach!\n");
                    printf("Nhan phim bat ky de quay lai!");
                    _getch(); // Chờ người dùng nhấn phím
                    Start(); // Quay lại màn hình chính
                }
            }
            // Nếu n khác 1 tức là tới từ mượn sách nên chỉ cần in thông tin sách 
            break;
        case 2:
            TimSachTheoTacGia(n);
            if (n == 1) { //Tương tự như trên
                printf("\nBan co muon muon sach khong? (Y/N): ");
                char choice;
                scanf(" %c", &choice);
                if (choice == 'Y' || choice == 'y') {
                    MuonSach(n); // Gọi hàm mượn sách với n = 1
                }
                else {
                    printf("\nBan da huy muon sach!\n");
                    printf("Nhan phim bat ky de quay lai!");
                    _getch(); // Chờ người dùng nhấn phím
                    Start(); // Quay lại
            }
            
        case 0:
            ThaoTacKhachHang();
            break;
        default:
            {
                printf("Lua chon khong hop le!\n");
                printf("Nhan phim bat ky de quay lai!");
                _getch(); // Chờ người dùng nhấn phím
                TraCuuSach(n);
            }
        }    
    }
}

void TimSachTheoTen(int *n){
    char Title[50];
    ClearScreen();
    printf("----------TRA CUU SACH-----------\n \n");
    printf("-------TIM SACH THEO TEN--------\n");
    printf("Nhap ten sach: ");
    scanf("%s", Title);
    unsigned int index = hash(Title); // Tính toán chỉ số băm
    AVLNode *result = searchAVL(HashTableBook[index], Title, compareString); // Tìm kiếm trong bảng băm
    if (result != NULL) {
        Book *book = (Book *)result->data; // Lấy dữ liệu sách
        printf("Ten sach: %s, Ten tac gia: %s, So luong: %d\n", book->Title, book->Author, book->Quantity);
    } else {
        printf("Khong tim thay sach\n");
        if (n == 2) { // n = 2 tức được gọi từ MuonSach, nếu khác 2 thì không cần hỏi
            printf("Ban co muon them yeu cau vao hang doi khong? (Y/N): ");
            char choice;
            scanf(" %c", &choice);
            if (choice == 'Y' || choice == 'y') {
                // Thêm yêu cầu vào hàng đợi
                printf("Da them yeu cau vao hang doi\n");
                // UwU tien?
                
            } else {
                printf("Ban da huy yeu cau!\n");
                printf("Nhan phim bat ky de quay lai!");
                _getch(); // Chờ người dùng nhấn phím
                ThaoTacKhachHang();
            }
        }
        else {
            printf("Bam phim bat ky de quay lai!");
            _getch(); // Chờ người dùng nhấn phím
            ThaoTacKhachHang();
        }
    }
}
void TimSachTheoTacGia(int *n){
    char Author[50];
    ClearScreen();
    printf("----------TRA CUU SACH-----------\n \n");
    printf("-------TIM SACH THEO TAC GIA-----\n");
    printf("Nhap ten tac gia: ");
    scanf("%s", Author);
    unsigned int index = hash(Author); // Tính toán chỉ số băm
    AVLNode *result = searchAVL(HashTableBook[index], Author, compareString); // Tìm kiếm trong bảng băm
    if (result != NULL) {
        Book *book = (Book *)result->data; // Lấy dữ liệu sách
        printf("Ten sach: %s, Ten tac gia: %s, So luong: %d\n", book->Title, book->Author, book->Quantity);
    } else {
        printf("Khong tim thay sach\n");
        if (n == 2) { // n = 2 tức được gọi từ MuonSach, nếu khác 2 thì không cần hỏi
            printf("Ban co muon them yeu cau vao hang doi khong? (Y/N): ");
            char choice;
            scanf(" %c", &choice);
            if (choice == 'Y' || choice == 'y') {
                // Thêm yêu cầu vào hàng đợi
                printf("Da them yeu cau vao hang doi\n");
                printf("Ban co muon them uu tien khong? (Y/N): ");
                char choice;
                scanf(" %c", &choice);
                if (choice == 'Y' || choice == 'y') {
                    // Thêm yêu cầu vào hàng đợi với ưu tiên
                    printf("Da them yeu cau vao hang doi voi uu tien\n");
                    printf("Nhan phim bat ky de quay lai!");
                    _getch(); // Chờ người dùng nhấn phím
                    ThaoTacKhachHang();
                } else {
                    printf("Ban da huy yeu cau!\n");
                    printf("Nhan phim bat ky de quay lai!");
                    _getch(); // Chờ người dùng nhấn phím
                    ThaoTacKhachHang();
                }

            } else {
                printf("Ban da huy yeu cau!\n");
                printf("Nhan phim bat ky de quay lai!");
                _getch(); // Chờ người dùng nhấn phím
                ThaoTacKhachHang();
            }
        }
        else {
            printf("Bam phim bat ky de quay lai!");
            _getch(); // Chờ người dùng nhấn phím
            ThaoTacKhachHang();
        }
    }
}
void MuonSach(int *n){
    ClearScreen();
    printf("----------MUON SACH----------\n \n");
    char IdentifyID[12];    
    printf("Nhap Can cuoc cong dan: ");     
    scanf("%s", IdentifyID);
    if (SearchMember(IdentifyID)) {
        if (GetCurrentQuantity(IdentifyID) < 10) {
            if (n == 2) TraCuuSach(n); 
            // n = 2 tức là từ ThaoTacKhachHang chưa có sách muốn mượn nên cần tra và in ra
            // n khác 2 tức là tới từ TraCuuSach đã có thông tin sách rồi
            printf("Xac nhan muon sach khong? (Y/N): "); //Xác nhận mượn sách
            char choice; //biến lựa chọn
            scanf(" %c", &choice);
            if (choice == 'Y' || choice == 'y') {
                // Tạo mã mượn sách
                // Cập nhật thông tin 
            }
            else {
                printf("Ban da huy muon sach!\n");
                printf("Nhan phim bat ky de quay lai!");
                _getch(); // Chờ người dùng nhấn phím
                ThaoTacKhachHang();
            }
        }
        else {
            printf("Ban da muon toi da 10 cuon sach!\n");
            printf("Ban co muon tra sach khong?");
            char choice;
            scanf(" %c", &choice);
            if (choice == 'Y' || choice == 'y') {
                traSach(n); // Gọi hàm trả sách với n = 1 hoặc n = 2
            }
            else {
                printf("Nhan phim bat ky de quay lai!");
                _getch(); // Chờ người dùng nhấn phím
                ThaoTacKhachHang();
            }
        }
    }
    else { 
        printf("Khong tim thay thanh vien!\n");
        printf("Ban co muon dang ky thanh vien khong? (Y/N): ");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'Y' || choice == 'y') {
            addMember(); // Gọi hàm thêm thành viên
            printf("Ban da dang ky thanh cong!\n");
            printf("Nhan phim bat ky de quay lai!");
            _getch(); // Chờ người dùng nhấn phím
            ThaoTacKhachHang();
        }
        else {
            printf("Nhan phim bat ky de quay lai!");
            _getch(); // Chờ người dùng nhấn phím
            ThaoTacKhachHang();
        }
    }
}
void traSach(int *n){
    ClearScreen();
    printf("----------TRA SACH----------\n \n");
    char IdentifyID[12], BorrowID[12];    
    printf("Nhap Can cuoc cong dan: ");     
    scanf("%s", IdentifyID);
    printf("Nhap ma muon sach: ");
    scanf("%s", BorrowID);
    if (KiemTraMaMuon(BorrowID)) {
        //Cập nhật thông tin trả sách
        if (KiemTraThuocThuVien) {
            //Cập nhật dữ liệu
            printf("Bam phim bat ky de quay lai!");
            _getch(); // Chờ người dùng nhấn phím
            ThaoTacKhachHang();
        } else {
            printf("Bam phim bat ky de quay lai!");
            _getch(); // Chờ người dùng nhấn phím
            ThaoTacKhachHang();
        }    
    else {
        printf("Khong tim thay ma muon sach!\n");
        printf("Nhan phim bat ky de quay lai!");
        _getch(); // Chờ người dùng nhấn phím
        ThaoTacKhachHang();
        }
    }
}
bool KiemTraMaMuon(char *BorrowID){
    unsigned int index = hash(BorrowID); // Tính toán chỉ số băm
    AVLNode *result = searchAVL(HashTableBorrowing[index], BorrowID, compareString); // Tìm kiếm trong bảng băm
    if (result != NULL) {
        return true; // Mã mượn sách đã tồn tại
    } else {
        return false; // Mã mượn sách không tồn tại
    }
}
void ThaoTacQuanLy(){
    int action;
    printf("Chon thao tac thuc hien: \n");
    printf("1. Them dau sach\n");
    printf("2. Xoa dau sach\n");
    printf("3. Bao cao hoat dong\n");
    printf("4. Tra cuu sach\n");
    printf("5. Thong tin sach toan bo thu vien\n");
    printf("0. Quay lai!");
    printf("Nhap lua chon: "); scanf("%d", &action);
    switch (action) {
        case 1:
            themDauSach();
            break;
        case 2:
            xoaDauSach();
            break;
        case 3:
            baoCaoHoatDong();
            break;
        case 4:
            tracuuSach();
            break;
        case 5:
            thongTinSach();
            break;    
        case 0:
            Start();
            break;
        default:
            {
                printf("Lua chon khong hop le!\n");
                printf("Nhan phim bat ky de quay lai!");
                _getch(); // Chờ người dùng nhấn phím
                ThaoTacQuanLy();
            }
    }    
}

void themDauSach(){
    ClearScreen();
    printf("----------THEM DAU SACH----------\n \n");
    Book *book = (Book *)malloc(sizeof(Book));
    printf("Nhap ten sach: ");
    scanf("%s", book->Title);
    printf("Nhap ten tac gia: ");
    scanf("%s", book->Author);
    printf("Nhap so luong: ");
    scanf("%d", &book->Quantity);
    unsigned int index = hash(book->Title); // Tính toán chỉ số băm
    HashTableBook[index] = insertAVL(HashTableBook[index], book, compareString); // Thêm sách vào bảng băm
    printf("Da them sach thanh cong!\n");
}

void xoaDauSach(){
    ClearScreen();
    printf("----------XOA DAU SACH----------\n \n");
    char Title[50];
    printf("Nhap ten sach: ");
    scanf("%s", Title);
    printf("Nhap ten tac gia: ");
    scanf("%s", Author);
}
void baoCaoHoatDong(){
    ClearScreen();
    printf("----------BAO CAO HOAT DONG----------\n \n");
    // Thực hiện báo cáo hoạt động
    printf("Bao cao hoat dong thanh cong!\n");
}

void thongTinSach(){
    ClearScreen();
    printf("----------THONG TIN SACH----------\n \n");
    // Thực hiện thông tin sách
    printf("Thong tin sach thanh cong!\n");
}