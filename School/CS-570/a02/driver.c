/*
  Trenton Green
  817704869
  cssc1088@edoras.sdsu.edu
  CS570
  Assignment #2
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ll.h"

int main(int argc, char* argv[]) {
    printf("Trenton Green, CS 570, Assignment #2\n");

    list *ll = construct();
    char* input;
    char* str;

    while (TRUE)  {
      input = readline("> ");

      if(input == NULL) {
        printf("\n");
        break;
      }

      str = malloc(strlen(input));
      str[0] = '\0';

      add_history(input);
      tokenize(ll, input, str);


      // ADDED TO ASSIGNMENT 2
      execute_commands(ll);

      // Only print the list if something was typed.
      if(strcmp(input, "") != 0) {
	     // printList(ll);
      }

      // ADDED TO ASSIGNMENT 2
      clear(ll);

      free(str);
    	free(input);
    }
    destruct(ll);
    return 0;
}
