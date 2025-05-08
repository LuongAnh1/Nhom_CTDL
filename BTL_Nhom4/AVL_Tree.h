#ifndef AVL_TREE
#define AVL_TREE
#include "Data.h"
#include <stdlib.h>

typedef int (*CompareFunction)(void*, void*); 
// cmp: hàm so sánh giữa 2 đối tượng, trả về 1 nếu lớn hơn, -1 nếu nhỏ hơn và 0 nếu bằng nhau
// void *data: dữ liệu cần thêm vào cây AVL - tự định nghĩa kiểu dữ liệu
AVLNode* insertAVL(AVLNode* root, void *data, CompareFunction cmp);
AVLNode* searchAVL(AVLNode* root, void *data, CompareFunction cmp);

#endif