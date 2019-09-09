#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h> //PATH_MAX, on edoras: <linux/limits.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "ll.h"

void execute_commands(list* ll) {
  node* tmp = ll->head;
  int idx = 0;
  int ctr = 0;
  int ret = 1;
  char buff[PATH_MAX];

  char* argv[LIMIT];

  while(tmp != NULL) {

    /*
      CARROT CHECK
      If a carrot is found, STRIP it and its PARAMETERS
      Check its parameters to see if it is a semicolon or pipe
        If it is, break from the loop and continue
        If reached the end break out of loop
    */
    if(strcmp(tmp->data, rcarrot) == 0 || strcmp(tmp->data, lcarrot) == 0) {
      printf("IO redirection and background not implemented\n");
      argv[0] = NULL;
      delete(ll, idx);

      //delete parameters until found a semicolon, pipe, or reached the end
      while(tmp != NULL) {
        tmp = tmp->next;

        if(tmp->next == NULL) {
          break;
        }

        if(strcmp(tmp->data, semicolon) == 0 ||
          strcmp(tmp->data, piper) == 0) {
          ctr = 0;
          break;
        }
        else {
          delete(ll, idx);
        }
      }
    }

    /*
      AMPERSAND CHECK
      If an ampersand is found, STRIP it
    */
    else if(strcmp(tmp->data, ampersand) == 0) {
      printf("IO redirection and background not implemented\n");
      argv[0] = NULL;
      delete(ll, idx);
    }

    /*
      SEMICOLON AND PIPE CHECK
      If found a semicolon or pipe, it's the end of command parameters, if any
      Make the last element in argv NULL and launch commands in argv
      Empty out argv to prep it for next command following semicolon or pipe
    */
    else if(strcmp(tmp->data, semicolon) == 0 ||
            strcmp(tmp->data, piper) == 0) {

      argv[ctr] = NULL;
      launch(argv);

      argv[0] = 0;
      ctr = 0;
    }

    /*
      CD CHECK
      If there are zero args, print error
      If there is more than 1 args
        Check if it is a semicolon or pipe, if it is, good to go
        If not print error and pass through all args
      Last check it to see if directory exists or not
    */
    else if(strcmp(tmp->data, "cd") == 0 && ctr == 0) { //else

      // 0 args
      if(tmp->next == NULL) {
        printf("Accepts exactly one argument\n");
      }
      else {
        tmp = tmp->next;
        idx++;

        // there is only one arg
        if(tmp->next == NULL) {
          ret = chdir(tmp->data);
        }
        // the second arg is a semicolon or pipe
        else if(strcmp(tmp->next->data, semicolon) == 0 ||
                strcmp(tmp->next->data, piper) == 0) {
          ret = chdir(tmp->data);
          tmp = tmp->next;
          idx++;
        }
        // pass thourgh arguments until found a semicolon or pipe
        else {
          printf("Accepts exactly one argument\n");

          while(tmp != NULL) {
            tmp = tmp->next;

            if(tmp->next == NULL) {
              break;
            }

            if(strcmp(tmp->data, semicolon) == 0 ||
              strcmp(tmp->data, piper) == 0) {
              break;
            }
          }
        }
      }

      // check if the directory exists or doesn't
      if(ret == -1) {
        printf("Directory does not exist or is not accessible\n");
        break;
      }
      if(ret == 0) {
        printf("Directory changed successfully\n");
      }
    }

    /*
      PWD CHECK
      If there is not any arguments following pwd, good to go
      If there is an argument
        Check if it a semicolon or pipe, good to go
        If not then too many arguments and print error
    */
    else if(strcmp(tmp->data, "pwd") == 0 && ctr == 0) {
      if(tmp->next == NULL) {
        if(getcwd(buff, sizeof(buff)) != NULL) {
          printf("Current working directory: %s\n", buff);
        }
        else {
          printf("Unable to obtain working directory\n");
          break;
        }
      }
      else if(strcmp(tmp->next->data, semicolon) == 0 ||
              strcmp(tmp->next->data, piper) == 0) {
        if(getcwd(buff, sizeof(buff)) != NULL) {
          printf("Current working directory: %s\n", buff);
        }
        else {
          printf("Unable to obtain working directory\n");
          break;
        }
        tmp = tmp->next;
        idx++;
      }
      else {
        printf("Accepts exactly one argument\n");
        break;
      }
    }

    /*
      ELSE
      Make sure argv is less than LIMIT
      Point argv to the current list data
      If reached the end of the list, place a NULL in last of argv and launch
    */
    else {
      if(ctr > LIMIT) {
        printf("too many arguments\n");
        break;
      }

      argv[ctr] = tmp->data;
      ctr++;

      //ensure that the last value in argv is NULL
      if(tmp->next == NULL) {
        argv[ctr] = NULL;
        launch(argv);
      }

    }
    tmp = tmp->next;
    idx++;
  }
}

/*
  Runs the commands in argv
  If forking fails print error
  If successful attempt to execute
  If execvp returns then the execution of command failed
  Else Parent waits for the child process to finish
    and will print if process exited successfully or not
*/
void launch(char* argv[100]) {

  pid_t child_pid;
  pid_t tpid;
  int child_status;

  child_pid = fork();

  // if returned negative forking failed
  if(child_pid < 0) {
    printf("Unable to spawn program\n");
    return;
  }

  if(child_pid == 0) {
    // if exec returns then it failed
    execvp(argv[0], argv);

    printf("Unable to execute %s\n", argv[0]);
    return;
  }
  else {
    tpid = wait(&child_status);
    if(tpid < 0) {
      printf("Process exited with error\n");
    }
    else {
      printf("Process exited successfully\n");
    }
  }
}
