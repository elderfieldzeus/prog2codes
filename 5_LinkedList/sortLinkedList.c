#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *link;
}*LIST;

int *getElem(int *size) {
    int stat[] = {5, 9, 1, 3, 7};
    *size = sizeof(stat) / sizeof(stat[0]);

    int *new = (int*)malloc(sizeof(int) * (*size));

    memcpy(new, stat, sizeof(int) * (*size));

    return new;
}

LIST populateList(int arr[], int size) {
    LIST head = NULL;
    LIST *curr = &head;

    for(int i = 0; i < size; i++, curr = &(*curr)->link) {
        LIST temp = (LIST) malloc(sizeof(struct node));
        temp->data = arr[i];
        temp->link = NULL;
        (*curr) = temp;
    }

    return head;
}

void displayList(LIST head) {
    for(LIST curr = head; curr != NULL; curr = curr->link) {
        printf("%d%s", curr->data, (curr->link == NULL) ? ".\n" : ", ");
    }
}

void sortList(LIST head) {
    for(LIST key = head; key != NULL; key = key->link) {
        LIST smallest = key;
        
        for(LIST trav = key->link; trav != NULL; trav = trav->link) {
            if(trav->data < smallest->data) {
                smallest = trav;
            }
        }

        if(key != smallest) {
            int temp = key->data;
            key->data = smallest->data;
            smallest->data = temp;
        }

    }
}

void freeList(LIST head) {
    while(head != NULL) {
        LIST temp = head;
        head = head->link;
        free(temp);
    }
}

int main() {
    int size; 
    int *arr = getElem(&size);
    LIST head = populateList(arr, size);

    displayList(head);

    sortList(head);

    displayList(head);

    free(arr);
    freeList(head);

    return 0;
}