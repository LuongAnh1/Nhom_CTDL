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

void insertNode(char IdentifyID[12], char Title[100], char Author[100], bool order){
    Book *book = searchBook(Title, Author);

    Queue *newNode = makeNode(IdentifyID, Title, Author, order);

    Queue *head;

    if(newNode->Order == 1){
        head = book->queue1;
    }
    else{
        head = book->queue0;
    }

    if(head == NULL){
        head = newNode;
        return;
    }

    Queue *tmp = head;
    while(tmp->next != NULL){
        tmp = tmp->next;
    }

    tmp->next = newNode;
}

