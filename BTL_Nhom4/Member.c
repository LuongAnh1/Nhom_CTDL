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
    newMember->CurrentQuantity = 0; // Khởi tạo số lượng sách mượn là 0
    InputMember(newMember); // Thêm thành viên vào bảng băm
    // Lưu thành viên vào file
    FILE *file = fopen("Member.csv", "a");
    if (file == NULL) {
        printf("Khong the mo file! Member.csv\n");
        return;
    }
    fprintf(file, "%s,%s,%d\n", newMember->IdentifyID, newMember->Name, newMember->CurrentQuantity);
    fclose(file);
}

//Tìm kiếm thành viên
bool SearchMember(char *IdentifyID) {
    unsigned int index = hash(IdentifyID); // Tính toán chỉ số băm
    AVLNode *result = searchAVL(HashTableMember[index], IdentifyID, compareString); // Tìm kiếm trong bảng băm
    // if (result == NULL) return NULL;
    // Member *member = (Member *)result->data; // Lấy dữ liệu thành viên
    // return member;
    if (result != NULL) {
        Member *member = (Member *)result->data; // Lấy dữ liệu thành viên
        printf("Can cuoc cong dan: %s, Ho va ten: %s, So sach muon: %d\n", member->IdentifyID, member->Name, member->CurrentQuantity);
        return true;
    } else {
        return false;
    }
}

//Xóa thành viên
void DeleteMember() {
    char IdentifyID[12];
    printf("Nhap Can cuoc cong dan: ");
    scanf("%s", IdentifyID);
    unsigned int index = hash(IdentifyID); // Tính toán chỉ số băm
    AVLNode *result = searchAVL(HashTableMember[index], IdentifyID, compareString); // Tìm kiếm trong bảng băm
    if (result != NULL) {
        Member *member = (Member *)result->data; // Lấy dữ liệu thành viên
        if (member->CurrentQuantity > 0) {
            printf("Khong the xoa thanh vien, vi con sach muon\n");
        }
        else HashTableMember[index] = deleteAVL(HashTableMember[index], result->data, compareString); // Xóa thành viên khỏi bảng băm
        printf("Da xoa thanh vien\n");
    } else {
        printf("Khong tim thay thanh vien\n");
    }
}
//Hàm trả về số lượng sách đang mượn của thành viên theo CCCD
int GetCurrentQuantity(char *IdentifyID) {
    unsigned int index = hash(IdentifyID); // Tính toán chỉ số băm
    AVLNode *result = searchAVL(HashTableMember[index], IdentifyID, compareString); // Tìm kiếm trong bảng băm
    if (result != NULL) {
        Member *member = (Member *)result->data; // Lấy dữ liệu thành viên
        return member->CurrentQuantity; // Trả về số lượng sách đang mượn
    } else {
        printf("Khong tim thay thanh vien\n");
        return -1;
    }
}

//------Ghi ra file CSV------

// Hàm duyệt cây AVL 
void inorderWriteMember(FILE *file, AVLNode *node) {
    if (node == NULL) return;

    inorderWriteMember(file, node->left);

    Member *member = (Member *)node->data;
    fprintf(file, "%s,%s,%d\n", member->IdentifyID, member->Name, member->CurrentQuantity);

    inorderWriteMember(file, node->right);
}

void StoreMember() {
    FILE *file = fopen("Member.csv", "w");
    if (file == NULL) {
        printf("Khong the mo file! Member.csv\n");
        return;
    }

    // Ghi tiêu đề các cột, có thể bỏ qua nếu không cần
    fprintf(file, "IdentifyID,Name,CurrentQuantity\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        AVLNode *node = HashTableMember[i];
        inorderWriteMember(file, node);
    }
    
    fclose(file);
}

