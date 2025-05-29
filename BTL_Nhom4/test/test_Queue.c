#include "Queue.h"
#include "Book.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
AVLNode *HashTableBook[TABLE_SIZE] = {NULL};
// Ham ho tro tao cau truc date
struct tm make_date(int d, int m, int y) {
    struct tm date = {0};
    date.tm_mday = d;
    date.tm_mon = m;
    date.tm_year = y;
    return date;
}

// Test makeNode
void test_makeNode() {
    printf("Test: Tao node hang doi\n");
    printf("Dau vao: ID = \"U001\", Title = \"BookA\", Author = \"AuthorA\", Ngay = 1/5/125, Order = 1\n");
    struct tm date = make_date(1, 5, 125);
    Queue *node = makeNode("U001", "BookA", "AuthorA", date, 1);
    assert(strcmp(node->IdentifyID, "U001") == 0);
    assert(strcmp(node->Title, "BookA") == 0);
    assert(strcmp(node->Author, "AuthorA") == 0);
    assert(node->Order == 1);
    assert(node->DecideBorrow.tm_mday == 1 && node->DecideBorrow.tm_mon == 5 && node->DecideBorrow.tm_year == 125);
    free(node);
}

// Test insertNode va getfront
void test_insertNode_getfront() {
    printf("Test: Them node vao hang doi va lay nguoi dau hang\n");
    printf("Tao sach: Title = \"BookA\", Author = \"AuthorA\", Quantity = 1\n");
    Book book;
    strcpy(book.Title, "BookA");
    strcpy(book.Author, "AuthorA");
    book.Quantity = 1;
    book.queue0 = NULL; book.queue1 = NULL;
    insertBook(book);

    printf("Them node uu tien: ID = \"U002\", Order = 1\n");
    struct tm date1 = make_date(2, 5, 125);
    insertNode("U002", "BookA", "AuthorA", 1, date1);

    printf("Them node thuong: ID = \"U003\", Order = 0\n");
    struct tm date2 = make_date(3, 5, 125);
    insertNode("U003", "BookA", "AuthorA", 0, date2);

    Book *b = searchBook("BookA", "AuthorA");
    Queue *front = getfront(b);
    printf("Nguoi dau hang: ID = %s (U002 la uu tien)\n", front ? front->IdentifyID : "NULL");
    assert(front && strcmp(front->IdentifyID, "U002") == 0);
}

// Test deleteNode
void test_deleteNode() {
    printf("Test: Xoa nguoi dau hang doi (uu tien truoc)\n");
    Book *b = searchBook("BookA", "AuthorA");
    printf("Xoa lan 1 (uu tien):\n");
    deleteNode(b);
    Queue *front = getfront(b);
    printf("Sau khi xoa: Nguoi dau hang la: %s (phai la U003)\n", front ? front->IdentifyID : "NULL");
    assert(front && strcmp(front->IdentifyID, "U003") == 0);

    printf("Xoa lan 2 (thuong):\n");
    deleteNode(b);
    front = getfront(b);
    printf("Sau khi xoa: Nguoi dau hang la: %s (phai la NULL)\n", front ? front->IdentifyID : "NULL");
    assert(front == NULL);
}

// Test searching
void test_searching() {
    printf("Test: Tim kiem nguoi trong hang doi theo ID\n");
    Book *b = searchBook("BookA", "AuthorA");
    printf("Them nguoi moi: ID = \"U004\", Order = 1\n");
    struct tm date = make_date(4, 5, 125);
    insertNode("U004", "BookA", "AuthorA", 1, date);
    Queue *found = searching(b, "U004");
    printf("Ket qua tim kiem: %s\n", found ? found->IdentifyID : "NULL");
    assert(found && strcmp(found->IdentifyID, "U004") == 0);
}

// Test traverse (in hang doi)
void test_traverse() {
    printf("Test: Duyet va in hang doi cho sach \"BookA\"\n");
    printf("Dau vao: Title = \"BookA\", Author = \"AuthorA\"\n");
    traverse("BookA", "AuthorA");
}

// Test luu va doc hang doi tu file
void test_save_load_queue_file() {
    printf("Test: Luu va doc hang doi tu file\n");
    printf("Luu hang doi ra file test_queue_out.txt\n");
    saveAllQueuesToFile("test_queue_out.txt");

    printf("Doc hang doi tu file test_queue_out.txt\n");
    loadQueueFromFile("test_queue_out.txt");

    // Co the in lai hang doi de kiem tra
    printf("Noi dung hang doi sau khi doc file:\n");
    traverse("BookA", "AuthorA");
}

int main() {
    printf("===== BAT DAU CHAY CAC TEST CHO Queue.c =====\n\n");
    test_makeNode();
    printf("\n");
    test_insertNode_getfront();
    printf("\n");
    test_deleteNode();
    printf("\n");
    test_searching();
    printf("\n");
    test_traverse();
    printf("\n");
    test_save_load_queue_file();
    printf("\n===== TAT CA CAC TEST DA CHAY XONG! =====\n");
    system("PAUSE");
    return 0;
}