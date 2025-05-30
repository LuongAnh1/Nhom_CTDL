#include "Queue.h"
#include "Book.h"
#include <stdlib.h>
#include <string.h>
// Tạo nút Queue 
Queue* makeNode(char* IdentifyID, char* Title, char* Author, bool Order){
    Queue *newNode = (Queue*)malloc(sizeof(Queue));
    strcpy(newNode->IdentifyID, IdentifyID);
    strcpy(newNode->Title, Title);
    strcpy(newNode->Author, Author);
    newNode->Order = Order;
    memset(&newNode->DecideBorrow, 0, sizeof(struct tm));
    newNode->next = NULL;
    return newNode;
}

// Thêm nút vào hàng đợi 
void insertNode(char *IdentifyID, char *Title, char *Author, bool Order) {
    Book *book = searchBook(Title, Author);
    if (book == NULL) {
        printf("Khong tim thay sach: %s - %s\n", Title, Author);
        return;
    }

    Queue *newNode = makeNode(IdentifyID, Title, Author, Order);

    if (Order) {
        // chen vao queue1 (uu tien)
        if (book->queue1 == NULL) {
            book->queue1 = newNode;
        } else {
            Queue *temp = book->queue1;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    } else {
        // chen vao queue0 (binh thuong)
        if (book->queue0 == NULL) {
            book->queue0 = newNode;
        } else {
            Queue *temp = book->queue0;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }
}

//Lấy thông tin người đầu tiên
Queue* getfront(Book *book){
    if (book->queue1) {
        return book->queue1;  // Ưu tiên 1
    } else if (book->queue0) {
        return book->queue0;  // Nếu không có người ưu tiên
    } else {
        return NULL; // Không có ai trong hàng đợi
    }
}

// Xoá node đầu tiên của cả hai hàng đợi (ưu tiên trước)
void deleteNode(Book *book) {
    Queue *temp;
    if (book->queue1) {
        temp = book->queue1;
        book->queue1 = book->queue1->next;
        free(temp);
        printf("Da xoa nguoi muon trong hang uu tien.\n");
    } else if (book->queue0) {
        temp = book->queue0;
        book->queue0 = book->queue0->next;
        free(temp);
        printf("Da xoa nguoi muon trong hang thuong.\n");
    } else {
        printf("Hang doi rong, khong co ai de xoa.\n");
    }
}

// Duyệt in cả hai hàng đợi
void traverse(char* Title, char* Author) {
    Book* book = searchBook(Title, Author);
    if (!book) return;

    printf("Hang doi uu tien:\n");
    Queue* p = book->queue1;
    while (p) {
        printf("%s (ID: %s)\n", p->Title, p->IdentifyID);
        p = p->next;
    }

    printf("Hang doi thuong:\n");
    p = book->queue0;
    while (p) {
        printf("%s (ID: %s)\n", p->Title, p->IdentifyID);
        p = p->next;
    }
}

// Tìm người trong queue1 hoặc queue0 của một cuốn sách
Queue* searching(Book* book, char* IdentifyID) {
    Queue* p = book->queue1;
    while (p) {
        if (strcmp(p->IdentifyID, IdentifyID) == 0) return p;
        p = p->next;
    }

    p = book->queue0;
    while (p) {
        if (strcmp(p->IdentifyID, IdentifyID) == 0) return p;
        p = p->next;
    }

    return NULL; // Không tìm thấy
}
// Lưu từng nhánh hàng đợi vào file 
void saveQueueToFileHelper(FILE *f, Queue *q) {
    while (q) {
        const char *id = (q->IdentifyID[0]) ? q->IdentifyID : "NULL";
        const char *title = (q->Title[0]) ? q->Title : "NULL";
        const char *author = (q->Author[0]) ? q->Author : "NULL";
        fprintf(f, "%s;%s;%s;%d/%d/%d;%d\n", 
            id, title, author, 
            q->DecideBorrow.tm_mday, 
            q->DecideBorrow.tm_mon + 1, 
            q->DecideBorrow.tm_year + 1900, 
            q->Order);
        q = q->next;
    }
}


// Lưu hàng đợi của sách vào file (hàng đợi ưu tiên vào không ưu tiên) 
void saveQueueOfBookWithFile(Book *book, void *filePtr) {
    FILE *f = (FILE *)filePtr;
    if (!book || !f) return;
    saveQueueToFileHelper(f, book->queue1);
    saveQueueToFileHelper(f, book->queue0);
}
// Dùng cho hàm saveAllQueuesToFile
void traverseAVLWithArg(AVLNode *root, void (*visit)(Book *, void *), void *arg) {
    if (!root) return;
    traverseAVLWithArg(root->left, visit, arg);
    if (root->data == NULL) {
        printf("LỖI: root->data == NULL\n");
        return;
    }
    visit((Book *)root->data, arg);
    traverseAVLWithArg(root->right, visit, arg);
}
// Duyệt toàn bộ sách để lưu hàng đợi 
void saveAllQueuesToFile(const char *fileName) {
    FILE *f = fopen(fileName, "w");
    if (!f) {
        printf("Khong the mo file %s de ghi!\n", fileName);
        return;
    }
    for (int i = 0; i < TABLE_SIZE; ++i) 
        if(HashTableBook[i]){
            traverseAVLWithArg(HashTableBook[i], saveQueueOfBookWithFile, f);
        }
    fclose(f);
}
// Đọc từ file ra 
void loadQueueFromFile(const char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (!f) {
        printf("Khong the mo file %s de doc!\n", fileName);
        return;
    }

    char line[300];
    while (fgets(line, sizeof(line), f)) {
        // Nếu dòng chỉ chứa ký tự newline (dòng trống)
        if (strcmp(line, "\n") == 0)
            continue;
        line[strcspn(line, "\n")] = '\0'; // Xóa ký tự xuống dòng 
        Queue *newNode = (Queue *)malloc(sizeof(Queue));

        sscanf(line, "%12[^;];%199[^;];%199[^;];%d/%d/%d;%d",
                newNode->IdentifyID, newNode->Title, newNode->Author,
                &newNode->DecideBorrow.tm_mday, &newNode->DecideBorrow.tm_mon,
                &newNode->DecideBorrow.tm_year, &newNode->Order);

        newNode->next = NULL;

        Book *book = (Book *)searchBook(newNode->Title, newNode->Author);
        if (book) {
            insertQueueNode(book, newNode);
        } else {
            free(newNode); // Tránh rò rỉ bộ nhớ nếu sách không tồn tại
        }
    }

    fclose(f);
}
// Thêm nút vào hàng đợi 
void insertQueueNode(Book *book, Queue *node) {
    Queue **head = node->Order ? &book->queue1 : &book->queue0;

    if (!*head) {
        *head = node;
    } else {
        Queue *cur = *head;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }
}

