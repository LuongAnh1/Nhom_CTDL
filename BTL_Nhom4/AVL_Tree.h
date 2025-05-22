#ifndef AVL_TREE
#define AVL_TREE
#include "Data.h"
#include <stdlib.h>

typedef int (*CompareFunction)(void*, void*); 
// cmp: hàm so sánh giữa 2 đối tượng, trả về 1 nếu lớn hơn, -1 nếu nhỏ hơn và 0 nếu bằng nhau
// void *data: dữ liệu cần thêm vào cây AVL - tự định nghĩa kiểu dữ liệu
AVLNode* createNode(void *data,void *key); // Tạo nút mới trong cây AVL
AVLNode* Balance(AVLNode* node); // Cân bằng lại cây AVL
AVLNode* insertAVL(AVLNode* root, void *data, void *key, CompareFunction cmp);
AVLNode* searchAVL(AVLNode* root, void *key, CompareFunction cmp);
AVLNode* minValueNode(AVLNode* node); // Tìm nút có giá trị nhỏ nhất trong cây con bên trái
AVLNode* deleteAVL(AVLNode* root, void *key, CompareFunction cmp); // Xóa nút trong cây AVL

#endif
