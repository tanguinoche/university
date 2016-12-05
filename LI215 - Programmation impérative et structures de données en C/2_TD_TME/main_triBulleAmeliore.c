#include <stdio.h>
#include <stdlib.h>
#include "utilitaires_tableaux.h"
#include "tri_bulle.h"
#include <time.h>
#define TAILLE 5

int main (){

  int tab[TAILLE];
  srand(time(NULL));
  init_tab_alea(tab,TAILLE);
  
    int i;
  for(i=0;i<TAILLE;i++){
      printf("%d ",tab[i]);
    }
  triBulleAmeliore(tab,TAILLE);
  afficher_tab(tab,TAILLE);
  tab_trie(tab,TAILLE);

  return 0;
}
