#include <cini.h>
#define NBMAX 49

int ajouter_tab(int tab[], int n, int val);

int main(){

int n=0, tab[6], val, success, i;



while(n<=6){
printf("Saisir un nombre pour la grille loto : ");
if(scanf("%d", &val)!=1||(val<1)||(val)>49){ printf("Erreur dans la saisie\n"); }
success=ajouter_tab(tab, n, val);
if(success){ n++; }
}


for(i=0;i<n;i++){
	printf("%d  ",tab[i]);
}

return 0;
}

int ajouter_tab(int tab[], int n, int val){
	int i=0, j=0, aux;
	
	while(i<n&&tab[i]<val){ //On cherche la position 
		i++;
	}
	
	if(i==n){ tab[i]=val; return 1; } //Si on a pas trouvé plus grand dans les valeurs initialisées, on le met après.
	
	if(tab[i]==val){ return 0; } //Si on a un doublon, on renvoie faux.
	
	if(tab[i]>val){ //Si on a trouvé sa position dans les valeurs initialisées, on les décale et on insert val.
		for(j=i; j<n ; j++){
			aux=tab[j];
			tab[j]=val;
			val=aux;
		}
		return 1;
	}
	
	return 0; //Dans tous les autres cas on renvoie faux.
}
