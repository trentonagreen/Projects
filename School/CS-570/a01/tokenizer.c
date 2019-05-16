#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ll.h"

/*

function that append a char to the end of a char*.s

*/
void append(char *str, char c) {
  int len = strlen(str);
  str[len] = c;
  str[len + 1] = '\0';
}

/*

function that tokenizes readline input. There are checks for: white-space,
special, escape, double quote, and single quote characters. All other characters
are appended to a char* which is then added to a linked list.

*/
int tokenize(list* ll, char* input, char* str) {
  const char* special = "|;<>&";
  const char* escape = "\\";
  const char* squote = "\'";
  const char* dquote = "\"";

  for(int i = 0; i < strlen(input); i++) {

    // ****************************WHITE-SPACE CHECK****************************
    if(isspace(input[i])) {
    
      // if found a space and the str container isn't empty, add to lists
      if(strcmp(str, "") != 0) {
        ENQUEUE;
      }
    }

    // ****************************SPECIAL CHECK****************************
    else if(strchr(special, input[i])) {

      // if character before is not a space
      if(!isspace(input[i-1])) {
      
        // if character before is special
        if(strchr(special, input[i - 1])) {
	
	  // if str container is empty append and add to list
          if(!strcmp("", str)) {
            append(str, input[i]);
            ENQUEUE;
          }
          else {
	  
	  // else string is not empty so add previous to list and then append
            ENQUEUE;
            append(str, input[i]);
          }
        }
	
	// else character before is a normal
        else {
          ENQUEUE;
          append(str, input[i]);
          ENQUEUE;
        }
      }
      // else character before is a white-space and can be appended and added
      else {
        append(str, input[i]);
        ENQUEUE;
      }
    }

    // ****************************ESCAPE CHECK****************************
    else if(strchr(escape, input[i])) {
    
      if(i + 1 == strlen(input)) {
        append(str, ' ');
      }
      
      // append the next character to str container
      else {
        i = i + 1;
        append(str, input[i]);
      }
    }

    // ********************DQUOTE CHECK****************************
    else if(strchr(dquote, input[i])) {
      for(int j = i + 1; j < strlen(input); j++) {
      
        // Iif another double quote is found add str container to list
        if(strchr(dquote, input[j])) {
          ENQUEUE;
          break;
        }
	
        //if there is an escape, append the string after to str container
        else if(strchr(escape, input[j])) {
          j = j + 1;
          append(str, input[j]);
        }
	
       // if on the last loop and still havent found double quote, append and add to list
       else if(j + 1 == strlen(input))  {
         append(str, input[j]); 
         ENQUEUE;
       }
       
        // else append normal characters
        else {
          append(str, input[j]);
        }
        i = j + 1;
      }
    }

    // ****************************SQUOTE CHECK****************************
    else if(strchr(squote, input[i])) {
      for(int j = i + 1; j < strlen(input); j++) {
      
        // if found another single quote character
        if(strchr(squote, input[j])) {
	
          // if the character after single quote is not a space, append and add to list
          if(!isspace(input[j+1])) {
            append(str, input[j+1]);
            ENQUEUE;
            i = j + 1;
          }
	  
          // else the character is a space so add str container to list
          else {
            ENQUEUE;
          }
          break;
        }
	
        // if found and escape character, append character after
        else if(strchr(escape, input[j])) {
          append(str, input[j]);
          i = i + 1;
          break;
        }
	
        // if on the last loop and no single quote is found, continue to append and add to list
        else if(j + 1 == strlen(input)) {
          append(str, input[j]);
          ENQUEUE;
        }
	
	// else only a normal character to append
        else {
          append(str, input[j]);
        }
        i = j + 1;
      }
    }

// ****************************REACHED LAST****************************

    //if on the last character, make sure to append and add to list
    else if(i + 1 == strlen(input)) {
      append(str, input[i]);
      ENQUEUE;
    }

// ****************************NORMAL****************************

    //else just append a normal character
    else {
      append(str, input[i]);
    }

    // if there is a final token that exists add to list
    if(strcmp(str, "") != 0 && i + 1 == strlen(input)) {
      ENQUEUE;
    }

  } //end of for loop
  return 0;
}
