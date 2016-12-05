#include <cini.h>

int f(int i1, int *p_i2) {
   int i3;

   i3 = i1 + *p_i2;
   *p_i2 = i3;

   return i3;
}

int main () {
   int i1 = 1, i2 = 2;

   f(i1, &i2);

   return 0;
}


