#include "tab.h"

float min(float tab[], int taille) {
  int i, min = tab[0];
  for(i = 1 ; i < taille ; i++)
    if(min > tab[i])
      min = tab[i];
  return tab[i];
}

int indice_min(float tab[], int taille) {
  int i, ind; 
  float min = min(tab, taille);
  for(i = 0 ; i < taille ; i++)
    if(min == tab[i]) ind = i;
  return ind;
}
