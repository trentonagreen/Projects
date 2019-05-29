#include <stdio.h>

int fib(int n) {
  if(n <= 1) {
    return n;
  }
  return (fib(n-1) + fib(n-2));
}

int NumWays(int n) {
  return fib(n+1);
}

int main(int argc, char **argv) {
  printf("Daily Programming, Day-10\n");
  printf("-----------------------------------------------------------------\n");
  
  int n = 4;
  int result = NumWays(n);

  printf("Number of ways:\t%d\n", result);
}