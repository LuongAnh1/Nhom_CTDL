#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Member.h"
#include "AVL_Tree.h"
#include "hash.h"

AVLNode *HashTableMember[TABLE_SIZE] = {NULL};
// Ham in thong tin mot thanh vien
void printMember(Member *member) {
    if (member)
        printf("ID: %s, Ten: %s, Sach muon: %d\n", member->IdentifyID, member->Name, member->CurrentQuantity);
    else
        printf("Thanh vien NULL\n");
}

// Ham duyet cay AVL theo thu tu giua de in thanh vien
void printInOrderMember(AVLNode* root) {
    if (root == NULL) return;
    printInOrderMember(root->left);
    printMember((Member*)root->data);
    printInOrderMember(root->right);
}

// In toan bo bang bam
void printAllMember() {
    printf("=== Danh sach thanh vien hien tai ===\n");
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (HashTableMember[i]) {
            printf("Bucket %d:\n", i);
            printInOrderMember(HashTableMember[i]);
        }
    }
}

// Kiem thu them thanh vien
void test_InputMember() {
    printf("=== KIEM THU THEM THANH VIEN ===\n");
    Member *m1 = (Member*)malloc(sizeof(Member));
    strcpy(m1->IdentifyID, "111");
    strcpy(m1->Name, "Nguyen Van A");
    m1->CurrentQuantity = 0;
    InputMember(m1);

    Member *m2 = malloc(sizeof(Member));
    strcpy(m2->IdentifyID, "222");
    strcpy(m2->Name, "Tran Thi B");
    m2->CurrentQuantity = 2;
    InputMember(m2);

    printAllMember();
}

// Kiem thu tim kiem thanh vien
void test_SearchMember() {
    printf("=== KIEM THU TIM KIEM THANH VIEN ===\n");
    Member *result = SearchMember("111");
    printf("Tim kiem ID 111:\n");
    printMember(result);

    result = SearchMember("333");
    printf("Tim kiem ID 333:\n");
    printMember(result);
}

// Kiem thu xoa thanh vien khong dung scanf
void test_DeleteMember_auto(char *id) {
    printf("=== KIEM THU XOA THANH VIEN ID %s ===\n", id);
    unsigned int index = hash(id);
    AVLNode *result = searchAVL(HashTableMember[index], id, compareString);
    if (result != NULL) {
        Member *member = (Member *)result->data;
        if (member->CurrentQuantity > 0) {
            printf("Khong the xoa thanh vien, vi con sach muon\n");
        } else {
            HashTableMember[index] = deleteAVL(HashTableMember[index], member->IdentifyID, compareString);
            printf("Da xoa thanh vien\n");
        }
    } else {
        printf("Khong tim thay thanh vien\n");
    }
    printAllMember();
}

int main() {
    // Xoa bang bam truoc khi test
    for (int i = 0; i < TABLE_SIZE; ++i) HashTableMember[i] = NULL;

    test_InputMember();
    test_SearchMember();
    test_DeleteMember_auto("222"); // Co sach muon, khong xoa duoc
    test_DeleteMember_auto("111"); // Xoa duoc
    test_DeleteMember_auto("999"); // Khong ton tai
    system("PAUSE");
    return 0;
}