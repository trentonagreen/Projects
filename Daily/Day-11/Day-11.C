#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 26

bool isValid(int *arr, int k) {
  int val = 0;
  for(int i = 0; i < MAX_CHARS; i++) {
    if(arr[i] > 0) {
      val++;
    }
  }

  return (k >= val);
}

char *substr(const char *src, int m, int n) {
  int len = n - m;

   char *dest = (char*)malloc(sizeof(char) * (len + 1));

   for(int i = m; i < n && (*src != '\0'); i++) {
     *dest = *(src + i);
     dest++;
   }

   *dest = '\0';
   return dest - len;
}

void kUniques(char *s, int k) {
  int un = 0;           // number of unique characters
  int len = sizeof(s);  // length of char array

  int count[MAX_CHARS];
  memset(count, 0, sizeof(count));

  for(int i = 0; i < len; i++) {
    if(count[s[i] - 'a'] == 0) {
      un++;
    }
    count[s[i] - 'a']++;
  }

  if(un < k) {
    printf("not enough unique characters\n");
  }

  int curr_start = 0;
  int curr_end = 0;
  int max_win_size = 1;
  int max_win_start = 0;

  memset(count, 0, sizeof(count));

  count[s[0] - 'a']++;

  for(int i = 1; i < len; i++) {
    count[s[i] - 'a']++;
    curr_end++;

    while (!isValid(count, k)) {
      count[s[i] - 'a']--;
      curr_start++;
    }

    if(curr_end - curr_start + 1 > max_win_size) {
      max_win_size = curr_end - curr_start + 1;
      max_win_start = curr_start;
    }
  }

  char *result = substr(s, max_win_start, max_win_size);

  printf("\tmax substring is:\t%s\n", result);
  printf("\twith length:\t%d\n", max_win_size);
}

int main(int argc, char **argv) {
  printf("Daily Programming, Day-11\n");
  printf("-----------------------------------------------------------------\n");

  char *s = "aabacbebebe";
  int k = 3;
  kUniques(s, k);
  return 0;
}