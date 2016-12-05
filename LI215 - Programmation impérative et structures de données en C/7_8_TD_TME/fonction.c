#include <stdio.h>

typedef struct _elt Elt;
struct _elt {
  int donnee;
  Elt *suivant;
};

int main () {
  int taille = 10;
  Elt *liste = NULL;
  Elt *nelt = NULL;
  int i = 0;

  for (i=0; i<taille; i++) {
    nelt= malloc (sizeof(Elt));
    if (nelt == NULL) {
      printf ("Erreur lors de l'allocation\n");
      return 0;
    }
    nelt->donnee=i;
    nelt->suivant = liste;
    liste = nelt;
  }

  nelt=liste;
  while (nelt) {
    printf (" %d " ,nelt->donnee);
    nelt= nelt->suivant;
  }
  printf("\n");

 


Elt *filtre_pair1(Elt *liste) {

  if (liste->suivant = filtre_pair1(liste->suivant)) {
    if (liste->donee %2 ==0) {
      nelt = liste->suivant;
      free (liste);
      return (nelt);
    }
  }
  return liste;
}

 filtre_pair1 (liste);

  nelt=liste;
  while (nelt) {
    printf (" %d " ,nelt->donnee);
    nelt= nelt->suivant;
  }
  printf("\n");
