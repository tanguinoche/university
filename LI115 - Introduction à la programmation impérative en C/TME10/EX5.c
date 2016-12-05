#include<stdio.h>
#include<stdlib.h>

#define ORIGINSEM 4
#define JORIGIN 15
#define MORIGIN 10
#define ANORIGIN 1582

//Prototypes :
void affiche_jour (int no);
void affiche_mois (int no);
int jdelasemaine(int jour, int mois, int annee);
int test_entier(int annee, int division);
int est_bis(int annee);
int jma2abs(int jour, int mois, int annee);

void affiche_jour (int no) {
   if (no == 0) { printf("lundi"); }
   if (no == 1) { printf("mardi"); }
   if (no == 2) { printf("mercredi"); }
   if (no == 3) { printf("jeudi"); }
   if (no == 4) { printf("vendredi"); }
   if (no == 5) { printf("samedi"); }
   if (no == 6) { printf("dimanche"); }
   if ( (no < 0) || (no > 6)) {
      printf("Cette valeur ne correspond pas a un jour de la semaine\n");
   }
}

void affiche_mois (int no) {

   if (no ==  1) { printf("janvier"); }
   if (no ==  2) { printf("fevrier"); }
   if (no ==  3) { printf("mars"); }
   if (no ==  4) { printf("avril"); }
   if (no ==  5) { printf("mai"); }
   if (no ==  6) { printf("juin"); }
   if (no ==  7) { printf("juillet"); }
   if (no ==  8) { printf("aout"); }
   if (no ==  9) { printf("septembre"); }
   if (no == 10) { printf("octobre"); }
   if (no == 11) { printf("novembre"); }
   if (no == 12) { printf("decembre"); }
   if ( (no < 1) || (no > 12)) {
      printf("Cette valeur ne correspond pas a un mois du calendrier\n");
   }
}

int jdelasemaine(int jour, int mois, int annee){
	int nbjours;
	nbjours=jma2abs(jour, mois, annee);
	return (nbjours+ORIGINSEM)%7;
}

int test_entier(int annee, int division) {
  //On vérifie que annee est un multiple de division dans quel cas on renvoie 1, sinon 0.
  if((annee%division)==0) {
    return 1;
  } else {
    return 0;
  }
}

int est_bis(int annee){

//Une année est bissextile si elle est divisible par 400, ou si elle est divisible par 4 mais pas par 100.

return ((annee%400)==0)||((annee%4)==0 && (annee%100)!=0);

}

int jma2abs(int jour, int mois, int annee) {
  int nbjours=0, bis, i;
  //Déclaration des tableaux
  int tabMois[2][12]= {{31,29,31,30,31,30,31,31,30,31,30,31},{31,28,31,30,31,30,31,31,30,31,30,31}};
  //int tabJours[2]= {365,366};

bis=est_bis(ANORIGIN);
if(annee>ANORIGIN) { //Calcul des jours jusqu'à la fin de l'année.
//On va jusqu'à la fin du mois de départ.

  for(i=JORIGIN ; i<=tabMois[bis][MORIGIN] ; i++) {
    nbjours++;
  }
//On ajoute les mois jusqu'à la fin de l'année.
  for(i=MORIGIN ; i<=11 ; i++) {
    nbjours+=tabMois[bis][i];
  }
  //Calcul du nombre de mois (et donc de jours) entre ANORIGIN+1 et le mois d'arrivée -1 de l'année d'arrivée.
  int year=ANORIGIN+1;
  for(i=0 ; (year<annee || i<mois-1) ; i++){
	  if(i==12){ //Si le mois est décembre, on a passé une année.
		  i=0;
		  year++;
	  }
	  bis=est_bis(year);
	  nbjours+=tabMois[bis][i];
  }
  return nbjours+jour;
} else { //L'année est la même
  if(mois>MORIGIN) { //Le mois est différent
    for(i=JORIGIN ; i<=tabMois[bis][MORIGIN] ; i++) { //On ajoute les jours jusqu'à la fin du mois d'origine.
      nbjours++;
    }
    for(i=MORIGIN+1 ; i<mois ; i++) { //On ajoute les mois compris strictement entre celui de départ et d'arrivée si il y en a.
      nbjours+=tabMois[bis][i];
    }
    return nbjours+jour; //On ajoute le nombre de jour du mois d'arrivée.
  } else { //L'année et le mois sont les mêmes.
    return JORIGIN-jour;
  }
}
}

int main() {
  int anneeB, bissextile=0, nbjours, jour, mois, annee, joursem;
  printf("Veuillez saisir une annee a partir de 1582 : ");
  if(scanf("%d", &anneeB) != 1) {
    printf("\nErreur dans la fonction main : variable annee.\n");
    exit(1);
  }
  if(anneeB<1582) {
    printf("\nNous n'etudions que les annees du calendrier gregorien, a partir de 1582.\n");
  } else {
    bissextile=est_bis(anneeB);
    if(bissextile) {
      printf("\n%d est une annee bissextile !\n", anneeB);
    } else {
      printf("\n%d n'est pas une annee bissextile !\n", anneeB);
    }
  }


  printf("Veuillez saisir un jour\n");
  if(scanf("%d", &jour) != 1) {
    printf("\nErreur dans la fonction main : variable annee.\n");
    exit(1);
  }
   if(jour<1 || jour>31){
	  printf("Erreur, le jour doit etre compris entre 1 et 31.");
	  exit(1);
  }
  printf("Veuillez saisir un mois\n");
  if(scanf("%d", &mois) != 1) {
    printf("\nErreur dans la fonction main : variable annee.\n");
    exit(1);
  }
  if(mois<1 || mois>12){
	  printf("Erreur, le mois doit etre compris entre 0 et 11.");
	  exit(1);
  }

  printf("Veuillez saisir une annee\n");
  if(scanf("%d", &annee) != 1) {
    printf("\nErreur dans la fonction main : variable annee.\n");
    exit(1);
  }
  nbjours=jma2abs(jour, mois, annee);

  printf("%d\n", nbjours);
  joursem=jdelasemaine(jour, mois, annee);
  affiche_jour(joursem);
  return 0;
}
