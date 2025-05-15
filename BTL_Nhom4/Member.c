#include "Member.h"
#include <string.h>
#include "AVL_Tree.h"
#include "Data.h"
#include "hash.h"

//Thêm thành viên
void InputMember(Member *newMember) {
    AVLNode *newNode = createNode(newMember); // Tạo nút mới cho thành viên
    char *key = newMember->IdentifyID; // Lấy IdentifyID làm khóa
    InsertAVL(HashTableMember[hash(key)], newNode, compareString); // Thêm vào bảng băm
}
// Đọc từ file csv
void ReadMember(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file! %s\n", filename);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)){
        Member *newMember = (Member*)malloc(sizeof(Member));
        sscanf(line, "%[^,],%[^,],%d", newMember->IdentifyID, newMember->Name, &newMember->CurrentQuantity);
        InputMember(newMember); // Thêm thành viên vào bảng băm
    }
    fclose(file);
}
void AddMember() {
    Member *newMember = (Member*)malloc(sizeof(Member));
    printf("Nhap Can cuoc cong dan: ");
    scanf("%s", newMember->IdentifyID);
    printf("Nhap ho va ten: ");
    scanf("%s", newMember->Name);
    printf("Nhap so sach muon: ");
    scanf("%d", &newMember->CurrentQuantity);
    InputMember(newMember); // Thêm thành viên vào bảng băm
}

//Tìm kiếm thành viên
void SearchMember() {
    char IdentifyID[12];
    printf("Nhap Can cuoc cong dan: ");
    scanf("%s", IdentifyID);
    unsigned int index = hash(IdentifyID); // Tính toán chỉ số băm
    AVLNode *result = searchAVL(HashTableMember[index], IdentifyID, compareString); // Tìm kiếm trong bảng băm
    if (result != NULL) {
        Member *member = (Member *)result->data; // Lấy dữ liệu thành viên
        printf("Can cuoc cong dan: %s, Ho va ten: %s, So sach muon: %d\n", member->IdentifyID, member->Name, member->CurrentQuantity);
    } else {
        printf("Khong tim thay thanh vien\n");
    }
}

//Xóa thành viên
void DeleteMember() {
    char IdentifyID[12];
    printf("Nhap Can cuoc cong dan: ");
    scanf("%s", IdentifyID);
    unsigned int index = hash(IdentifyID); // Tính toán chỉ số băm
    AVLNode *result = searchAVL(HashTableMember[index], IdentifyID, compareString); // Tìm kiếm trong bảng băm
    Member *member = (Member *)result->data; // Lấy dữ liệu thành viên
    if (result != NULL && member->CurrentQuantity == 0) {// Kiểm tra có tìm thấy thành viên và số sách mượn là 0
        HashTableMember[index] = deleteAVL(HashTableMember[index], result->data, compareString); // Xóa thành viên khỏi bảng băm
        free(result->data); // Giải phóng bộ nhớ
        free(result); // Giải phóng nút
        printf("Xoa thanh vien thanh cong\n");
    } else {
        printf("Khong tim thay thanh vien\n");
    }
}
