#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50

typedef struct {
    char FName[16];
    char LName[20];
    char MI;
}Nametype;

typedef struct {
    Nametype name;
    unsigned ID;
    char Course[8];
    int Year;
}Studtype;

typedef struct {
    Studtype Stud[SIZE];
    int count;
}Studlist;

Studlist initList();
void displayList(Studlist L);
Studtype getInput();
void populateList(Studlist *pL, int n);
void sortByID(Studlist *pL);

int main() {
    Studlist L = initList();
    int size;
    printf("\033[H\033[J");
    printf("Enter size: ");
    scanf("%d", &size);
    populateList(&L, size);
    sortByID(&L);
    displayList(L);
    return 0;
}

Studlist initList() {
    Studlist L = {.count = 0};
    return L;
}

void displayList(Studlist L) {
    if(L.count > 0) {
        char header[] = "  ID NUMBER  |                  NAME                  |  COURSE  |  YEAR  ";
        printf("\033[H\033[J");
        printf("%s\n", header);
        for(int i = 0; i < strlen(header); i++) printf("-");
        for(int i = 0; i < L.count; i++) {
            char name[100];
            sprintf(name, "%s, %s %c.", L.Stud[i].name.LName, L.Stud[i].name.FName, L.Stud[i].name.MI);
            printf("\n%-13u %-40s %-10s %-8d", L.Stud[i].ID, name, L.Stud[i].Course, L.Stud[i].Year);
        }
    }
}

Studtype getInput() {
    Studtype S;
    char mName[100];
    printf("\033[H\033[J");
    printf("First name: ");
    scanf(" %s", S.name.FName);
    printf("Middle Name: ");
    scanf(" %s", mName);
    S.name.MI = mName[0];
    printf("Last name: ");
    scanf( "%s", S.name.LName);
    printf("ID: ");
    scanf("%u", &S.ID);
    printf("Course: ");
    scanf(" %s", S.Course);
    printf("Year: ");
    scanf("%d", &S.Year);
    // printf("\n");
    return S;
}

void populateList(Studlist *pL, int n) {
    if(pL->count + n <= SIZE) {
        for(int i = 0; i < n; i++) {
            pL->Stud[pL->count++] = getInput();
        }
    }
}

void sortByID(Studlist *pL) {
    if(pL->count > 1) {
        for(int i = 0; i < pL->count - 1; i++) {
            for(int j = 0; j < pL->count - 1 - i; j++) {
                if(pL->Stud[j].ID > pL->Stud[j + 1].ID) {
                    Studtype temp = pL->Stud[j];
                    pL->Stud[j] = pL->Stud[j + 1];
                    pL->Stud[j + 1] = temp;
                }
            }
        }
    }
}