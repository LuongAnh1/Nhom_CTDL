#include "book.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

//hàm chuyển về các ký tự thường
void tolowerCase(char *str){
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

void trim(char *str) {
    // Xóa khoảng trắng đầu
    while(isspace((unsigned char)*str)) str++;
    // Xóa khoảng trắng cuối
    char *end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    *(end+1) = '\0';
}

//đọc dữ liệu từ file csv
void loadBooksFromFile(const char *fileName){
    FILE *file = fopen(fileName, "r");
    if(!file){
        printf("Không thể mở file\n");
        return;
    }

    char line[256];
    while(fgets(line, sizeof(line), file)){
        Book book;
        char *token;

        // Xử lý ký tự thừa 
        line[strcspn(line, "\n")] = '\0';

        // Tách title
        token = strtok(line, ",");
        if(token) {
            strncpy(book.Title, token, sizeof(book.Title) - 1);
            book.Title[sizeof(book.Title) - 1] = '\0';
        } else continue;

        // Tách author
        token = strtok(NULL, ",");
        if(token) {
            strncpy(book.Author, token, sizeof(book.Author) - 1);
            book.Author[sizeof(book.Author) - 1] = '\0';
        } else continue;

        // Tách quantity
        token = strtok(NULL, ",");
        if(token) book.Quantity = atoi(token);
        else continue;

        // Chuẩn hóa các thông tin
        tolowerCase(book.Title);
        tolowerCase(book.Author);

        // Chèn sách
        insertBook(book);
    }

    fclose(file);
}


//tạo key từ title và author: title_author
void generateKey(char *key, const char *title, const char *author){
    char t[100], a[100];
    strncpy(t, title, sizeof(t));
    strncpy(a, author, sizeof(a));
    t[sizeof(t) - 1] = '\0';
    a[sizeof(a) - 1] = '\0';

    tolowerCase(t);
    tolowerCase(a);
    snprintf(key, 201, "%s_%s", t, a);
}

//hàm hash
int hashFunction(const char *key){
    unsigned long hash  = 5381;
    int c;
    while((c = *key++)){
        hash = ((hash << 5) + hash) + c;
    }

    return hash % TABLE_SIZE;
}

//hàm so sánh book
int compareBook(void *a, void *b){
    return strcmp(((Book*)a)->Key, ((Book*)b)->Key);
}

//chèn sách vào AVL
void insertBook(Book book){
    trim(book.Title);
    trim(book.Author);
    tolowerCase(book.Title);
    tolowerCase(book.Author);
    generateKey(book.Key, book.Title, book.Author);
    int index = hashFunction(book.Key);

    Book *found = searchBook(book.Title, book.Author);
    if (!found) {
        Book *newBook = malloc(sizeof(Book));
        if (newBook) {
            *newBook = book;
            HashTableBook[index] = insertAVL(HashTableBook[index], newBook, compareBook);
        }
    } else {
        found->Quantity += book.Quantity; // hoặc bỏ qua nếu không muốn cộng dồn
    }
}

//tìm kiêm sách 
Book* searchBook(const char *title, const char *author){
    char t[100], a[100];
    strncpy(t, title, sizeof(t)-1); t[sizeof(t)-1] = '\0';
    strncpy(a, author, sizeof(a)-1); a[sizeof(a)-1] = '\0';
    trim(t); trim(a);
    tolowerCase(t); tolowerCase(a);

    char key[100];
    generateKey(key, t, a);
    int index = hashFunction(key);

    Book tmp;
    strcpy(tmp.Key, key);
    AVLNode *found = searchAVL(HashTableBook[index], &tmp, compareBook);
    if(found) return (Book*)found->data;
    return NULL;
}

//xóa sách khỏi AVL Tree
void deleteBook(const char *title, const char *author){
    char key[100];
    generateKey(key, title, author);
    //lấy vị trí
    int index = hashFunction(key);

    Book tmp;
    strcpy(tmp.Key, key);
    //xóa
    HashTableBook[index] = deleteAVL(HashTableBook[index], &tmp, compareBook);
}

//hàm hiển thị thông tin của sách
void displayBook(AVLNode *root){
    if(!root){
        return;
    }

    displayBook(root->left);
    Book *b = (Book*)root->data;
    printf("Title: %s | Author: %s | Quantity: %d\n", b->Title, b->Author, b->Quantity);
    displayBook(root->right);
}

//hàm hiển thị toàn bộ thông tin sách của thư viện
void displayAllBooks(){
    for(int i = 0; i < TABLE_SIZE; i++){
        if(HashTableBook[i]){
            // printf("Hash Index [%d]: \n", i);
            displayBook(HashTableBook[i]);
        }
    }
}

void saveBookNode(FILE *file, AVLNode *root) {
    if (!root) return;
    saveBookNode(file, root->left);
    Book *b = (Book*)root->data;
    fprintf(file, "%s,%s,%d\n", b->Title, b->Author, b->Quantity);
    saveBookNode(file, root->right);
}

void saveToFile(const char *fileName){
    FILE *file = fopen(fileName, "w");

    if(!file){
        printf("Không thể mở file.");
        return;
    }

    for(int i = 0; i < TABLE_SIZE; i++){
        if(HashTableBook[i]){
            saveBookNode(file, HashTableBook[i]);
        }
    }

    fclose(file);

    printf("Đã lưu toàn bộ sách vào file.");
}
