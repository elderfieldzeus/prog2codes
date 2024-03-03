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
void freeAll(NameList **head);

int main() {
    NameList *head;
    initialize(&head);
    populateList(&head);
    displayList(head);
    populateList(&head);
    displayList(head);
    freeAll(&head);
    return 0;
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

void askForInput(NameList **node) {
    printf("First Name: ");
    scanf(" %s", (*node)->fName);
    printf("Middle Initial: ");
    scanf(" %c", &(*node)->mi);
    printf("Last Name: ");
    scanf(" %s", (*node)->lName);
    printf("Age: ");
    scanf("%d", &(*node)->age);
    printf("\n");
}

void populateList(NameList **head) {
    NameList *prev = NULL, *curr;
    for(curr = *head; curr != NULL; prev = curr, curr = curr->next);

    int size = askForSize(), prevIsNull = 0;

    if(prev == NULL && size > 0) {
        prev = (NameList*) malloc(sizeof(struct name));
        prev->next = NULL;
        askForInput(&prev);
        *head = prev;
        prevIsNull = 1;
    }

    for(int i = (prevIsNull == 0) ? 0 : 1; i < size; i++) {
        NameList *temp = (NameList*) malloc(sizeof(struct name));
        temp->next = NULL;
        askForInput(&temp);
        prev->next = temp;
        prev = prev->next;
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
        printf("\n");
    }
}

void freeAll(NameList **head) {
    while((*head) != NULL) {
        NameList *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}