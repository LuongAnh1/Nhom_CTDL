#include <stdio.h>
#include <stdlib.h>
#include "AVL_Tree.h"

// Ham so sanh cho so nguyen
int intCompare(void *a, void *b) {
    return (*(int*)a) - (*(int*)b);
}

// Ham duyet giua de in cac gia tri trong cay AVL
void printInOrder(AVLNode* root) {
    if (root == NULL) return;
    printInOrder(root->left);
    printf("%d ", *(int*)root->data);
    printInOrder(root->right);
}

// Kiem thu them phan tu vao cay
void test_insert() {
    printf("=== KIEM THU INSERT ===\n");
    AVLNode* root = NULL;
    int a = 10, b = 20, c = 5;
    root = insertAVL(root, &a, &a, intCompare);
    root = insertAVL(root, &b, &b, intCompare);
    root = insertAVL(root, &c, &c, intCompare);

    printf("Cay AVL sau khi chen 10, 20, 5 (thu tu giua): ");
    printInOrder(root);
    printf("\n");
}

// Kiem thu tim kiem phan tu trong cay
void test_search() {
    printf("=== KIEM THU SEARCH ===\n");
    AVLNode* root = NULL;
    int v[3] = {10, 20, 5};
    for (int i = 0; i < 3; ++i)
        root = insertAVL(root, &v[i], &v[i], intCompare);

    printf("Cay AVL hien tai (thu tu giua): ");
    printInOrder(root);
    printf("\n");

    int searchVal = 20;
    AVLNode* found = searchAVL(root, &searchVal, intCompare);
    if (found)
        printf("Tim thay nut co gia tri %d\n", *(int*)found->data);
    else
        printf("Khong tim thay nut co gia tri %d\n", searchVal);

    searchVal = 99;
    found = searchAVL(root, &searchVal, intCompare);
    if (found)
        printf("Tim thay nut co gia tri %d\n", *(int*)found->data);
    else
        printf("Khong tim thay nut co gia tri %d\n", searchVal);
}

// Kiem thu xoa phan tu trong cay
void test_delete() {
    printf("=== KIEM THU DELETE ===\n");
    AVLNode* root = NULL;
    int v[5] = {10, 20, 5, 15, 25};
    for (int i = 0; i < 5; ++i)
        root = insertAVL(root, &v[i], &v[i], intCompare);

    printf("Cay AVL truoc khi xoa (thu tu giua): ");
    printInOrder(root);
    printf("\n");

    int del = 20;
    root = deleteAVL(root, &del, intCompare);
    printf("Cay AVL sau khi xoa 20 (thu tu giua): ");
    printInOrder(root);
    printf("\n");

    del = 99;
    root = deleteAVL(root, &del, intCompare);
    printf("Cay AVL sau khi xoa 99 (khong ton tai) (thu tu giua): ");
    printInOrder(root);
    printf("\n");
}

int main() {
    test_insert();
    test_search();
    test_delete();
    system("PAUSE");
    return 0;
}