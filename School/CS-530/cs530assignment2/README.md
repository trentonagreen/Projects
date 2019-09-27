# CS530Assignment2

This assignment is broken up into two parts.

prog2_1.h
  Header file given at beginning of assignment.

prog2_1.c
  A thread safe linked list with functions to create a queue.
  Functions include tSafeConstruct, tSafeDestruct, tSafeEnqueue, tSafeDequeue.

prog2_2.
  This program takes two command line arguments. First is K, the number of
  pseudoprime numbers. Second is B, required bit length of prime number to find.

  Example Compilation:
  
      gcc prog2_2.c prog2_1.c -lgmp -lpthread -o prog2_2

  Example Output:
  
      ./prog2_2 4 31
      > Assignment #2-2, Trenton Green, trenton.green@sbcglobal.net
      > 1073741827
      > 1073741831
      > 1073741833
      > 1073741839
     
  Example Output:
  
      ./prog2_2 10 4
      > Assignment #2-2, Trenton Green, trenton.green@sbcglobal.net
      > 11
      > 13
      > No more numbers of bit length 4

     
