#include <cini.h>

int a = 3, b = 15, c = 2;

int f1(int v, int n) {
   int i;

   for (i = 0; i < a; i++) {
      v = v+n;
   }
   return v;
}

void f2(int n1, int n2) {
   if (n1 < n2) {
      b = n1;
      c = n2;
   }
   else {
      b = n2;
      c = n1;
   }
}

int main() {
   int v1 = 3, v2 = 5, v3 = 1;

   v1 = f1(v1,2);
   f2(v2,v3);
   return 0;
}
