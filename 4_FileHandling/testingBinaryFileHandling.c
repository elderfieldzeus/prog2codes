//TESTING OUT FILE HANDLING FUNCTIONS

#include <stdio.h>
#include <string.h>

int main() {
    FILE *fptr;
    if((fptr = fopen("./binary.dat", "rb+")) == NULL) {
        printf("FILE NOT PRESENT\n");
        if((fptr = fopen("./binary.dat", "wb+")) == NULL) {
            printf("FILE NOT WRITTEN\n");
            return 1;
        }
    }
    else {
        printf("FILE PRESENT\n");
        if((fptr = fopen("./binary.dat", "ab+")) == NULL) {
            printf("FILE CANNOT BE READ");
            return 1;
        }
    }

    char string[100];
    char printed[100];
    printf("Enter word to be placed in file: ");
    scanf(" %s", string);
    strcat(string, "\0");
    fwrite(string, sizeof(char), strlen(string) + 1, fptr);
    rewind(fptr);
    int i = 0;
    while(fread(printed + i, sizeof(char), 1, fptr) != 0) {
        if(printed[i] == '\0') {
            printf("%s\n", printed);
            i = -1;
        }
        i++;
    }
    fclose(fptr);
    return 0;
}