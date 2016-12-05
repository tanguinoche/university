#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
  float i = 1.;
  float pi = 0;
  float p = atof(argv[1]);
 printf("Precision égal à : %f.\n", p);


  do {
    pi += 1/i;
    i += 2;
    pi -= 1/i;
    i += 2;
  }while(p < (1/i));

  printf("Pi environ égal à : %.10f.\n", pi*4.0);

  return 0;
}
