#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node {
    char *name;
    struct node *next;
}*LIST;

enum CHOICES {
    INSERTFRONT = 1, INSERTLAST, DELETE, DISPLAY
};

int homePage();
char *askForName();
void capitalize(char *name);
void insertFront(LIST *head);
void insertLast(LIST *head);
void delete(LIST *head);
void display(LIST head);
void freeAll(LIST *head);

int main() {
    LIST head = NULL;
    int choice;
    do{
        choice = homePage();
        printf("\033[H\033[J");
        switch(choice) {
            case INSERTFRONT: insertFront(&head); break;
            case INSERTLAST: insertLast(&head); break;
            case DELETE: delete(&head); break;
            case DISPLAY: display(head); break;
            default: printf("THANKS FOR USING"); choice = -1;
        }
        printf("\n");
    }while(choice != -1);
    freeAll(&head);
}

int homePage() {
    int choice;
    printf("LIST POINTER MENU:\n");
    printf("Choose an option:\n");
    printf("[1] Insert name first\n");
    printf("[2] Insert name last\n");
    printf("[3] Delete name\n");
    printf("[4] Display names\n");
    printf("[?] Exit\n");
    printf("Choice: ");
    scanf("%d", &choice);
    return choice;
}

char *askForName() {
    char *name = malloc(sizeof(char) * 100);
    scanf(" %[^\n]", name);
    name = realloc(name, sizeof(char) * (strlen(name) + 1));
    capitalize(name);
    return name;
}

void capitalize(char *name) {
    *name = toupper(*name);
    for(int i = 1; *(name + i) != '\0'; i++) {
        *(name + i) = tolower(*(name + i));
    }
}

void insertFront(LIST *head) {
    LIST temp = malloc(sizeof(struct node));
    temp->next = *head;
    printf("Enter name to be inserted in front: ");
    temp->name = askForName();
    *head = temp;
}

void insertLast(LIST *head) {
    if(*head == NULL) {
        *head = malloc(sizeof(struct node));
        printf("Enter name to be inserted at the end: ");
        (*head)->name = askForName();
        (*head)->next = NULL;
    }
    else {
        LIST curr = *head;
        for(curr; curr->next != NULL; curr = curr->next);
        curr->next = malloc(sizeof(struct node));
        curr = curr->next;
        printf("Enter name to be inserted at the end: ");
        curr->name = askForName();
        curr->next = NULL;
    }
}

void delete(LIST *head) {
    if(*head == NULL) {
        printf("(THERE IS NOTHING TO DELETE)\n");
        return;
    }

    printf("Enter name to be deleted: ");
    char *name = askForName();

    LIST prev, curr;
    for(prev = NULL, curr = *head; curr != NULL && (strcmp(name, curr->name) != 0); prev = curr, curr = curr->next);
    if(prev == NULL) {
        LIST temp = *head;
        *head = (*head)->next;
        free(temp->name);
        free(temp);
        printf("NAME DELETED!\n");
    }
    else if(curr != NULL) {
        prev->next = curr->next;
        free(curr->name);
        free(curr);
        printf("NAME DELETED!\n");
    } 
    else {
        printf("NAME IS NOT FOUND\n");
    }
}

void display(LIST head) {
    if(head == NULL) {
        printf("(EMPTY)\n");
    }
    else{
        for(LIST curr = head; curr != NULL; curr = curr->next) {
            printf("%s\n", curr->name);
        }
    }
}

void freeAll(LIST *head) {
    if(*head == NULL) return;
    LIST prev, curr;
    for(prev = *head, curr = (*head)->next;; prev = curr, curr = curr->next) {
        free(prev->name);
        free(prev);
        if(curr == NULL) break;
    }
}