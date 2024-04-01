#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
 
typedef struct {
	char LName[16];
	char FName[20];
	char MI;
}Nametype;
 
typedef struct {
	Nametype name;
	unsigned ID;
	char Course[8];
	int year;
}Studtype;
 
typedef struct {
	Studtype students[MAX];
	int count;
}StudList;
 
StudList populateList();
void displayList(StudList L);
void insertAtPos(StudList *L, Studtype S, int pos);
Studtype deleteElem(StudList *L, unsigned ID);
int deleteAllCourse(StudList *L, char dCourse[]);
void sortList(StudList *L);
void insertSorted(StudList *L, Studtype stud);
 
 
int main() {
	StudList L = populateList();
	Studtype S = {{"MEOW", "MEOW", 'D'}, 444444, "BSCS", 1};
 
	displayList(L);
 
	insertAtPos(&L, S, 3);
	displayList(L);
 
	Studtype Deleted = deleteElem(&L, 111111);
	displayList(L);
	printf("\n\nDELETED: %s\n\n", Deleted.name.LName);
 
	int deleted = deleteAllCourse(&L, "BSIT");
	displayList(L);
	printf("NUM OF DELETED: %d\n", deleted);
 
	sortList(&L);
	displayList(L);
 
	Studtype NEW = {{"Kaw", "Kurt", 'D'}, 999999, "BSCS", 1};
	insertSorted(&L, NEW);
	displayList(L);
	return 0;
}
 
 
StudList populateList() {
	Studtype S[] = {{{"Elderfield", "Zeus", 'D'}, 111111, "BSCS", 1}, 
					{{"Escandor", "Railey", 'G'}, 222222, "BSIS", 1}, 
					{{"Rondina", "Earl", 'G'}, 333333, "BSCS", 1}};
	int numElem = sizeof(S) / sizeof(Studtype);
 
	StudList L = {.count = 0};
	int i;
 
	for(i = 0; i < MAX && i < numElem; i++) {
		L.students[L.count++] = S[i];
	}
 
	return L;
}
 
 
void displayList(StudList L) {
	int i;
	printf("\nLIST:\n");
	for(i = 0; i < L.count; i++) {
		printf("%s %c. %-20s\t%u\t%s \t%d\n", 
		L.students[i].name.FName, L.students[i].name.MI, 
		L.students[i].name.LName, L.students[i].ID, 
		L.students[i].Course, L.students[i].year);
	}
}
 
 
void insertAtPos(StudList *L, Studtype S, int pos) {
	if(L->count < MAX && pos <= L->count) {
		int i;
		for(i = L->count; i >= pos; i--) {
			L->students[i] = L->students[i - 1];
		}
		L->students[pos] = S;
		L->count++;
	}
	else {
		printf("\n\nERROR\n\n");
	}
}
 
 
Studtype deleteElem(StudList *L, unsigned ID) {
	Studtype deleted = {{"XXXX", "XXXXX", 'X'}, 0, "XXXX", 0};
	int i;
	for(i = 0; i < L->count && ID != L->students[i].ID; i++) {}
	if(i < L->count) {
		deleted = L->students[i];
		for(i++; i < L->count; i++) {
			L->students[i - 1] = L->students[i];
		}
		L->count--;
	}
	return deleted;
}
 
int deleteAllCourse(StudList *L, char dCourse[]) {
	int deleteCount = 0, i, j;
	for(i = 0; i < L->count;) {
		if(strcmp(L->students[i].Course, dCourse) == 0) {
			deleteCount++;
			for(j = i + 1; j < L->count; j++) {
				L->students[j - 1] = L->students[j];
			}
			L->count--;
		}
		else {
			i++;
		}
	}
	return deleteCount;
}
 
void sortList(StudList *L) {
	int i, j;
	for(i = 0; i < L->count; i++) {
		int small = i;
		for(j = i + 1; j < L->count; j++) {
			if(strcmp(L->students[j].name.LName, L->students[small].name.LName) < 0) {
				small = j;
			}
		}
		if(small != i) {
			Studtype temp = L->students[small];
			L->students[small] = L->students[i];
			L->students[i] = temp;
		}
	}
}
 
void insertSorted(StudList *L, Studtype stud) {
	if(L->count < MAX) {
		int i, j;
		for(i = 0; i < L->count && strcmp(stud.name.LName, L->students[i].name.LName) > 0; i++) {}
		if(i <= L->count) {
			for(j = L->count++; j >= i; j--) {
				L->students[j] = L->students[j - 1];
			}
			L->students[i] = stud;
		}
	}	
}