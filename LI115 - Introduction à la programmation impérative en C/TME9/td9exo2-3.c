#include <cini.h>

int f(int i1, int i2) {
   int i3;

   printf("Au debut de f : i1 = %d, i2 = %d\n", i1, i2);

   i3 = i1 + i2;
   i2 = i3;

   printf("A la fin de f : i1 = %d, i2 = %d\n", i1, i2);

   return i3;
}

int main() {
   int i1 = 1, i2 = 2, res = 0;

   res = f(i1, i2);
   return  0;
}

