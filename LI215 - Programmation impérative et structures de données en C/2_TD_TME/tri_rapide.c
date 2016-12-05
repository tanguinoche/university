#include "utilitaires_tableaux.h"
#include <stdlib.h>
#include <stdio.h>



void triRapide(int tab[], int n) {

  int *tab1=nouveau_tableau(n);
  int *tab2=nouveau_tableau(n);
  int *tab3=nouveau_tableau(n);
  int j;
  for(j=0;j<n;j++){
    if(tab1[j]<tab1[n/2]){
      tab2[j]=tab1[j];
    }
    else{
      tab3[j]=tab1[j];
    }



}


int partitionner(int tab[], int s, int n)
	{
      int p = 0;


      return p;
	}

void triRapideOptimise(int tab[], int s, int n)
	{

	}
