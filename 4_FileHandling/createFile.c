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
	int YrLevel;
}Studtype;

typedef struct {
	Studtype students[MAX];
	int count;
}RecordList;

char *getFileName();
RecordList getRecords();
void addToFile(RecordList record, char *filename);
void displayFromFile(char *filename);

int main() {
	char *filename = getFileName();
	//RecordList record = getRecords();
	//addToFile(record, filename);
	displayFromFile(filename);
	free(filename);
	return 0;
}

char *getFileName() {
	char *filename = malloc(sizeof(char) * 100);
	printf("Enter filename: ");
	scanf(" %[^\n]", filename);
	filename = realloc(filename, sizeof(char) * strlen(filename) + 1);
	return filename;
}

RecordList getRecords() {
	RecordList record;
	printf("Enter number of records: ");
	scanf("%d", &record.count);
	int i;
	for(i = 0; i < record.count; i++) {
		system("cls");
		printf("Last name: ");
		scanf(" %[^\n]", record.students[i].name.LName);
		printf("First name: ");
		scanf(" %[^\n]", record.students[i].name.FName);
		printf("MI: ");
		scanf(" %c", &record.students[i].name.MI);
		printf("Enter ID Number: ");
		scanf(" %u", &record.students[i].ID);
		printf("Enter Course: ");
		scanf(" %s", record.students[i].Course);
		printf("Enter year level: ");
		scanf("%d", &record.students[i].YrLevel);
		printf("\n");
	}
	return record;
}

void addToFile(RecordList record, char *filename) {
	FILE *fptr;
	if((fptr = fopen(filename, "wb+")) == NULL) {
		printf("ERROR");
		return;
	}
	fwrite(record.students, sizeof(Studtype), record.count, fptr);
	fclose(fptr);
}

void displayFromFile(char *filename) {
	FILE *fptr;
	Studtype student;
	if((fptr = fopen(filename, "rb")) == NULL) {
		printf("ERROR");
		return;
	}
	system("cls");
	printf("    %-6s |              %-17s | %-6s | %-4s\n", "ID", "NAME", "COURSE", "YEAR");
	while(fread(&student, sizeof(Studtype), 1, fptr) > 0) {
		char fullname[100];
		sprintf(fullname, "%s, %s %c.", student.name.LName, student.name.FName, student.name.MI);
		printf("%-10u | %-30s | %-6s | %-4d\n", student.ID, fullname, student.Course, student.YrLevel);
	}
	fclose(fptr);
}
