#include "Member.h"
#include <string.h>
#include "AVL_Tree.h"
#include "Data.h"
#include "hash.h"

// Tạo 
//Thêm thành viên
void InputMember(Member *newMember) {
    char *key = newMember->IdentifyID; // Lấy IdentifyID làm khóa
    HashTableMember[hash(key)] = insertAVL(HashTableMember[hash(key)], newMember, key, compareString); // Thêm vào bảng băm
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
        // Nếu dòng chỉ chứa ký tự newline (dòng trống)
        if (strcmp(line, "\n") == 0)
            continue;
        line[strcspn(line, "\n")] = '\0';
        Member *newMember = (Member*)malloc(sizeof(Member));
        sscanf(line, "%[^,],%[^,],%d", newMember->IdentifyID, newMember->Name, &newMember->CurrentQuantity);
        InputMember(newMember); // Thêm thành viên vào bảng băm
    }
    fclose(file);

}

//Tìm kiếm thành viên
Member* SearchMember(char *IdentifyID) {
    unsigned int index = hash(IdentifyID); // Tính toán chỉ số băm
    AVLNode *result = searchAVL(HashTableMember[index], IdentifyID, compareString); // Tìm kiếm trong bảng băm
    if (result != NULL) {
        Member *member = (Member *)result->data; // Lấy dữ liệu thành viên
        return member;
    } else {
        return NULL; // Không tìm thấy thành viên 
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
        else HashTableMember[index] = deleteAVL(HashTableMember[index], member->IdentifyID, compareString); // Xóa thành viên khỏi bảng băm
        printf("Da xoa thanh vien\n");
    } else {
        printf("Khong tim thay thanh vien\n");
    }
}

//------Ghi ra file CSV------

// Hàm duyệt cây AVL 

void inorderWriteMember(FILE *file, AVLNode *node) {
    if (node == NULL) return;

    Member *member = (Member *)node->data;
    fprintf(file, "%s,%s,%d\n", member->IdentifyID, member->Name, member->CurrentQuantity);
    
    inorderWriteMember(file, node->left);

    inorderWriteMember(file, node->right);
}

void StoreMember() {
    FILE *file = fopen("data/Member.csv", "w");
    if (file == NULL) {
        printf("Khong the mo file! Member.csv\n");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        AVLNode *node = HashTableMember[i];
        inorderWriteMember(file, node);
    }
    
    fclose(file);
}

