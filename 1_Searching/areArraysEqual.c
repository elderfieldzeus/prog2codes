#include <stdio.h>
#include <stdlib.h>

void *getInput(int size);
int isEqual(int a[], int b[], int size);

int main() {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);
    int *arr1 = getInput(size);
    int *arr2 = getInput(size);
    printf("Both arrays %s equal.", (isEqual(arr1, arr2, size)) ? "are" : "are not");
    free(arr1);
    free(arr2);
    return 0;
}

void *getInput(int size) {
    int *arr = malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", arr + i);
    }
    printf("\n");
    return arr;
}

int isEqual(int a[], int b[], int size) {
    int i, j;
    for(i = 0, j = 0; i < size && j < size; i++) {
        for(j = 0; j < size && a[i] != b[j]; j++);
    }
    return (j == size) ? 0 : 1;
}