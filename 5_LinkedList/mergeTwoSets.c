#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *link;
}*SET;

SET mergeSets(SET a, SET b) {
    SET c = NULL;
    SET *travC = &c;

    while(a != NULL && b != NULL) {
        if(a->data < b->data) {
            SET temp = (SET)malloc(sizeof(struct node));
            temp->data = a->data;
            temp->link = NULL;
            (*travC) = temp;
            a = a->link;
        }
        else {
            SET temp = (SET)malloc(sizeof(struct node));
            temp->data = b->data;
            temp->link = NULL;
            (*travC) = temp;

            if(a->data == b->data) {
                a = a->link;
            }

            b = b->link;
        }

        travC = &(*travC)->link;
    }

    SET finisher = (a == NULL) ? b : a;

    while(finisher != NULL) {
        SET temp = (SET)malloc(sizeof(struct node));
        temp->data = finisher->data;
        temp->link = NULL;
        (*travC) = temp;
        finisher = finisher->link;
        travC = &(*travC)->link;
    }

    return c;
}

void sortSet(SET a) {
    for(SET key = a; key != NULL; key = key->link) {
        SET smallest = key;
        
        for(SET trav = key->link; trav != NULL; trav = trav->link) {
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

SET populateList() {
    SET new = NULL;
    SET *ptrNew = &new;

    int size;

    printf("\nEnter size: ");
    scanf("%d", &size);
    for(int i = 0; i < size; i++) {
        SET temp = (SET)malloc(sizeof(struct node));
        printf("Enter number: ");
        scanf("%d", &temp->data);
        temp->link = NULL;
        (*ptrNew) = temp;
        ptrNew = &(*ptrNew)->link;
    }

    return new;
}

void displayList(SET s) {
    for(SET trav = s; trav != NULL; trav = trav->link) {
        printf("%d%s", trav->data, (trav->link != NULL) ? ", " : ".\n");
    }
}

int main() {
    SET a = populateList();
    SET b = populateList();

    sortSet(a);
    sortSet(b);

    printf("Set a: ");
    displayList(a);

    printf("Set b: ");
    displayList(b);

    SET c = mergeSets(a, b);

    printf("Set c: ");
    displayList(c);
    return 0;
}