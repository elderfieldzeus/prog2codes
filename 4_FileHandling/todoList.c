#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    char task[30];
    unsigned status : 1;
}Taskbar;

typedef struct {
    Taskbar *tasks;
    int count;
    int max;
}TaskList;

TaskList getTasks(const char file[]);
void inputTask(TaskList *list, const char file[]);
void displayTasks(TaskList list);

int main() {
    char file[] = "./tasks.dat";
    TaskList list = getTasks(file);
    inputTask(&list, file);
    //printf("%d\n", list.count);
    displayTasks(list);
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
    
    list.tasks = (Taskbar*) malloc(sizeof(Taskbar) * MAX);
    list.count = -1;
    while(fread(&list.tasks[++list.count], sizeof(Taskbar), 1, fptr) != 0);
    list.tasks = (Taskbar*) realloc(list.tasks, sizeof(Taskbar) * list.count);
    fclose(fptr);
    return list;
}

void inputTask(TaskList *list, const char file[]) {
    FILE *fptr;
    if((fptr = fopen(file, "ab")) == NULL) {
        printf("ERROR IN INPUT");
    }

    list->tasks = (Taskbar*) realloc(list->tasks, sizeof(Taskbar) * (++list->count));

    printf("Enter task: ");
    scanf(" %[^\n]", list->tasks[list->count - 1].task);
    list->tasks[list->count - 1].status = 0;
    fwrite(&list->tasks[list->count - 1], sizeof(Taskbar), 1, fptr);
    fclose(fptr);
}

void displayTasks(TaskList list) {
    printf("%-30s | STATUS\n", "TASKS");
    for(int i = 0; i < 50; i++) printf("-");
    for(int i = 0; i < list.count; i++) {
        printf("\n%-30s | %s", list.tasks[i].task, list.tasks[i].status ? "FINISHED" : "NOT FINISHED");
    }
}