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
AVLNode* createNode(void *Data, void *Key) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    newNode->data = Data;
    newNode->key =Key;
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
AVLNode* Balance(AVLNode* node) {
    // Cập nhật chiều cao của nút
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Tính toán độ cân bằng của nút
    int balance = getBalance(node);

    // Nếu nút mất cân bằng, có 4 trường hợp

    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Trả về con trỏ gốc của cây đã được cân bằng
}
AVLNode* insertAVL(AVLNode* root, void *data, void *key, CompareFunction cmp){
    // Kiểm tra xem cây có nút chưa
    if (root == NULL) 
        return createNode(data, key); // Tạo nút mới nếu cây rỗng

    // Đưa cây vào đúng vị trí dựa trên giá trị của dữ liệu
    if (cmp(key, root->key) < 0)
        root->left = insertAVL(root->left, data, key, cmp);
    else if (cmp(key, root->key) > 0) 
        root->right = insertAVL(root->right, data, key, cmp);
    else // Nếu dữ liệu đã tồn tại trong cây => không làm gì cả
        return root;
    return Balance(root); // Cân bằng lại cây sau khi đã thêm nút mới
}
AVLNode* searchAVL(AVLNode* root, void *key, CompareFunction cmp){
    if (root == NULL || cmp(key, root->key) == 0) {
        return root; // Nếu tìm thấy hoặc cây rỗng
    }

    // Nếu dữ liệu nhỏ hơn nút hiện tại, tìm kiếm trong cây con bên trái
    if (cmp(key, root->key) < 0) {
        return searchAVL(root->left, key, cmp);
    }

    // Nếu dữ liệu lớn hơn nút hiện tại, tìm kiếm trong cây con bên phải
    return searchAVL(root->right, key, cmp);
}
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;

    // Tìm nút có giá trị nhỏ nhất trong cây con bên trái
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}
AVLNode* deleteAVL(AVLNode* root, void *key, CompareFunction cmp) {
    // Nếu cây rỗng, trả về NULL
    if (root == NULL) {
        return root;
    }

    // Tìm vị trí của nút cần xóa
    if (cmp(key, root->key) < 0) {
        root->left = deleteAVL(root->left, key, cmp);
    } else if (cmp(key, root->key) > 0) {
        root->right = deleteAVL(root->right, key, cmp);
    } else {
        // Nút cần xóa được tìm thấy
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode* temp = root->left ? root->left : root->right;

            // Nếu không có con nào (nút là lá), gán NULL cho nút hiện tại
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else { // Nếu có một con, gán con đó cho nút hiện tại
                *root = *temp; // Sao chép nội dung của nút con vào nút hiện tại
            }
            free(temp); // Giải phóng bộ nhớ của nút đã xóa
        } else {
            // Nút có hai con: tìm giá trị nhỏ nhất trong cây con bên phải
            // bằng cách xét nút con bên phải và timg nút con nhỏ nhất bên tráitrái
            AVLNode* temp = minValueNode(root->right);

            // Sao chép giá trị nhỏ nhất vào nút hiện tại
            root->data = temp->data;

            // Xóa nút nhỏ nhất trong cây con bên phải (gọi lại hàm đệ quy -> vị trí xóa là vị trí của nút nhỏ nhất)
            // -> cân bằng lại cây từ nút nhỏ nhất của cây con bên phải
            root->right = deleteAVL(root->right, temp->key, cmp);
        }
    }

    // Nếu cây chỉ còn một nút hoặc rỗng, trả về NULL
    if (root == NULL) {
        return root;
    }

    return Balance(root); // Cân bằng lại cây sau khi đã xóa nút
}