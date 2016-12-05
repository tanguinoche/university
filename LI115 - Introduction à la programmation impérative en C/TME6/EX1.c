#include <cini.h>

#define MAX 5

int main(int argc, char **argv)
{
  int i=0, valeurValide=0, nombreValeurs=0;
  float saisie=0, totalValeurs=0, moyenne=0;
  float tableauValeurs[MAX]= {0};
//On demande à l'utilisateur de saisir des flottants. Au maximum Max flottants. Si l'utilisateur finit la saisie avant, il tape -1.
//On vérifie également que MAX est une valeur possible.
  printf("Veuillez rentrer vos valeurs, %d maximum.\n", MAX);
  if(MAX>=1) {
    /*On fait une boucle do-while afin de contrôler le nombre de notes VALIDES renseignées.*/
    do {
      if(scanf("%f", &saisie) != 1) {
        printf("Erreur lors de la saisie.\n");
        exit(1);
      }
      if(saisie == -1) {
        printf("Saisie terminee par l'utilisateur.\n");
        tableauValeurs[valeurValide]=saisie;
        break;
      } else if(saisie<-1 || (saisie>-1 && saisie<0)) {
        printf("La valeur saisie n'est pas valide, veuillez rentrer un flottant positif.\n");
      } else {
        tableauValeurs[valeurValide]=saisie;
        valeurValide++;
        totalValeurs+=saisie; //Utilisé pour calculer la moyenne.
        nombreValeurs+=1;     //Utilisé pour calculer la moyenne.
      }
    } while(valeurValide<MAX);

    //On affiche maintenant le tableau en tenant compte du nombre de valeurs valides renseignées.
    if(nombreValeurs>0 && nombreValeurs<=MAX) {
      printf("Le tableau de valeurs :\n");
      for(i=0; i<valeurValide; i++) {
        printf("%f  ", tableauValeurs[i]);
      }
      printf("\n");

      //On calcule maintenant la moyenne des notes valides.
        moyenne=totalValeurs/nombreValeurs;
        printf("La moyenne est %f.\n", moyenne);
      } else if(nombreValeurs==0) {
      printf("Aucune note rentree.\n"); //Le programme est sécurisé si on a pas rentré de note. Dans le cas contraire, on aurait moyenne = Nan.
      } else {
        printf("Erreur lors du calcul de la moyenne.\n");
      }

    } else {
      printf("Le max indique en define n'est pas valide.\nFin du programme.\n\n");
      exit(1);
    }

    return 0;
  }
