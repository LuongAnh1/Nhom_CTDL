#ifndef QUEUE_H
#define QUEUE_H

#include "data.h"

void insertNode(char IdentifyID[12], char Title[100], char Author[100], bool order);
void deleteNode();

void traverse();

Queue* searching();

#endif