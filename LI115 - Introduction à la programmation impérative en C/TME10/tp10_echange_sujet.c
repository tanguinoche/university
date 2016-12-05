#include <cini.h>

void echanger(int *a, int *b){
  int aux;
  aux=*a;
  *a=*b;
  *b=aux;
}

int main () {
   int a;
   int b;

   /* Saisie de la valeur de la variable a */
   printf("Saisie de a : ");
   if(scanf("%d", &a)!=1){
	   printf("Erreur lors de la saisie de a, veuillez saisir un entier.\n");
   }

   /* Saisie de la valeur de la variable b */
   printf("Saisie de b : ");
    if(scanf("%d", &b)!=1){
	   printf("Erreur lors de la saisie de b, veuillez saisir un entier.\n");
   }

   printf("Avant echange :  a = %d et b = %d\n", a, b);

   /* appel a la fonction echanger */
   echanger(&a, &b);

   printf("Apres echange :  a = %d et b = %d\n", a, b);
   return 0;
}

