#include <stdio.h>
#include "utilitaires_tableaux.h"
#include "tri_bulle.h"
#include <time.h>
#define TAILLE 5

void triBulle(int tab[], int n){
  int i,j;
  for(i=n-1;i>0;i--){
    for(j=0;j<i;j++){
      if(tab[j]>tab[j+1]){
	echanger_elem_tab(tab,j,j+1);
      }
    }
  }
}

void triBulleAmeliore(int tab[], int n){
  int i,j;
  int echange=1;

  while(echange){
    echange=0;
   for(i=n-1;i>0;i--){
    for(j=0;j<i;j++){
      if(tab[j]>tab[j+1]){
	echanger_elem_tab(tab,j,j+1);
	echange=1;
   
      }
    }
   }
  }
}


