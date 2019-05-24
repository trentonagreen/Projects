#include <stdio.h>
#include <string.h>

int decode(char *sequence, int size) {

  // table to store sub problems
  int count[size + 1];
  count[0] = 1;
  count[1] = 1;

  for(int i = 2; i <= size; i++) {
    count[i] = 0;

    if(sequence[i-1] > '0') {
      count[i] = count[i-1];
    }

    if(sequence[i-1] == '1' || (sequence[i-2] == '2' && sequence[i-1] < '7')) {
      count[i] += count[i-2];
    }
  }
  return count[size];
}

int main(int argc, char **argv) {
  printf("Daily Programming, Day-6\n");
  printf("-----------------------------------------------------------------\n");

  char sequence[] = "111";
  int size = strlen(sequence);
  
  int result = decode(sequence, size);
  printf("%d\n", result);
}