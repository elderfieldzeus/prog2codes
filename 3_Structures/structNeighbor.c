/*
TEST CODE TO SEE IF PTR ARITHMETIC READS ALL ELEMENTS AND NOT JUST THE FIRST STRING
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char first[5];
    char second[5];
    char third[5];
}TEST;

int main() {
    TEST names = {"zeus", "meow", "grr"};
    char *ptr = names.first;
    printf("Size of struct is %d\n", (int)sizeof(names));
    for(int i = 0; i < (int)sizeof(names); i++) {
        printf("%c", *(ptr + i) == '\0' ? '?' : *(ptr + i));
    }
    return 0;
}