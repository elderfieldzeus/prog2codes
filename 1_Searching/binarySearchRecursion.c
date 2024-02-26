#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int *arr, int size);
int binarySearch(int *arr, int low, int high, int elem);

int main () {
    int *arr, size, elem;
    printf("Enter size of array: ");
    scanf("%d", &size);
    arr = malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", arr + i);
    } 
    bubbleSort(arr, size);

    do{
        printf("Enter element to search: ");
        scanf("%d", &elem);
        printf("The element %d is %s\n", elem, binarySearch(arr, 0, size, elem) ? "found." : "not found.");
    }while(elem > 0);

    free(arr);
    return 0;
}

int binarySearch(int *arr, int low, int high, int elem) {
    if(low > high) return 0;

    int mid = (high + low) / 2;
    
    if(arr[mid] == elem) return 1;
    else{
        return elem > arr[mid] ? binarySearch(arr, mid + 1, high, elem) : binarySearch(arr, low, mid - 1, elem);
    }
}

void bubbleSort(int *arr, int size) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
