#include "book.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

AVLNode *HashtableBook[TABLE_SIZE];

void tolowerCase(char *str){
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

void loadBooksFromFile(const char *fileName){
    FILE *file = fopen(fileName, "r");

    if(!file){
        printf("Không thể mở file");
        return;
    }

    char line[256];
    while(fgets(line, sizeof(line), file)){
        Book book;
        char *token;

        line[strcspn(line, "\n")] = '\0';

        token = strtok(line, ",");
        if(token) strncpy(book.Title, token, sizeof(book.Title));
        else continue;

        token = strtok(NULL, ",");
        if(token) strncpy(book.Author, token, sizeof(book.Author));
        else continue;

        token = strtok(NULL, ",");
        if(token) book.Quantity = atoi(token);
        else continue;

        strncpy(book.Key, book.Title, sizeof(book.Key));
        strncat(book.Key, "_", sizeof(book.Key) - strlen(book.Key) - 1);
        strncat(book.Key, book.Author, sizeof(book.Key) - strlen(book.Key) - 1);

        tolowerCase(book.Key);
        tolowerCase(book.Title);
        tolowerCase(book.Author);

        book.Key[sizeof(book.Key) - 1] = '\0';
        book.Title[sizeof(book.Title) - 1] = '\0';
        book.Author[sizeof(book.Author) - 1] = '\0';

        insertBook(book);
    }

    fclose(file);
}

void generateKey(char *key, const char *title, cosnt char *author){
    char t[100], a[100];
    strncpy(t, title, sizeof(t));
    strncpy(a, author, sizeof(a));
    t[sizeof(t) - 1] = '\0';
    a[sizeof(a) - 1] = '\0';

    tolowerCase(t);
    tolowerCase(a);
    snprintf(key, 201, %s_%s, t, a);
}

int hashFunction(const char *key){
    unsigned long hash  = 5381;
    int c;
    while((c = *key++)){
        hash = ((hash << 5) + hash) + c;
    }

    return hash % TABLE_SIZE;
}

int compareBook(void *a, void *b){
    return strcmp(((Book*)a)->key, ((Book*)b)->key);
}

void insertBook(Book book){
    generateKey(book.Key, book.Title, book.Author);
    int index = hashFunction(book.Key);
    HashTableBook[index] = insertAVL(HashTableBook[index], &book, compareBook);
}

Book* searchBook(const char *title, const char *author){
    char key[100];
    generateKey(book.Key, book.Title, book.Author);
    int index = hashFunction(key);

    Book tmp;
    strcpy(tmp.Key, key);
    AVLNode *found = searchAVL(HashtableBook[index], &temp, compareBook);
    if(found) return (Book*)found->data;

    return NULL;
}

void deleteBook(const char *title, const char *author){
    char key[100];
    generateKey(key, title, author);
    int index = hashFunction(key);

    Book tmp;
    strcmp(tmp.Key, key);
    HashTableBook[index] = deleteAVL(HashTableBook[index], &tmp, compareBook);
}

void displayBook(AVLNode *root){
    if(!root){
        return;
    }

    displayBook(root->left);
    Book *b = (Book*)root->data;
    printf("Title: %s | Author: %s | Quantity: %d\n", b->Title, b->Author, b->Quantity);
    displayBook(root->right);
}

void displayAllBooks(){
    for(int i = 0; i < TABLE_SIZE; i++){
        if(HashTableBook[i]){
            printf("Hash Index [%d]: \n", i);
            displayBook(HashTableBook[i]);
        }
    }
}
