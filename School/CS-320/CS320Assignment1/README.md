Trenton Green <br />
trenton.green@sbcglobal.net <br />

<br />
prog1_1.c <br />
C program that prompts user to enter their name. Program will take in their name and print a greeting message with their full name. <br />

<br />
prog1_2.h <br />
A header file  containing struct stack with functions for Push, Pop, and Grow. And a MakeStack. <br />

<br />
prog1_2.c <br />
Implementation of MakeStack, Push, Pop, and Grow. The Grow function doubles the stacks size. The push function will call grow if the stack is not big enough. The pop function will return -1 if stack is empty

<br />
prog1_3.c <br />
A driver program for prog1_2.c. Takes a single command line argument that is an integer. Upon correct inputs will print a "> " and take input from STDIN. A delimiter will split the string if need and call the push or pop function depending on the input. 