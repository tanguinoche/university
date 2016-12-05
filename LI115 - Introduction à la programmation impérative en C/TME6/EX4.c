#include <cini.h>

#define MAX 5

int main(int argc, char **argv)
{
  int i=0, valeurValide=0, nombreValeurs=0, j=0, k=0, valeur=0;
  float saisie=0, totalValeurs=0, moyenne=0;
  float tableauValeurs[MAX]= {0};

//On demande � l'utilisateur de saisir des flottants. Au maximum Max flottants. Si l'utilisateur finit la saisie avant, il tape -1.
//On v�rifie �galement que MAX est une valeur possible.
  printf("Veuillez rentrer vos valeurs, %d maximum.\n", MAX);
  if(MAX>=1) {
    /*On fait une boucle do-while afin de contr�ler le nombre de notes VALIDES renseign�es.*/
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
        totalValeurs+=saisie; //Utilis� pour calculer la moyenne.
        nombreValeurs+=1;     //Utilis� pour calculer la moyenne.
      }
    } while(valeurValide<MAX);

    //On affiche maintenant le tableau en tenant compte du nombre de valeurs valides renseign�es.
    if(nombreValeurs>0 && nombreValeurs<=MAX) {
      printf("Le tableau de valeurs :\n");
      for(i=0; i<valeurValide; i++) {
        printf("%f  ", tableauValeurs[i]);
      }
      printf("\n");

      //On calcule maintenant la moyenne des notes valides.
      moyenne=totalValeurs/nombreValeurs;
      printf("La moyenne est %f.\n", moyenne);

      /*EXERCICE 4*/
      //On prend un nombre dans la tableau...
      for(j=0 ; j<nombreValeurs ; j++) {
        valeur=0;
        //Puis on parcourt le m�me tableau pour voir combien de fois celui-ci est r�p�t�.
        for(k=0 ; k<nombreValeurs ; k++) {
          if(tableauValeurs[j] == tableauValeurs[k]) {
            valeur++;
            if(valeur>=2) {
              tableauValeurs[k]=-2; /*Pour chaque nombre identique trouv�, on remplace celui-ci par -2, afin de ne pas le recompter plus tard.
				* On peut prend -2 car lors de l'�nonc� de l'exercice 1, on nous dit que ce sont des flottants positifs. Si ce n'�tait pas le cas,
				* on aurait pu utiliser les bool�ens.*/
            }
          } else if(k==-2) {
            //Ne rien faire puisque ce nombre a d�j� �t� comptabilis� pr�c�demment.
          }
        }
        if(valeur>1 && tableauValeurs[j]!=-2) { //La valeur doit �tre pr�sente au moins deux fois pour l'afficher (cf �nonc�).
          printf("La valeur %f est pr�sente %d fois.\n", tableauValeurs[j], valeur);
        }
      }
      /*FIN EXERCICE 4*/
    } else if(nombreValeurs==0) {
      printf("Aucune note rentree.\n"); //Le programme est s�curis� si on a pas rentr� de note. Dans le cas contraire, on aurait moyenne = Nan.
    } else {
      printf("Erreur lors du calcul de la moyenne.\n");
    }

  } else {
    printf("Le max indique en define n'est pas valide.\nFin du programme.\n\n");
    exit(1);
  }

//Pour i = 0, on parcourt le tableau de taille N, si tab[0] = qqch, on incr�mente i


  return 0;
}
