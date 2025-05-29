#include "Book.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

AVLNode *HashTableBook[TABLE_SIZE] = {NULL};
// Ham test tolowerCase
void test_tolowerCase() {
    printf("Test: Chuyen chuoi ve chu thuong\n");
    printf("Dau vao: \"HeLLo\"\n");
    char s1[] = "HeLLo";
    tolowerCase(s1);
    printf("Sau khi xu ly: \"%s\"\n", s1);
    assert(strcmp(s1, "hello") == 0);
}

// Ham test trim
void test_trim() {
    printf("Test: Xoa khoang trang dau/cuoi chuoi\n");
    printf("Dau vao: \"   hello   \"\n");
    char s1[] = "   hello   ";
    trim(s1);
    printf("Sau khi xu ly: \"%s\"\n", s1);
    assert(strcmp(s1, "hello") == 0);
}

// Ham test generateKey
void test_generateKey() {
    printf("Test: Tao key tu title va author\n");
    printf("Dau vao: title = \"   HeLLo\", author = \"   WorLD   \"\n");
    char key[201];
    generateKey(key, "   HeLLo", "   WorLD   ");
    printf("Key sinh ra: \"%s\"\n", key);
    assert(strcmp(key, "hello_world") == 0);
}

// Ham test insertBook va searchBook
void test_insert_and_searchBook() {
    printf("Test: Them sach va tim sach\n");
    printf("Dau vao: Title = \"TestBook\", Author = \"TestAuthor\", Quantity = 5\n");
    Book book;
    strcpy(book.Title, "TestBook");
    strcpy(book.Author, "TestAuthor");
    book.Quantity = 5;

    insertBook(book);

    Book *found = searchBook("TestBook", "TestAuthor");
    if(found) {
        printf("Tim thay sach: Title = \"%s\", Author = \"%s\", Quantity = %d\n", found->Title, found->Author, found->Quantity);
    } else {
        printf("Khong tim thay sach!\n");
    }
    assert(found != NULL);
    assert(strcmp(found->Title, "testbook") == 0);
    assert(strcmp(found->Author, "testauthor") == 0);
    assert(found->Quantity == 5);
}

// Ham test cong don Quantity khi them sach trung
void test_insert_duplicateBook() {
    printf("Test: Them sach trung va kiem tra Quantity\n");
    printf("Dau vao lan 1: Title = \"Duplicate\", Author = \"Author\", Quantity = 2\n");
    Book book;
    strcpy(book.Title, "Duplicate");
    strcpy(book.Author, "Author");
    book.Quantity = 2;
    insertBook(book);

    printf("Dau vao lan 2: Title = \"Duplicate\", Author = \"Author\", Quantity = 3\n");
    book.Quantity = 3;
    insertBook(book);

    Book *found = searchBook("Duplicate", "Author");
    if(found) {
        printf("Sau khi them 2 lan, so luong la: %d\n", found->Quantity);
    }
    assert(found && found->Quantity == 5);
}

// Ham test deleteBook
void test_deleteBook() {
    printf("Test: Xoa sach\n");
    printf("Dau vao: Title = \"DelBook\", Author = \"DelAuthor\", Quantity = 1\n");
    Book book;
    strcpy(book.Title, "DelBook");
    strcpy(book.Author, "DelAuthor");
    book.Quantity = 1;
    insertBook(book);

    printf("Xoa sach: Title = \"DelBook\", Author = \"DelAuthor\"\n");
    deleteBook("DelBook", "DelAuthor");
    Book *found = searchBook("DelBook", "DelAuthor");
    if(found) {
        printf("Xoa khong thanh cong!\n");
    } else {
        printf("Sach da duoc xoa khoi he thong.\n");
    }
    assert(found == NULL);
}

// Ham test load va save file
void test_load_and_save_file() {
    printf("Test: Doc sach tu file va luu sach ra file\n");
    printf("Tao file test_books.txt voi noi dung mau\n");
    FILE *f = fopen("test_books.txt", "w");
    fprintf(f, "Book1;Author1;10\nBook2;Author2;5\n");
    fclose(f);

    printf("Doc sach tu file test_books.txt\n");
    loadBooksFromFile("test_books.txt");
    Book *b1 = searchBook("Book1", "Author1");
    Book *b2 = searchBook("Book2", "Author2");
    if(b1) printf("Tim duoc Book1: Quantity = %d\n", b1->Quantity);
    if(b2) printf("Tim duoc Book2: Quantity = %d\n", b2->Quantity);
    assert(b1 && b1->Quantity == 10);
    assert(b2 && b2->Quantity == 5);

    printf("Luu du lieu sach ra file test_out.txt\n");
    saveToFile("test_out.txt");
    printf("Ban co the mo test_out.txt de kiem tra ket qua.\n");
}

int main() {
    printf("===== BAT DAU CHAY CAC TEST CHO Book.c =====\n\n");
    test_tolowerCase();
    printf("\n");
    test_trim();
    printf("\n");
    test_generateKey();
    printf("\n");
    test_insert_and_searchBook();
    printf("\n");
    test_insert_duplicateBook();
    printf("\n");
    test_deleteBook();
    printf("\n");
    test_load_and_save_file();
    printf("\n===== TAT CA CAC TEST DA CHAY XONG! =====\n");
    system("PAUSE");
    return 0;
}