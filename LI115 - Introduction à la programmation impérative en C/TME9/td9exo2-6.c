#include <cini.h>

int f(int i1, int *p_i2) {
   int i3;
   int i4 = *p_i2;

   i3 = i1 + i4;
   i4 = i3;

   *p_i2 = i4;

   return i3;
}

int main() {
   int i1 = 1, i2 = 2, res = 0;

   res=f(i1, &i2);

   return 0;
}
