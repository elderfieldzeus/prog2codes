#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    int number;
    struct node *next;
    struct node *prev;
}Doubly;

void insertEnd(Doubly **head, Doubly **tail, int insert);
void insertStart(Doubly **head, Doubly **tail, int insert);
void displayStraight(Doubly *head);
void displayReversed(Doubly *tail);
void freeAll(Doubly **head);

int main() {
    Doubly *head, *tail;
    head = tail = NULL;
    insertEnd(&head, &tail, 3);
    insertEnd(&head, &tail, 4);
    insertEnd(&head, &tail, 5);
    insertStart(&head, &tail, 2);
    insertStart(&head, &tail, 1);
    displayStraight(head);
    displayReversed(tail);
    freeAll(&head);
    return 0;
}

void insertEnd(Doubly **head, Doubly **tail, int insert) {
    Doubly *temp = (Doubly*)malloc(sizeof(struct node));
    temp->number = insert;
    if(*head == NULL) {
        *head = *tail = temp;
        (*head)->prev = (*head)->next = (*tail)->prev = (*tail)->next = NULL;
    }
    else {
        (*tail)->next = temp;
        temp->prev = (*tail);
        *tail = temp;
        (*tail)->next = NULL;
    }
}

void insertStart(Doubly **head, Doubly **tail, int insert) {
    Doubly *temp = (Doubly *)malloc(sizeof(struct node));
    temp->number = insert;
    if(*tail == NULL) {
        *tail = *head = temp;
        (*tail)->next = (*tail)->prev = (*head)->next = (*head)->prev = NULL;
    }
    else {
        (*head)->prev = temp;
        temp->next = (*head);
        *head = temp;
        (*head)->prev = NULL;
    }
}

void displayStraight(Doubly *head) {
    printf("Straight: ");
    for(Doubly *curr = head; curr != NULL; curr = curr->next) {
        printf("%d ", curr->number);
    }
    printf("\n");
}

void displayReversed(Doubly *tail) {
    printf("Reversed: ");
    for(Doubly *curr = tail; curr != NULL; curr = curr->prev) {
        printf("%d ", curr->number);
    }
    printf("\n");
}

void freeAll(Doubly **head) {
    while((*head) != NULL) {
        Doubly *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}