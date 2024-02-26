#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void welcome();
void init();
void options();
void addTask();
void viewTask();
void finishTask();
void removeDash(char *word);
void makeLowerCase(char *word);

int main(){
    welcome();
    init();
    options();
    return 0;
}

void welcome(){
    //printf("\033[H\033[J");
    printf("WELCOME TO ZEUS' TO-DO LIST!!!\n");
}

void init(){
    FILE *fptr = fopen("todo.txt", "w+");

    char check[100];
    int hasStarted = 0;
    while(fgets(check, 100, fptr) != NULL){
        check[strcspn(check, "\n")] = '\0';
        if(strcmp(check, "TO-DO:") == 0)
            hasStarted = 1;
    }

    if(!hasStarted){
        FILE *write = fopen("todo.txt","w");
        fprintf(write, "TO-DO:\n");
        fclose(write);
    }
    
    fclose(fptr);
}

void options(){
    int opt, go = 1;
    while(go){
        printf("\nCHOOSE AN OPTION:\n");
        printf("[1] ADD TASK\n");
        printf("[2] VIEW TASKS\n");
        printf("[3] FINISH TASK\n");
        printf("[4] CLEAR TASKS\n");
        printf("[5] EXIT\n");
        printf("CHOSEN OPTION: ");
        scanf("%d", &opt);
        printf("\033[H\033[J");
        switch(opt){
            case 1 : addTask(); break;
            case 2 : viewTask(); break;
            case 3 : finishTask(); break;
            case 4 : remove("todo.txt"); init(); printf("CLEARED!\n"); break;
            default : printf("THANKS FOR USING"); return;
        }
    }
    
}

void addTask(){
    FILE *ptr = fopen("todo.txt", "a");
    char task[1000];
    printf("Enter new task: ");
    scanf(" %[^\n]", task);
    strcat(task, "\n");
    fprintf(ptr, "-");
    fprintf(ptr, task);
    fclose(ptr);
    printf("\033[H\033[J");
    printf("ADDED!\n");
}

void viewTask(){
    FILE *ptr = fopen("todo.txt", "r");
    char print[1000];
    int empty = 1;
    while(fgets(print, 1000, ptr) != NULL){
        printf("%s", print);
        if(print[0] == '-')
            empty = 0;
    }

    if(empty){
        printf("(NO TASKS YET)\n");
    }
    fclose(ptr);
}

void finishTask(){
    FILE *ptr = fopen("todo.txt", "r"), *temp = fopen("temp.txt", "w+");
    char check[1000], delete[1000], print[1000];
    viewTask();
    printf("\nEnter finished task: ");
    scanf(" %[^\n]", delete);
    makeLowerCase(delete);
    while(fgets(check, 1000, ptr) != NULL){
        check[strcspn(check, "\n")] = '\0';
        strcpy(print, check);
        removeDash(check);
        makeLowerCase(check);
        if(strcmp(delete, check) != 0){
            strcat(print, "\n");
            fprintf(temp, print);
        }
        else{
            printf("\033[H\033[J");
            printf("DELETED!\n");
        }
    }

    fclose(ptr);
    fclose(temp);

    remove("todo.txt");
    rename("temp.txt", "todo.txt");
}

void removeDash(char *word){
    int i;
    for(i = 1; word[i] != '\0'; i++){
        word[i - 1] = word[i];
    }
    word[i - 1] = '\0';
}

void makeLowerCase(char *word){
    for(int i = 0; word[i] != '\0'; i++){
        word[i] = tolower(word[i]);
    }
}