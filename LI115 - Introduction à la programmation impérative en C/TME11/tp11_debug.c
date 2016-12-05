#include <cini.h> //include et non define.

int f1(int p1, int p2) { //p1 n'est pas un pointeur.
   return p1 + p2;
}

void f2(int* a, int* b) { //La fonction ne retourne rien.
   int p3 = *a;

   *a = *b;
   *b = p3;
}

int main() {
   int a = 2, b; //Pas besoin d'initialiser b.
   char ch = 'a';

   b = f1(a, ch);
   printf("La somme de %d et %d est %d\n", a, ch, b);

   printf("Veuillez saisir un nombre : ");
   if (scanf("%d", &a) != 1) { //On applique scanf sur l'adresse de a.
      printf("Erreur fatale a la saisie\n");
      exit(1);
   }
   printf("Le nombre saisi est : %d\n", a);

   printf("Valeurs de a et b avant f2 : %d et %d\n", a, b);

   f2(&a, &b); //On a oublié de renseigner les arguments nécessaires à l'exécution de f2. La variable t est inutile, f2 ne renvoie rien.

   printf("Valeurs de a et b apres f2 : %d et %d\n", a, b);

   return 0;
}

