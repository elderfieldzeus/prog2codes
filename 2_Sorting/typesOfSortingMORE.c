#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int arr[5];
}Numbers;

Numbers getNumbers();
int *makeCopy(Numbers array);
void printIt(int *array);
void bubbleSort(int *array);
void selectionSort(int *array);
void insertionSort(int *array);
void quickSort(int *array, int low, int high);//recursive function
void printQuickSort(int *array);
void mergeSort(int *array, int low, int high);//recursive function
void mergeArray(int *array, int low, int high);
void printMergeSort(int *array);

int main(){
    setbuf(stdout, NULL);
    int size = 5;
    Numbers array = getNumbers();

    bubbleSort:
        int *copyB = makeCopy(array);
        bubbleSort(copyB);
        free(copyB);

    selectionSort:
        int *copyS = makeCopy(array);
        selectionSort(copyS);
        free(copyS);

    insertionSort:
        int *copyI = makeCopy(array);
        insertionSort(copyI);
        free(copyI);

    quickSort:
        int *copyQ = makeCopy(array);
        quickSort(copyQ, 0, size-1);
        printQuickSort(copyQ);
        free(copyQ);

    mergeSort: 
        int *copyM = makeCopy(array);
        mergeSort(copyM, 0, size-1);
        printMergeSort(copyM);
        free(copyM);
}

Numbers getNumbers(){
    Numbers array;
    printf("\033[H\033[J");
    for(int i=0; i<5; i++){
        printf("Enter number %d: ", i+1);
        scanf("%d", &array.arr[i]);
    }
    return array;
}

int *makeCopy(Numbers array){
    int *copy = malloc(sizeof(int)*5);
    for(int i = 0; i < 5; i++){
        copy[i] = array.arr[i];
    }
    return copy;
}

void printIt(int *array){
    for(int i=0; i<5; i++){
        printf("%d ", array[i]);
    }
    printf("\b]");
}

void bubbleSort(int *array){
    //BUBBLE SORTING ALGORITHM BELOW
    for(int i=1; i<5; i++){
        for(int j=0; j<5-i; j++){
            if(array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }

    //PRINT
    printf("\nBUBBLE SORT: \t[");
    printIt(array);
}

void selectionSort(int *array){
    //SELECTION SORTING ALGORITHM BELOW
    for(int i = 0; i<5-1; i++){
        int min = i;
        for(int j=i+1; j<5; j++){
            if(array[j] < array[min]){
                min = j;
            }
        }
        if(min != i){
            int temp = array[min];
            array[min] = array[i];
            array[i] = temp;
        }
    }

    //PRINT
    printf("\nSELECTION SORT: [");
    printIt(array);
}

// void insertionSort(int *array){
//     //INSERTION ALGORITHM BELOW
//     for(int i = 1; i<5; i++){
//         int key = array[i];
//         int j = i-1;

//         while(j >= 0 && array[j] > key){
//             array[j+1] = array[j];
//             j = j-1;
//         }
//         array[j+1] = key;
//     }

//     //PRINT
//     printf("\nINSERTION SORT: [");
//     printIt(array);
// }

void insertionSort(int *array) {
    for(int i = 1; i < 5; i++) {
        for(int j = i; j > 0 && array[j] < array[j - 1]; j--) {
            int temp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = temp;
        }
    }

    //PRINT
    printf("\nINSERTION SORT: [");
    printIt(array);
}

void quickSort(int *array, int low, int high){
    //QUICK SORT ALGORITHM BELOW
    if (low < high){
        int j = low-1;
        int pivot = array[high];
        for(int i = low; i < high; i++){ //sort numbers so that partition is inbetween the numbers lesser than it and the numbers greater than it
            if(array[i] <= pivot){
                j++;
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }

        int temp = array[j + 1];
        array[j + 1] = array[high];
        array[high] = temp;

        int partitionIndex = j + 1; //partition index is equal to the position of the last swapped number (which is the last number)
        quickSort(array, low, partitionIndex-1); //sort below the partition
        quickSort(array, partitionIndex+1, high); //sort above the parition
    }
}

void printQuickSort(int *array){
    //PRINT
    printf("\nQUICK SORT: \t[");
    printIt(array);
}

void mergeSort(int *array, int low, int high){
    //MERGE SORT ALGORITHM BELOW
    if(low < high){
        int partition = low + (high - low) / 2;
        mergeSort(array, low, partition);
        mergeSort(array, partition + 1, high);
        mergeArray(array, low, high);
    }
}

void mergeArray(int *array, int low, int high){
    int partition = low + (high - low) / 2;
    int leftArraySize = partition - low + 1;
    int rightArraySize = high - partition;
    int leftArray[leftArraySize], rightArray[rightArraySize];

    for(int i = 0; i < leftArraySize; i++){
        leftArray[i] = array[low + i];
    }
    for(int i = 0; i < rightArraySize; i++){
        rightArray[i] = array[partition + 1 + i];
    }

    int leftRef = 0, rightRef = 0, i = low;
    while(leftRef < leftArraySize && rightRef < rightArraySize){
        if(leftArray[leftRef] <= rightArray[rightRef]){
            array[i] = leftArray[leftRef];
            leftRef++;
        }else{
            array[i] = rightArray[rightRef];
            rightRef++;
        }
        i++;
    }

    while(leftRef < leftArraySize){
        array[i] = leftArray[leftRef];
        i++;
        leftRef++;
    }

    while(rightRef < rightArraySize){
        array[i] = rightArray[rightRef];
        i++;
        rightRef++;
    }
}

void printMergeSort(int *array){
    //PRINT
    printf("\nMERGE SORT: \t[");
    printIt(array);
}