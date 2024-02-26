#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int *arr, int size);
int binarySearch(int *arr, int size, int elem);

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
        printf("The element %d is %s\n", elem, binarySearch(arr, size, elem) ? "found." : "not found.");
    }while(elem > 0);

    free(arr);
    return 0;
}

int binarySearch(int *arr, int size, int elem) { // 1 2 3 4 5
    int low = 0, high = size - 1, mid; // low = 0, high = 4
    mid = (high + low) / 2; // mid = 2
    while(low < high && elem != arr[mid]) { // 0 < 4 && 6 != 3 // 3 < 4 && 6 != 4 // 4 < 4 && 6 != 5
        elem > arr[mid] ? (low = mid + 1) : (high = mid - 1); // low = 2 + 1 = 3 // low = 3 + 1 = 4 
        mid = (high + low) / 2; //mid = (3 + 4) / 2 = 3  //mid = (4 + 4) / 2 = 4
    }
    return arr[mid] == elem ? 1 : 0;
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
