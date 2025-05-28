#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h" 

int main() {
    // Kiểm thử hàm băm
    char *keys[] = {"Alice", "Bob", "Charlie", "David", "Eve", "Zoe", "Aaron"};
    int n = sizeof(keys) / sizeof(keys[0]);

    printf("==> Kiem thu ham bam:\n");
    for (int i = 0; i < n; i++) {
        unsigned int h = hash(keys[i]);
        printf("Hash(\"%s\") = %u\n", keys[i], h);
    }

    // Kiểm thử hàm so sánh chuỗi
    printf("\n==> Kiem thu ham so sanh chuoi:\n");

    char *a = "Hello";
    char *b = "Hello";
    char *c = "World";

    printf("compareString(\"%s\", \"%s\") = %d\n", a, b, compareString(a, b)); // Kỳ vọng: 0
    printf("compareString(\"%s\", \"%s\") = %d\n", a, c, compareString(a, c)); // Kỳ vọng: < 0
    printf("compareString(\"%s\", \"%s\") = %d\n", c, a, compareString(c, a)); // Kỳ vọng: > 0
    system("PAUSE");
    return 0;
}
