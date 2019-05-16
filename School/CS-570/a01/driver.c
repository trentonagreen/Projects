/*

Trenton Green
817704869
cssc1088@edoras.sdsu.edu
CS570
Assignment #1

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ll.h"

int main(int argc, char* argv[]) {
    printf("Trenton Green, CS 570, Assignment #1\n");
    
    list *ll = construct();
    char* input;
    char* str;

    while (1)  {
      input = readline("> ");

      // if reached EOF break out of loop
      if(!input) {
      	break;
      }

      str = malloc(strlen(input));
      str[0] = '\0';

      add_history(input);
      tokenize(ll, input, str);

      // Only print the list if something was typed.
      if(strcmp(input, "") != 0) {
	       printList(ll);
      }
      free(str);
      free(input);
    }
    return 0;
}
