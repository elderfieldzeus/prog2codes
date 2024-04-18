#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} *DOUBLY;

void insertStart(DOUBLY *head, DOUBLY *tail, int num) {
    
    DOUBLY temp = (DOUBLY)malloc(sizeof(struct node));
    temp->data = num;

    if(*head == NULL || *tail == NULL) {
        *head = temp;
        *tail = temp;

        temp->next = NULL;
        temp->prev = NULL;
    }
    else {
        temp->next = *head;
        temp->prev = NULL;

        (*head)->prev = temp;

        *head = temp;
    }

}

void insertEnd(DOUBLY *head, DOUBLY *tail, int num) {
    
    DOUBLY temp = (DOUBLY)malloc(sizeof(struct node));
    temp->data = num;

    if(*head == NULL || *tail == NULL) {
        *head = temp;
        *tail = temp;

        temp->next = NULL;
        temp->prev = NULL;
    }
    else {
        temp->next = NULL;
        temp->prev = *tail;

        (*tail)->next = temp;

        *tail = temp;
    }

}

void displayHead(DOUBLY head) {
    DOUBLY curr = head;
    for(; curr != NULL; curr = curr->next) {
        printf("%d%s", curr->data, (curr->next == NULL) ? ".\n" : ", ");
    }
}

void displayTail(DOUBLY tail) {
    DOUBLY curr = tail;
    for(; curr != NULL; curr = curr->prev) {
        printf("%d%s", curr->data, (curr->prev == NULL) ? ".\n" : ", ");
    }
}

int main() {
    DOUBLY head = NULL, tail = NULL; //initialize

    insertStart(&head, &tail, 0);
    insertStart(&head, &tail, 1);
    insertStart(&head, &tail, 2);
    insertStart(&head, &tail, 3);
    insertEnd(&head, &tail, -1);
    insertEnd(&head, &tail, -2);

    displayHead(head);
    displayTail(tail);

    return 0;
}