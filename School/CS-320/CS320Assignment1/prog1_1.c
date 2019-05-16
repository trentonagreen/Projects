#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Assignment #1-1, Trenton Green, trenton.green@sbcglobal.net\n");
    printf("What is your name?\n"); 

    char buff[256];
    scanf("%[^\n]s", buff);
    printf("Hello %s!\n", buff);
}
