#include <stdio.h>
#include <string.h>

int main() {
    FILE *fptr;
    if((fptr = fopen("./binary.txt", "r+")) == NULL) {
        printf("FILE NOT PRESENT\n");
        if((fptr = fopen("./binary.txt", "w+")) == NULL) {
            printf("FILE NOT WRITTEN\n");
            return 1;
        }
    }
    else {
        printf("FILE PRESENT\n");
        if((fptr = fopen("./binary.txt", "a+")) == NULL) {
            printf("FILE CANNOT BE READ");
            return 1;
        }
    }

    char string[100];
    char printed[100];
    printf("Enter word to be placed in file: ");
    scanf(" %s", string);
    strcat(string, "\n");
    fwrite(string, sizeof(char), strlen(string), fptr);
    rewind(fptr);
    while(fread(printed, sizeof(char), 100, fptr) != 0) {
        
    }
    fclose(fptr);
    return 0;
}