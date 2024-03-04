#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int data;
    struct node *next;
}*LIST;

void init(LIST *head) {
    *head = NULL;
}

void insertFirst(LIST *head, int num) {
    LIST temp = (LIST)malloc(sizeof(struct node));
    temp->data = num;
    temp->next = *head;
    *head = temp;
}

void insertLast(LIST *head, int num) {
    LIST *curr = NULL, temp;
    for(curr = head; (*curr) != NULL; curr = &(*curr)->next); //curr points to address of head, then address of next, then next, and so on.
    temp = (LIST)malloc(sizeof(struct node));
    temp->data = num;
    temp->next = NULL;
    (*curr) = temp;
}

void insertNthIndex(LIST *head, int num, int index) {
    LIST *curr = NULL, temp;
    int i;
    for(i = 0, curr = head; i < index && (*curr) != NULL; i++, curr = &(*curr)->next);

    if(i < index) {
        printf("Index exceeds linked list size\n");
    }
    else {
        temp = (LIST)malloc(sizeof(struct node));
        temp->data = num;
        temp->next = (*curr);
        (*curr) = temp;
    }
}

void display(LIST head) {
    for(LIST trav = head; trav != NULL; trav = trav->next) {
        printf("%d%s", trav->data, trav->next == NULL ? ".\n": ", ");
    }
}

void freeAll(LIST *head) {
    LIST temp;
    while((*head) != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main() {
    LIST head;
    init(&head);
    insertFirst(&head, 3);
    insertLast(&head, 5);
    insertNthIndex(&head, 4, 1);
    display(head);
    freeAll(&head);
    return 0;
}