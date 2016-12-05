#include <cini.h>

bool f(int p, int n, int *r) { //On récupère un pointeur => int *r.
   bool res = false;

   *r = p%n; //On envoie le résultat à l'adresse du pointeur.
   if (*r == 0) {
      res = true;
   }
   return res;
}

int main() {
   int x,y;
   int reste=0; //Il faut initialiser la variable reste car elle est envoyée à la fonction f.
   bool div;

   printf("Saisissez un entier : ");
   if (scanf("%d", &x) != 1) {
      printf("Erreur fatale a la saisie\n");
      exit(1);
   }
   printf("Saisissez un deuxieme entier : ");
   if (scanf("%d", &y) != 1) {
      printf("Erreur fatale a la saisie\n");
      exit(1);
   }

   div = f(x,y,&reste); //On doit envoyer l'adresse de la variable reste, afin de pouvoir la modifier dans f.
   if( div ) {
      printf("%d est un diviseur de %d\n", y, x);
   }
   else {
      printf("le reste de la division de %d par %d est %d\n", x, y, reste); //On envoie ce qu'il se trouve à *reste.
   }
   return 0;
}
