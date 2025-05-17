#include "hash.h"
#define TABLE_SIZE 10

unsigned int hash(char *str) {
    unsigned long long hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % TABLE_SIZE;
}
// Hàm so sánh xâu
int compareString(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}