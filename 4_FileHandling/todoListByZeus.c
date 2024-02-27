#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100

typedef struct {
    char task[30];
    unsigned status : 1; //bit field
}Tasktype;

typedef struct {
    Tasktype *tasks; //array of tasks
    int count;
}TaskList;

TaskList getTasks(const char file[]);
void inputTask(TaskList *list, const char file[]); //gets input
int optionsScreen(TaskList *list, const char file[]); //displays choices
int continueOrNot(); //prompts user on if the program should continue
void displayTasks(TaskList list); //displays the different tasks
void finishTask(TaskList *list, const char file[]); //change task status to finished
void deleteTasks(TaskList *list, const char file[]); //delete unwanted tasks
void clearList(TaskList *list, const char file[]); //resets the data in the list
void updateFile(TaskList list, const char file[]); //updates file with new info
int findTask(char search[], TaskList *list); //searches the task and returns index
int areSameString(const char s1[], const char s2[]); //compares 2 strings (not case sensitive)
void exitScreen(); //displays exit screen

int main() {
    char file[] = "./tasks.dat";
    TaskList list = getTasks(file);
    int loop;
    do {
        loop = optionsScreen(&list, file);
    }while(loop);
    exitScreen();
    free(list.tasks);
    return 0;
}

TaskList getTasks(const char file[]) {
    TaskList list;
    FILE *fptr;
    if((fptr = fopen(file, "rb+")) == NULL) {
        if((fptr = fopen(file, "wb+")) == NULL) {
            printf("ERROR\n");
        }
    }
    
    list.tasks = (Tasktype*) malloc(sizeof(Tasktype) * MAX);
    list.count = -1;
    while(fread(&list.tasks[++list.count], sizeof(Tasktype), 1, fptr) != 0);
    list.tasks = (Tasktype*) realloc(list.tasks, sizeof(Tasktype) * list.count);
    fclose(fptr);
    return list;
}

int optionsScreen(TaskList *list, const char file[]) {
    int choice;
    printf("\033[H\033[J");
    printf("WELCOME TO ZEUS' TO-DO LIST!!!\n");
    printf("What would you like to do?\n");
    printf("[1] Display Tasks\n");
    printf("[2] Add Task\n");
    printf("[3] Finish Task/s\n");
    printf("[4] Delete Task/s\n");
    printf("[5] Clear All Tasks\n");
    printf("[?] Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1: displayTasks(*list); break;
        case 2: inputTask(list, file); break;
        case 3: finishTask(list, file); break;
        case 4: deleteTasks(list, file); break;
        case 5: clearList(list, file); break;
        default: choice = 0;
    }

    if(choice != 0) {
        choice = continueOrNot();
    }

    return choice;
}

int continueOrNot() {
    char cont;
    printf("\nWould you like to continue? [y/n]: ");
    scanf(" %c", &cont);
    return (tolower(cont) == 'y') ? 1 : 0;
}

void inputTask(TaskList *list, const char file[]) {
    FILE *fptr;
    if((fptr = fopen(file, "ab")) == NULL) {
        printf("ERROR IN INPUT");
    }

    list->tasks = (Tasktype*) realloc(list->tasks, sizeof(Tasktype) * (++list->count));
    printf("\033[H\033[J");
    printf("Enter task: ");
    scanf(" %[^\n]", list->tasks[list->count - 1].task);
    list->tasks[list->count - 1].status = 0;
    fwrite(&list->tasks[list->count - 1], sizeof(Tasktype), 1, fptr);
    fclose(fptr);
}

void displayTasks(TaskList list) {
    printf("\033[H\033[J");
    printf("%-30s | STATUS\n", "TASKS");
    for(int i = 0; i < 50; i++) 
        printf("-");
    printf("\n");
    if(list.count > 0) {
        for(int i = 0; i < list.count; i++) {
            printf("%-30s | %s\n", list.tasks[i].task, list.tasks[i].status ? "FINISHED" : "NOT FINISHED");
        }
    }
    else {
        printf("(TO DO LIST IS EMPTY)\n");
    }
}

void finishTask(TaskList *list, const char file[]) {
    char toBeFinished[100];
    int found = 0;
    printf("\033[H\033[J");
    printf("Enter task you have finished: ");
    scanf(" %[^\n]", toBeFinished);

    for(int i = 0; i < list->count; i++) {
        if(areSameString(list->tasks[i].task, toBeFinished) == 0) {
            list->tasks[i].status = 1;
            found = 1;
        }
    }

    if(found == 0) {
        printf("TASK NOT FOUND! Pls try again\n");
        return;
    }

    printf("TASK STATUS UPDATED\n");
    updateFile(*list, file);
}

void deleteTasks(TaskList *list, const char file[]) {
    char toBeDeleted[100];
    int index;
    printf("\033[H\033[J");
    printf("Enter task to delete: ");
    scanf(" %[^\n]", toBeDeleted);

    index = findTask(toBeDeleted, list);

    if(index == -1) {
        printf("TASK NOT FOUND! Pls try again\n");
        return;
    }

    while(index != -1){
        list->count--;
        for(int i = index; i < list->count; i++) {
            list->tasks[i] = list->tasks[i + 1];
        }
        list->tasks = (Tasktype*) realloc(list->tasks, sizeof(Tasktype) * list->count);
        index = findTask(toBeDeleted, list);
    }

    printf("TASK SUCCESSFULLY DELETED!!\n");
    updateFile(*list, file);
}

void clearList(TaskList *list, const char file[]) {
    FILE *fClear;

    list->count = 0;
    list->tasks = (Tasktype*) realloc(list->tasks, sizeof(Tasktype) * list->count);

    printf("\033[H\033[J");

    if((fClear = fopen("./clear.dat", "wb+")) == NULL) {
        printf("ERROR IN CLEAR\n");
    }

    printf("TO-DO LIST HAS BEEN SUCCESSFULLY CLEARED");
    remove(file);
    rename("./clear.dat", file);
    fclose(fClear);
}

void updateFile(TaskList list, const char file[]) {
    FILE *fDelete;
    int i = 0;
    if((fDelete = fopen("./delete", "wb+")) == NULL) {
        printf("ERROR IN DELETE");
    }
    for(int i = 0; i < list.count; i++) {
        fwrite(&list.tasks[i], sizeof(Tasktype), 1, fDelete);
    }
    remove(file);
    rename("./delete", file);
    fclose(fDelete);
}

int findTask(char search[], TaskList *list) {
    int i;
    for(i = 0; i < list->count && areSameString(search, list->tasks[i].task) != 0; i++) {}
    return (i == list->count) ? -1 : i;
}

int areSameString(const char s1[], const char s2[]) {
    if(strlen(s1) != strlen(s2)) return 1;
    else {
        int i;
        for(i = 0; s1[i] != '\0' && tolower(s1[i]) == tolower(s2[i]); i++);
        return (i == strlen(s1)) ? 0 : 1;
    }
}

void exitScreen() {
    printf("\033[H\033[J");
    printf("THANK YOU FOR USING ZEUS' TO-DO LIST\n");
    printf("Made on 02/27/2024\n");
}
