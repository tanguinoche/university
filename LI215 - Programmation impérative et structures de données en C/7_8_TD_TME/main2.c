#include "ecosys.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float p_ch_dir = 0.01;
float d_proie = 1;
float d_predateur = 1;
float p_manger = 0.2;
float p_reproduce = 0.01;
float energie = 50;

int main () {

  Animal *liste_proie= creer_animal ( 0, 0 , 50);
  Animal *liste_predateur= creer_animal (2, 0, 50);

  ajouter_animal(6,5,&liste_proie);
  ajouter_animal(2,3,&liste_proie);
  ajouter_animal(7,2,&liste_proie);
  ajouter_animal(7,5,&liste_proie);
  ajouter_animal(5,8,&liste_proie);
  ajouter_animal(14,2,&liste_proie);
  ajouter_animal(7,9,&liste_proie);
  

  ajouter_animal(11,9,&liste_predateur);
  ajouter_animal(18,19,&liste_predateur);
  ajouter_animal(3,15,&liste_predateur);
  ajouter_animal(2,14,&liste_predateur);
  ajouter_animal(7,12,&liste_predateur);


  printf(" %d proies\n",compte_animal_it(liste_proie));
  printf(" %d predateurs\n",compte_animal_rec(liste_predateur));
  afficher_ecosys(liste_proie,liste_predateur);
  
  int inf=1;

 while (inf == 1) {
   rafraichir_proies(&liste_proie);
   rafraichir_predateurs(&liste_predateur,&liste_proie);
   afficher_ecosys(liste_proie,liste_predateur);
  }        
      
    return 0;
}
