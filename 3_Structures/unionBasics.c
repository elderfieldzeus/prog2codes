#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef union {
    char name[30];      //N
    int age;            //A
    char location[40];  //L
    float GPA;          //G
}UNION;

typedef struct {
    UNION info;
    char choice;
}UnionManager;

void printUnion(UnionManager per);
void askUnion(UnionManager *per);

int main() {
    UnionManager per;
    //printUnion(per);
    do {
        askUnion(&per);
        printUnion(per);
    } while(toupper(per.choice) != 'E');
    printf("\nThanks for using!\n");
    printf("Size is only %d\n", (int)sizeof(per.info)); //40 (size of the biggest element which is location[40])
    return 0;
}

void printUnion(UnionManager per) {
    switch(toupper(per.choice)) {
        case 'N':
            printf("YOUR NAME IS: %s\n\n", per.info.name); break;
        case 'A':
            printf("YOUR AGE IS: %d\n\n", per.info.age); break;
        case 'L':
            printf("YOUR ADDRESS IS: %s\n\n", per.info.location); break;
        case 'G':
            printf("YOUR GPA IS: %.2f\n\n", per.info.GPA); break;
        default:
            break;
    }
}

void askUnion(UnionManager* per) {
    //system("clear"); //system("cls"); if on windows
    printf("What would you like to input:\n");
    printf("[N] Name\n");
    printf("[A] Age\n");
    printf("[L] Location / Address\n");
    printf("[G] GPA\n");
    printf("[E] Exit\n");
    printf("Answer: ");
    scanf(" %c", &per->choice);

    switch(toupper(per->choice)) {
        case 'N':
            printf("\nInput Name: ");
            scanf(" %[^\n]", per->info.name);
            break;
        case 'A':
            printf("\nInput Age: ");
            scanf("%d", &per->info.age);
            break;
        case 'L':
            printf("\nInput Location / Address: ");
            scanf(" %[^\n]", per->info.location);
            break;
        case 'G':
            printf("\nInput GPA: ");
            scanf("%f", &per->info.GPA);
            break;
        case 'E':
            break;
        default:
            printf("\nINVALID INPUT TRY AGAIN\n\n");
    }
}