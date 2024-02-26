#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *next;
}*LIST;

LIST getInput();
void reverseList(LIST *head);
void printList(LIST head);
void freeAll(LIST head);

int main() {
    LIST head = getInput();
    printList(head);
    reverseList(&head);
    printList(head);
    freeAll(head);
    return 0;
}

LIST getInput() {
    int size;
    LIST newNode = (LIST)malloc(sizeof(struct node));
    LIST temp = newNode;
    printf("Enter size: ");
    scanf("%d", &size);

    if(size == 0) return NULL;

    for(int i = 0; i < size; i++) {
        printf("Enter data [%d]: ", i);
        scanf("%d", &temp->data);
        if(i < size - 1){
            temp->next = (LIST)malloc(sizeof(struct node));
            temp = temp->next;
        }
    }
    temp->next = NULL;
    return newNode;
}

void reverseList(LIST *head) {
    if(*head == NULL) return;

    LIST curr, prev, after;
    curr = *head, prev = NULL, after = (*head)->next;
    while(after != NULL) {
        curr->next = prev;
        prev = curr;
        curr = after;
        after = after->next;
    }

    curr->next = prev;
    *head = curr;
}

void printList(LIST head) {
    if(head == NULL) {
        printf("HEAD IS EMPTY\n");
        return;
    }

    printf("\nElements in the linked list:\n");
    for(LIST curr = head; curr != NULL; curr = curr->next) {
        printf("%d\n", curr->data);
    }
}

void freeAll(LIST head) {
    if(head == NULL) return;

    LIST curr, prev;
    for(curr = head->next, prev = head; curr != NULL; prev = curr, curr = curr->next) {
        free(prev);
    }
    free(prev);
}
