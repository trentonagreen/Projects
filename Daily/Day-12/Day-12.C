#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INTERVAL 1000

int main(int argc, char **argv) {
  printf("Daily Programming, Day-12\n");
  printf("-----------------------------------------------------------------\n");

  int interval;
  double rand_x, rand_y, og_dist, pi;
  int circle_points = 0, square_points = 0;

  srand(time(NULL));

  for(int i = 0; i < (INTERVAL * INTERVAL); i++) {
    rand_x = (rand() % (INTERVAL+1)) / INTERVAL;
    rand_y = (rand() % (INTERVAL+1)) / INTERVAL;

    og_dist = rand_x * rand_x + rand_y * rand_y;

    if(og_dist <= 1) {
      circle_points++;
    }

    square_points++;

    pi = (4 * circle_points) / square_points;
  }

  printf("Final estimation of pi:\t%lf\n", pi);
}