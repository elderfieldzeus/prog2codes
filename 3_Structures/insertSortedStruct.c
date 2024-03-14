#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct {
    int num[MAX];
    int count;
} LIST;

void insertSorted(LIST *x, int elem) {
    if(x->count < MAX) {
        int i;
        for(i = x->count - 1; i >= 0 && elem < x->num[i]; i--) {
            x->num[i + 1] = x->num[i];
        }
        x->num[i + 1] = elem;
        x->count++;
    }
};

void displayList(LIST x) {
    for(int i = 0; i < x.count; i++) {
        printf("%d ", x.num[i]);
    }
    printf("\n");
}

int main() {
    LIST x = {.count = 0};
    int num = 0;
    do {
        printf("Enter number: ");
        scanf("%d", &num);
        insertSorted(&x, num);
        displayList(x);
    } while(num != -1);
}