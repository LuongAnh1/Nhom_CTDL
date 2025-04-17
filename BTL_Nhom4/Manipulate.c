#include "Manipulate.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "Data.h"

void Insert(Book book) {
    char s[201];
    sprintf(s,"%s_%s", book.Name, book.Author); // Tạo chuỗi khóa từ tên và tác giả
    unsigned int key = hash(s); // Tính toán chỉ số băm
    Node *newNode = (Node*)malloc(sizeof(Node)); // Tạo nút mới
    newNode->data = book; // Gán dữ liệu cho nút mới
    newNode->left = NULL;
    newNode->right = NULL;
    if(Table[key] == NULL)
        Table[key] = newNode; // Gán nút mới vào bảng băm
    else{
        char s1[201];
        sprintf(s1,"%s_%s",Table[key]->data.Name,Table[key]->data.Author); // Tạo chuỗi khóa từ tên và tác giả của nút đầu tiên
        Node *cur=Table[key],*parent; 
        int l=strcmp(s1,s);
        while(l != 0){
            parent=cur;
            if(l<0)
                cur=cur->left; // Di chuyển sang nút bên phải
            else
                cur=cur->right; // Di chuyển sang nút bên trái
            if (cur == NULL)
                break; // Thoát khỏi vòng lặp
            sprintf(s1,"%s_%s",cur->data.Name,cur->data.Author); // Tạo chuỗi khóa từ tên và tác giả của nút hiện tại
            l=strcmp(s1,s);
        }
        if (l<0)
            parent->right=newNode;
        else if (l>0)
            parent->left=newNode;
        else{
            cur->data.Have += book.Have; // Cộng số lượng sách nếu đã tồn tại trong danh sách liên kết
            free(newNode);
        }
    }
}