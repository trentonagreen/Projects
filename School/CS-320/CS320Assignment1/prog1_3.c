#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"prog1_2.h"

int main(int argc, char *argv[]) { 
    printf("Assignment #1-3, Trenton Green, trenton.green@sbcglobal.net\n");

    if(argc != 2) {
        printf("\nThis program expects a single command line argument.\n");
        return 0;
    }    

    char buff[256];
    char *token;
    int i;
    int x;
    int N = atoi(argv[1]);
    int* data[N];
    *data = (int *)malloc(sizeof(int*)*N);
    

    struct stack* stack = MakeStack(10);

    for(i = 0; i < N; i++) {
        printf("> ");   
        fgets(buff, 256, stdin);

        //trim the whitespace from input
        if((strlen(buff) > 0) && (buff[strlen(buff) - 1] == '\n')) {
            buff[strlen(buff) - 1] = '\0';
        }

        //split string, and point first word to token
        token = strtok(buff, " ");

        if(token == NULL) {
            continue;
        }
 
        //if token is Pop or pop 
        //then split string and point the second word to token
        //if there is no second word run Pop
        if(strcmp(token, "Pop") == 0 || strcmp(token, "pop") == 0) {
            token = strtok(NULL, " ");
            if(token == NULL) {
                printf("%d\n", Pop(stack));
            }   
            else
                continue;
        }  
        //if token is push
        //then split string and point the second word to token
        //if there is a second word 
        //then convert the string to an int and Push int 
        else if(strcmp(token, "push") == 0) {
            token = strtok(NULL, " ");
            if(token != NULL) {
                x = atoi(token);
                token = strtok(NULL, " ");
                if(token == NULL) {                
                    Push(stack, x);
                }
            } 
        }    
    }// end of for loop   

    //free(data);
 
}// end of main