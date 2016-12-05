#include <cini.h>

#define DIM 10
/* On remarque que tab[i] est équivalent à tab+i.
 * En effet, avec tab[i], on "lit le tableau".
 * Avec *(tab+i), on va chercher directement à l'adresse de tab[i].
 * C'est un bon exemple pour voir qu'un tableau est un pointeur.*/
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
