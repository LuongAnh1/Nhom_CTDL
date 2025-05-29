#include "queue.h"
#include "book.h"
// Tạo nút Queue 
Queue* makeNode(char IdentifyID[12], char Title[100], char Author[100], struct tm DecideDate, bool Order){
    Queue *newNode = (Queue*)malloc(sizeof(Queue));
    strcpy(newNode->IdentifyID, IdentifyID);
    strcpy(newNode->Title, Title);
    strcpy(newNode->Author, Author);
    newNode->Order = Order;
    newNode->DecideBorrow = DecideDate;
    newNode->next = NULL;
    return newNode;
}

// Thêm nút vào hàng đợi 
void insertNode(const char *IdentifyID, const char *Title, const char *Author, bool Order, struct tm DecideDate) {
    Book *book = searchBook(Title, Author);
    if (book == NULL) {
        printf("Khong tim thay sach: %s - %s\n", Title, Author);
        return;
    }

    Queue *newNode = makeNode(IdentifyID, Title, Author, DecideDate, Order);

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
        printf("Đã xóa người mượn trong hàng ưu tiên.\n");
    } else if (book->queue0) {
        temp = book->queue0;
        book->queue0 = book->queue0->next;
        free(temp);
        printf("Đã xóa người mượn trong hàng thường.\n");
    } else {
        printf("Hàng đợi rỗng, không có ai để xóa.\n");
    }
}

// Duyệt in cả hai hàng đợi
void traverse(char Title[100], char Author[100]) {
    Book* book = searchBook(Title, Author);
    if (!book) return;

    printf("Hàng đợi ưu tiên:\n");
    Queue* p = book->queue1;
    while (p) {
        printf("%s (ID: %s)\n", p->Title, p->IdentifyID);
        p = p->next;
    }

    printf("Hàng đợi thường:\n");
    p = book->queue0;
    while (p) {
        printf("%s (ID: %s)\n", p->Title, p->IdentifyID);
        p = p->next;
    }
}

// Tìm người trong queue1 hoặc queue0 của một cuốn sách
Queue* searching(Book* book, char IdentifyID[12]) {
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
void saveQueueToFileHelper(FILE *f, Queue *q, const char *title, const char *author) {
    while (q) {
        fprintf(f, "%s;%s;%s;%d/%d/%d;%d\n", q->IdentifyID, title, author, 
            q->DecideBorrow.tm_mday, q->DecideBorrow.tm_mon,q->DecideBorrow.tm_year,
            q->Order);
        q = q->next;
    }
}
// Lưu hàng đợi của sách vào file (hàng đợi ưu tiên vào không ưu tiên) 
void saveQueueOfBookWithFile(Book *book, void *filePtr) {
    FILE *f = (FILE *)filePtr;
    if (!book || !f) return;
    saveQueueToFileHelper(f, book->queue1, book->Title, book->Author);
    saveQueueToFileHelper(f, book->queue0, book->Title, book->Author);
}
// Dùng cho hàm saveAllQueuesToFile
void traverseAVLWithArg(AVLNode *root, void (*visit)(Book *, void *), void *arg) {
    if (!root) return;
    traverseAVLWithArg(root->left, visit, arg);
    visit((Book *)root->data, arg);
    traverseAVLWithArg(root->right, visit, arg);
}
// Duyệt toàn bộ sách để lưu hàng đợi 
void saveAllQueuesToFile(const char *fileName) {
    FILE *f = fopen(fileName, "w");
    if (!f) {
        printf("Không thể mở file %s để ghi!\n", fileName);
        return;
    }
    for (int i = 0; i < TABLE_SIZE; ++i) {
        traverseAVLWithArg(HashTableBook[i], saveQueueOfBookWithFile, f);

    }
    fclose(f);
}
// Đọc từ file ra 
void loadQueueFromFile(const char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (!f) {
        printf("Không thể mở file %s để đọc!\n", fileName);
        return;
    }

    char line[300];
    while (fgets(line, sizeof(line), f)) {
        // Nếu dòng chỉ chứa ký tự newline (dòng trống)
        if (strcmp(line, "\n") == 0)
            continue;
        line[strcspn(line, "\n")] = '\0'; // Xóa ký tự xuống dòng 
        Queue *newNode = (Queue *)malloc(sizeof(Queue));

        sscanf(line, "%11[^,];%99[^,];%99[^,];%d/%d/%d;%d",
               newNode->IdentifyID, newNode->Title, newNode->Author,
               newNode->DecideBorrow.tm_mday,newNode->DecideBorrow.tm_mon,
               newNode->DecideBorrow.tm_year ,newNode->Order);
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

