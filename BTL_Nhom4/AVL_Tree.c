#include "AVL_Tree.h"

// Hàm lấy chiều cao của nút
int getHeight(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}
// Hàm so sánh 2 số nguyên
int max(int a, int b) {
    return (a > b) ? a : b;
}
// Tạo nút mới cho cây AVL
AVLNode* createNode(void *data) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // Mới thêm vào nên chiều cao là 1
    return newNode;
}
//Hàm quay phải để cần bằng lại cây AVL
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Thực hiện quay phải
    x->right = y;
    y->left = T2;

    // Cập nhật chiều cao của các nút
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    // Trả về nút mới làm gốc
    return x;
}
//Hàm quay trái để cần bằng lại cây AVL
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Thực hiện quay trái
    y->left = x;
    x->right = T2;

    // Cập nhật chiều cao của các nút
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    // Trả về nút mới làm gốc
    return y;
}
// Hàm lấy độ cân bằng của nút
int getBalance(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}
AVLNode* insertAVL(AVLNode* root, void *data, CompareFunction cmp){
    // Kiểm tra xem cây có nút chưa
    if (root == NULL) 
        return createNode(data); // Tạo nút mới nếu cây rỗng

    // Đưa cây vào đúng vị trí dựa trên giá trị của dữ liệu
    if (cmp(data, root->data) < 0)
        root->left = insertAVL(root->left, data, cmp);
    else if (cmp(data, root->data) > 0) 
        root->right = insertAVL(root->right, data, cmp);
    else // Nếu dữ liệu đã tồn tại trong cây, trả về vị trí hiện tại
        return root;

    // Cập nhật chiều cao của nút cha
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Tính toán độ cân bằng của nút cha để kiểm tra xem có cần cân bằng lại không
    int balance = getBalance(root);

    // Nếu nút mất cân bằng, có 4 trường hợp

    // Left Left Case
    if (balance > 1 && cmp(data, root->left->data) < 0) {
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && cmp(data, root->right->data) > 0) {
        return leftRotate(root);
    }

    // Left Right Case
    if (balance > 1 && cmp(data, root->left->data) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && cmp(data, root->right->data) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root; // Trả về con trỏ gốc của cây đã được cân bằng
}
AVLNode* searchAVL(AVLNode* root, void *data, CompareFunction cmp){
    if (root == NULL || cmp(data, root->data) == 0) {
        return root; // Nếu tìm thấy hoặc cây rỗng
    }

    // Nếu dữ liệu nhỏ hơn nút hiện tại, tìm kiếm trong cây con bên trái
    if (cmp(data, root->data) < 0) {
        return searchAVL(root->left, data, cmp);
    }

    // Nếu dữ liệu lớn hơn nút hiện tại, tìm kiếm trong cây con bên phải
    return searchAVL(root->right, data, cmp);
}