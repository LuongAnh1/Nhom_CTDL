#include <stdio.h>
#include <stdlib.h>
#include "AVL_Tree.h"

// Hàm so sánh khóa kiểu int
int compareInt(void* a, void* b) {
    int intA = *(int*)a;
    int intB = *(int*)b;
    return intA - intB;
}

// Hàm in theo thứ tự giữa để kiểm tra cây
void inorderTraversal(AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", *(int*)(root->key));
        inorderTraversal(root->right);
    }
}

int main() {
    AVLNode* root = NULL;

    // Dữ liệu kiểm thử
    int keys[] = {20, 10, 30, 25, 40, 22, 50};
    int n = sizeof(keys) / sizeof(keys[0]);

    // Chèn các phần tử vào cây AVL
    printf("Chen cac nut: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", keys[i]);
        int* key = malloc(sizeof(int));
        *key = keys[i];
        root = insertAVL(root, NULL, key, compareInt);
    }
    printf("\n");

    // In cây theo thứ tự giữa sau khi chèn
    printf("Cay AVL sau khi chen (inorder): ");
    inorderTraversal(root);
    printf("\n");

    // Tìm kiếm 1 nút
    int target = 25;
    AVLNode* found = searchAVL(root, &target, compareInt);
    if (found) {
        printf("Tim thay nut co khoa %d.\n", *(int*)found->key);
    } else {
        printf("Khong tim thay nut co khoa %d.\n", target);
    }

    // Xóa một nút
    int toDelete = 30;
    printf("Xoa nut co khoa %d.\n", toDelete);
    root = deleteAVL(root, &toDelete, compareInt);

    // In cây sau khi xóa
    printf("Cay AVL sau khi xoa (inorder): ");
    inorderTraversal(root);
    printf("\n");
    system("PAUSE");
    return 0;
}
