#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *getInput(int *size);
void bubbleSortLightUp(int arr[], int size);
void bubbleSortHeavyDown(int arr[], int size);
void insertionSortShift(int arr[], int size);
void insertionSortSwap(int arr[], int size);
void selectionSort(int arr[], int size);
void display(int arr[], int size);

int main() {
    int size;
    int *arr = getInput(&size);
    int copy[size];
    printf("\nOriginal array: \t\t");
    display(arr, size);
    printf("\n");

    memcpy(copy, arr, size * sizeof(int));
    bubbleSortLightUp(copy, size);
    printf("Bubble sort (light up): \t");
    display(copy, size);

    memcpy(copy, arr, size * sizeof(int));
    bubbleSortHeavyDown(copy, size);
    printf("Bubble sort (heavy down): \t");
    display(copy, size);

    memcpy(copy, arr, size * sizeof(int));
    insertionSortShift(copy, size);
    printf("Insertion sort (shift): \t");
    display(copy, size);

    memcpy(copy, arr, size * sizeof(int));
    insertionSortSwap(copy, size);
    printf("Insertion sort (swap): \t\t");
    display(copy, size);

    memcpy(copy, arr, size * sizeof(int));
    selectionSort(copy, size);
    printf("Selection sort: \t\t");
    display(copy, size);

    free(arr);
    return 0;
}

int *getInput(int *size) {
    int *arr;
    printf("Enter size: ");
    scanf("%d", size);
    arr = (int*)malloc(sizeof(int) * (*size));
    for(int i = 0; i < *size; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", arr + i);
    }
    return arr;
} 

void display(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d%s", arr[i], i == size - 1 ? ".\n" : ", ");
    }
}

void bubbleSortLightUp(int arr[], int size) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = size - 1; j > i; j--) {
            if(arr[j] < arr[j - 1]) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }
}

void bubbleSortHeavyDown(int arr[], int size) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - 1 - i; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSortShift(int arr[], int size) {
    for(int i = 1; i < size; i++) {
        int key = arr[i];
        int j;
        for(j = i; j > 0 && key < arr[j - 1]; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = key;
    }
}

void insertionSortSwap(int arr[], int size) {
    for(int i = 1; i < size; i++) {
        for(int j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
            int temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
        }
    }
}

void selectionSort(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        int smallestIndex = i;
        for(int j = i + 1; j < size; j++) {
            if(arr[j] < arr[smallestIndex]) {
                smallestIndex = j;
            }
        }
        if(smallestIndex != i) {
            int temp = arr[smallestIndex];
            arr[smallestIndex] = arr[i];
            arr[i] = temp;
        }
    }
}