#include <cini.h>
void somme(int a, int *som){
	//Calcul de la somme des entiers.
	*som+=a;
}

void min_max(int a, int *min, int *max){
	//Calcul du min et du max parmi les entiers.
	if(a<*min){
		*min=a;
	}
	if(a>*max){
		*max=a;
	}
}

int main(int argc, char **argv)
{
	int q, i, entier, som=0, min, max;
	//On saisit la quantité d'entiers.
	printf("Veuillez saisir le nombre d'entier a saisir.\n");
	   if(scanf("%d", &q)!=1){
	   printf("Erreur lors de la saisie de a, veuillez saisir un entier.\n");
   }
   printf("\n");

   //On saisit les entiers.
   //Une première fois pour initialiser min et max.
	   if(scanf("%d", &entier)!=1){
	   printf("Erreur lors de la saisie de a, veuillez saisir un entier.\n");
   }
   printf("Vous avez saisi : %d\n", entier);
   min=entier;
   max=entier;
   somme(entier, &som);
   min_max(entier, &min, &max);

   //Puis les autres.
   for(i=1 ; i<q ; i++){
	   if(scanf("%d", &entier)!=1){
	   printf("Erreur lors de la saisie de a, veuillez saisir un entier.\n");
   }
   printf("Vous avez saisi : %d\n", entier);
   somme(entier, &som);
   min_max(entier, &min, &max);
}
printf("\nLa somme totale est %d.\n Le minimum est : %d.\n Le maximum est : %d.\n",som, min, max);
	return 0;
}

