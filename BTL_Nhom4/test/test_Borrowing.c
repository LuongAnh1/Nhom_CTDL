#include "Borrowing.h"
#include "Book.h"
#include "Member.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

AVLNode *HashTableBook[TABLE_SIZE] = {NULL};
AVLNode *HashTableMember[TABLE_SIZE] = {NULL};
AVLNode *HashTableBorrowing[TABLE_SIZE] = {NULL};
// Ham ho tro tao cau truc date
struct tm make_date(int d, int m, int y) {
    struct tm date = {0};
    date.tm_mday = d;
    date.tm_mon = m;
    date.tm_year = y;
    return date;
}

// Test sinh ma tu dong
void test_generateCode() {
    printf("Test: Sinh ma phieu muon tu dong\n");
    char code[7] = "";
    generateCode(code);
    printf("Ma moi duoc sinh ra: %s\n", code);
    assert(strlen(code) == 6);
}

// Test tao node borrowing
void test_createBorrowingNode() {
    printf("Test: Tao node phieu muon\n");
    printf("Dau vao: ID = \"M001\", Title = \"BookA\", Author = \"AuthorA\", Ngay = 1/5/125\n");
    struct tm date = make_date(1, 5, 125);
    Borrowing *node = createBorrowingNode("M001", "BookA", "AuthorA", date);
    printf("%s\n",node->IdentifyID);
    printf("Node duoc tao: ID = %s, Title = %s, Author = %s, Code = %s, Ngay muon: %d/%d/%d\n",
        node->IdentifyID, node->Title, node->Author, node->Code,
        node->Start.tm_mday, node->Start.tm_mon, node->Start.tm_year);
    
    assert(strcmp(node->IdentifyID, "M001") == 0);
    assert(strcmp(node->Title, "BookA") == 0);
    assert(strcmp(node->Author, "AuthorA") == 0);
    assert(strlen(node->Code) == 6);
    free(node);
}

// Test them phieu muon vao bang bam
void test_InputBorrowing() {
    printf("Test: Them phieu muon vao bang bam\n");
    struct tm date = make_date(2, 5, 125);
    Borrowing *node = createBorrowingNode("M002", "BookA", "AuthorA", date);
    InputBorrowing(node);
    AVLNode *found = searchBorrowingTicket(node->Code);
    printf("Them xong, kiem tra tim kiem theo ma: %s\n", found ? "Tim thay" : "Khong thay");
    assert(found != NULL);
}

// Test tao phieu muon va cap nhat so luong sach, ban doc
void test_createBorrowingTicket() {
    printf("Test: Tao phieu muon va cap nhat so luong sach, so luong muon cua ban doc\n");
    // Tao ban doc va sach neu chua co
    Member mem;
    strcpy(mem.IdentifyID, "M003");
    mem.CurrentQuantity = 0;
    InputMember(&mem);

    Book book;
    strcpy(book.Title, "BookA");
    strcpy(book.Author, "AuthorA");
    book.Quantity = 2;
    insertBook(book);

    struct tm date = make_date(3, 5, 125);
    createBorrowingTicket("M003", "BookA", "AuthorA", date);

    Book *b = searchBook("BookA", "AuthorA");
    Member *m = SearchMember("M003");
    printf("So luong sach con lai: %d, So luong dang muon cua ban doc: %d\n", b->Quantity, m->CurrentQuantity);
    assert(b->Quantity == 1);
    assert(m->CurrentQuantity == 1);
}

// Test kiem tra qua han
void test_isBorrowingOverdue() {
    printf("Test: Kiem tra phieu muon co qua han khong\n");
    struct tm date = make_date(1, 0, 120); // Nam 2020, da qua han
    Borrowing *node = createBorrowingNode("M004", "BookA", "AuthorA", date);
    InputBorrowing(node);
    AVLNode *found = searchBorrowingTicket(node->Code);
    printf("Kiem tra qua han voi ngay muon cach day nhieu nam\n");
    int overdue = isBorrowingOverdue(found);
    printf("Ket qua: %s\n", overdue ? "QUA HAN" : "KHONG QUA HAN");
    assert(overdue == 1);
}

// Test xoa phieu muon va cap nhat so luong sach, ban doc
void test_deleteBorrowingTicket() {
    printf("Test: Xoa phieu muon va cap nhat so luong sach, ban doc\n");
    // Tao phieu muon moi
    struct tm date = make_date(5, 5, 125);
    Borrowing *node = createBorrowingNode("M005", "BookA", "AuthorA", date);
    InputBorrowing(node);

    Book *b = searchBook("BookA", "AuthorA");
    if (!b) {
        Book book;
        strcpy(book.Title, "BookA");
        strcpy(book.Author, "AuthorA");
        book.Quantity = 1;
        insertBook(book);
        b = searchBook("BookA", "AuthorA");
    }
    Member *m = SearchMember("M005");
    if (!m) {
        Member mem;
        strcpy(mem.IdentifyID, "M005");
        mem.CurrentQuantity = 1;
        InputMember(&mem);
    }

    printf("Xoa phieu muon co ma: %s\n", node->Code);
    deleteBorrowingTicket(node->Code);
    AVLNode *found = searchBorrowingTicket(node->Code);
    printf("Sau khi xoa, kiem tra lai: %s\n", found ? "Con ton tai" : "Da bi xoa");
    assert(found == NULL);
}

// Test doc va ghi file borrowing.csv
void test_Read_Write_BorrowingFile() {
    printf("Test: Ghi file borrowing.csv va doc lai\n");
    storeBorrowing();
    printf("Doc file borrowing.csv\n");
    ReadBorrowing("borrowing.csv");
    // Co the kiem tra lai bang bam bang searchBorrowingTicket voi mot ma cu the
}

int main() {
    printf("===== BAT DAU CHAY CAC TEST CHO borrowing.c =====\n\n");
    test_generateCode();
    printf("\n");
    test_createBorrowingNode();
    printf("\n");
    test_InputBorrowing();
    printf("\n");
    test_createBorrowingTicket();
    printf("\n");
    test_isBorrowingOverdue();
    printf("\n");
    test_deleteBorrowingTicket();
    printf("\n");
    test_Read_Write_BorrowingFile();
    printf("\n===== TAT CA CAC TEST DA CHAY XONG! =====\n");
    system("PAUSE");
    return 0;
}