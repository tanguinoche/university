#include <stdio.h>
#include <stdlib.h>

int compte_mots(char **tab)
{
  int res = 0;
  while(tab[res])
    res++;
  return res;
} 

void affiche_tab_mots (char **tab) 
{
  int res = 0;
  while(tab[res] != NULL) { 
    printf ("%s", *(tab+res));
    printf ("\n");
    res++;
  } 
}  

char **detruit_tab_mots(char **ptab_mots)
{
  int i = 0;
  while(ptab_mots[i])
    free(*(ptab_mots + i));
  
  free(ptab_mots);
  return ptab_mots;
}

int main () 
{
  char **tab = malloc(4 * sizeof(char*));
  tab[0] = "iusfijdfh";
  tab[1] = "ljdfsijc";
  tab[2] = "msix";
  printf("%d\n", compte_mots(tab));
  affiche_tab_mots(tab);
  
}
