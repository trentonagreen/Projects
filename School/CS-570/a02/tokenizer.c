#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ll.h"

void append(char *str, char c) {
  int len = strlen(str);
  str[len] = c;
  str[len + 1] = '\0';
}

void tokenize(list* ll, char* input, char* str) {

  for(int i = 0; i < strlen(input); i++) {

    //****************************WHITE-SPACE CHECK****************************
    if(isspace(input[i])) {
      if(strcmp(str, "") != 0) {
        ENQUEUE;
      }
    }

    //****************************SPECIAL CHECK****************************
    else if(strchr(special, input[i])) {

      // IF CHARACTER BEFORE SPECIAL IS NOT A SPACE
      if(!isspace(input[i-1])) {
        // IF CHARACTER BEFORE SPECIAL IS SPECIAL
        if(strchr(special, input[i - 1])) {
          if(!strcmp("", str)) {
            append(str, input[i]);
            ENQUEUE;
          }
          else {
            ENQUEUE;
            append(str, input[i]);
          }
        }
        else {
          ENQUEUE;
          append(str, input[i]);
          ENQUEUE;
        }
      }
      // IF CHARACTER BEFORE SPECIAL IS A SPACE
      else {
        append(str, input[i]);
        ENQUEUE;
      }
    }

    //****************************ESCAPE CHECK****************************
    else if(strchr(escape, input[i])) {
      // IF ESCAPE CHARACTER IS AT THE END, APPEND A SPACE CHARACTER
      if(i + 1 == strlen(input)) {
        append(str, ' ');
      }
      // IF NOT ADD NEXT CHARACTER TO THE TOKEN
      else {
        i = i + 1;
        append(str, input[i]);
      }
    }

    //********************DQUOTE CHECK****************************
    else if(strchr(dquote, input[i])) {
      for(int j = i + 1; j < strlen(input); j++) {
        // IF FOUND ANOTHER DOUBLE QUOTE
        if(strchr(dquote, input[j])) {
          ENQUEUE;
          break;
        }
        // IF FOUND AN ESCAPE CHARACTER
        else if(strchr(escape, input[j])) {
          j = j + 1;
          append(str, input[j]);
        }
       // IF ON LAST LOOP STILL HAVENT FOUND A DOUBLE QUOTE
       else if(j + 1 == strlen(input))  {
         append(str, input[j]); //check for spaces
         ENQUEUE;
       }
        // ELSE APPEND NORMAL CHARACTER
        else {
          append(str, input[j]);
        }
        i = j + 1;
      }
    }

    //****************************SQUOTE CHECK****************************
    else if(strchr(squote, input[i])) {
      for(int j = i + 1; j < strlen(input); j++) {
        // IF FOUND ANOTHER SINGLE QUOTE
        if(strchr(squote, input[j])) {
          // IF THE CHARACTER AFTER THE SINGLE QUOTE IS NOT A SPACE
          if(!isspace(input[j+1])) {
            append(str, input[j+1]);
            ENQUEUE;
            i = j + 1;
          }
          // ELSE THE CHARACTER IS A SPACE
          else {
            ENQUEUE;
          }
          break;
        }
        // IF FOUND AN ESCAPE CHARACTER
        else if(strchr(escape, input[j])) {
          append(str, input[j]);
          i = i + 1;
          break;
        }
        // IF ON LAST LOOP AND STILL HAVENT FOUND A SINGLE QUOTE
        else if(j + 1 == strlen(input)) {
          append(str, input[j]);
          ENQUEUE;
        }
        else {
          append(str, input[j]);
        }
        i = j + 1;
      }
    }

    //****************************REACHED LAST****************************
    else if(i + 1 == strlen(input)) {
      append(str, input[i]);
      ENQUEUE;
    }

    //****************************NORMAL****************************
    else {
      append(str, input[i]);
    }

    // IF THERE IS A FINAL TOKEN THAT EXISTS ENQUEUE
    if(strcmp(str, "") != 0 && i + 1 == strlen(input)) {
      ENQUEUE;
    }

  } //end of for loop
  return;
}
