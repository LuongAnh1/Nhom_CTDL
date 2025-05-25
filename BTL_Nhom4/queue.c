#include "queue.h"
#include "book.h"

Queue* makeNode(char IdentifyID[12], char Title[100], char Author[100], bool order){
    Queue *newNode = (Queue*)malloc(sizeof(Queue));
    strcpy(newNode->IdentifyID, IdentifyID);
    strcpy(newNode->Title, Title);
    strcpy(newNode->Author, Author);
    newNode->Order = order;
    //time tự nhập
    newNode->next = NULL;
    return newNode;
}

void insertNode(char IdentifyID[12], char Title[100], char Author[100], bool order) {
    Book* book = searchBook(Title, Author);
    if (!book) {
        printf("Không tìm thấy sách.\n");
        return;
    }

    Queue* newNode = makeNode(IdentifyID, Title, Author, order);
    if (!newNode) {
        printf("Không đủ bộ nhớ để tạo node mới.\n");
        return;
    }

    Queue** head = order ? &(book->queue1) : &(book->queue0);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Queue* temp = *head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
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

