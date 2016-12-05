#include <cini.h>

#define DIM 10

int main() {
   int tab[DIM];
   int i;

   for (i=0; i < DIM; i++) {
      tab[i] = CINI_random(0, 10);
   }

   printf("Affichage 1 : \n");
   for (i = 0; i < DIM; i++) {
      printf("%d  ", tab[i]);
   }
   printf("\n");

   printf("Affichage 2 : \n");
   for (i = 0; i < DIM; i++) {
      printf("%d  ", *(tab+i));
   }
   printf("\n");
   return 0;
}
