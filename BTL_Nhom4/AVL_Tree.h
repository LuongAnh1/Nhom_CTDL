#ifndef AVL_TREE
#define AVL_TREE
#include "Data.h"

AVLNode* insertAVL(AVLNode* root, void *data, CompareFunction cmp);
// cmp: hàm so sánh giữa 2 đối tượng, trả về 1 nếu lớn hơn, -1 nếu nhỏ hơn và 0 nếu bằng nhau
#endif