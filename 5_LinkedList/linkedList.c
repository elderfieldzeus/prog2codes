#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_STRING 100

typedef struct linkedList{
    char* listedName;
    struct linkedList *next;
}LinkedList;

void init(LinkedList **head);
char* askForInput();
void addNode(LinkedList **head, char *name);
void viewNodes(LinkedList *head);
int again();

int main(){
    LinkedList *head;
    char *name;
    int tryAgain;

    init(&head); //head = NULL
    do{
        name = askForInput();
        addNode(&head, name);
        viewNodes(head);
        tryAgain = again();
    }while(tryAgain);
}

void init(LinkedList **head){
    *head = NULL;
}

char* askForInput(){
    char *name = malloc(sizeof(char) * MAX_STRING);
    printf("\033[H\033[J");
    printf("Enter name to add: ");
    scanf(" %99[^\n]", name);
    return name;
}

void addNode(LinkedList **head, char *name){
    LinkedList *current = *head;
    LinkedList *temp;

    if(*head == NULL){
        *head = malloc(sizeof(struct linkedList));
        current = *head;
    }
    else{
        for(current; current->next != NULL; current = current->next);
        current->next = malloc(sizeof(struct linkedList));
        current = current->next;
    }

    current->listedName = malloc(sizeof(struct linkedList));
    strcpy(current->listedName, name);
    current->next = NULL;
}

void viewNodes(LinkedList *head){
    if(head == NULL){
        printf("HEAD IS NULL\n");
    }
    printf("\n");
    for(LinkedList *current = head; current != NULL; current = current->next){
        printf("%s\n", current->listedName);
    }

    printf("\n");
}

int again(){
    char ans;
    printf("Would you like to add another name? [y/n]: ");
    scanf(" %c", &ans);

    if(tolower(ans) == 'y'){
        return 1;
    }
    
    return 0;
}