#include <stdio.h>
#include <stdlib.h>

typedef struct name{
    char fName[20];
    char lName[20];
    char mi;
    int age;
    struct name *next; 
} NameList;

void initialize(NameList **head);
int askForSize();
void populateList(NameList **head);
void displayList(NameList *head);

int main() {
    NameList *head;
    initialize(&head);
    populateList(&head);
    displayList(head);
}

void initialize(NameList **head) {
    *head = NULL;
} 

int askForSize() {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);
    return size;
}

void populateList(NameList **head) {
    NameList *current = NULL;
    int headNull = 0;

    int size = askForSize();

    if(*head == NULL || size > 0) {
        current = (NameList *) malloc(sizeof(struct name));
        printf("First Name: ");
        scanf(" %s", current->fName);
        printf("Middle Initial: ");
        scanf(" %c", &current->mi);
        printf("Last Name: ");
        scanf(" %s", current->lName);
        printf("Age: ");
        scanf("%d", &current->age);
        current->next = NULL;
        *head = current;
        headNull = 1;
    }

    for(int i = (headNull) ? 1 : 0; i < size; i++) {
        NameList *newNode = (NameList*) malloc(sizeof(struct name));
        printf("\nFirst Name: ");
        scanf(" %s", newNode->fName);
        printf("Middle Initial: ");
        scanf(" %c", &newNode->mi);
        printf("Last Name: ");
        scanf(" %s", newNode->lName);
        printf("Age: ");
        scanf("%d", &newNode->age);
        newNode->next = NULL;
        current->next = newNode;
        current = current->next;
    }
}

void displayList(NameList *head) {
    if(head != NULL) {
        printf("              NAME               | AGE \n");
        for(NameList *current = head; current != NULL; current = current->next) {
            char name[50];
            sprintf(name, "%s, %s %c.", current->lName, current->fName, current->mi);
            printf("%-33s %-d\n", name, current->age);
        }
    }
}

