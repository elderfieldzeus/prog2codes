#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    STUD = 1, TEACH
}CHOICE;

typedef struct {
    char studentID[9];  //9
    char lastName[20];  //20
    int age;            //4
    float grade;        //4
}STUDENT;

typedef struct {
    char teacherID[9];  //9
    char lastName[20];  //20
    int age;            //4
    int numOfClasses;   //4
}TEACHER;

typedef union {
    STUDENT stud;
    TEACHER teach;
}LOGIN;

typedef struct {
    LOGIN log;
    CHOICE choice;
}UnionManager;

void populateChoice(UnionManager *logs) {
    switch(logs->choice) {
        case STUD:
            STUDENT s = {"23104469", "Elderfield", 20, 1.2};
            logs->log.stud = s;
            break;
        case TEACH:
            TEACHER t = {"69696969", "Sarmiento", 49, 5};
            logs->log.teach = t;
            break;
        default:
            printf("WRONG\n");
    }
}

void displayChoice(UnionManager logs) {
    switch(logs.choice) {
        case STUD:
            printf("\nID: %s\nNAME: %s\nAGE: %d\nGRADE: %.2f\n", logs.log.stud.studentID, logs.log.stud.lastName, logs.log.stud.age, logs.log.stud.grade);
            break;
        case TEACH:
            printf("\nID: %s\nNAME: %s\nAGE: %d\nNO OF CLASSES: %d\n", logs.log.teach.teacherID, logs.log.teach.lastName, logs.log.teach.age, logs.log.teach.numOfClasses);
            break;
        default:
            printf("WRONG AGAIN\n");
    }

    printf("\nSIZE OF LOGIN = %lu\n", sizeof(LOGIN));
}

int main() {
    UnionManager logs;
    int ch;
    printf("[1] Student\n[2] Teacher\nEnter choice: ");
    scanf(" %d", &ch);
    logs.choice = ch;
    populateChoice(&logs);
    displayChoice(logs);
    return 0;
}