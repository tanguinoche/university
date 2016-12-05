#include<stdlib.h>
#include<stdio.h>
#include "repertoire.h"

void set_nom_prenom(Contact *c, char *nom, char *prenom) 
{
  unsigned int i;
  for(i = 0 ; i < strlen(nom) ; i++)
    c->nom[i] = nom[i];
  for (i = 0 ; i < strlen(prenom) ; i++)
    c->prenom[i] = prenom[i];
}

Contact *nouveau_contact(void) 
{
  Contact *nc = (Contact *)malloc(sizeof(Contact));
  
  unsigned int i = 0;
  //Initialisation du nouveau contact
  
  for(i = 0 ; i < 31 ; i++)
    nc->nom[i] = '\0';
  for(i = 0 ; i < 31 ; i++)
    nc->prenom[i] = '\0';
  nc->date_naissance.jour = 0;
  nc->date_naissance.mois = 0;
  nc->date_naissance.annee = 0;
  for(i = 0 ; i < 21 ; i++)
    nc->telephone[i] = '\0';
  for(i = 0 ; i < 51 ; i++)
    nc->adresse.rue[i] = '\0'; 
  nc->adresse.code_postal = 0;
  for(i = 0 ; i < 26 ; i++)
    nc->adresse.ville[i] = '\0';
  
  return nc;
}

void liberer_contact(Contact *c) 
{
  free(c);
}

Contact *cree_repertoire(int n) 
{
  Contact *r = (Contact *)malloc(sizeof(Contact *) * n);
  unsigned int i;
  for(i = 0 ; i < n ; i++) {
    r[i].nom[0] = '\0';
    r[i].prenom[0] = '\0';
    r[i].date_naissance.jour = 0;
    r[i].date_naissance.mois = 0;
    r[i].date_naissance.annee = 0;
    r[i].telephone[0] = '\0';
    r[i].adresse.rue[0] = '\0';
    r[i].adresse.code_postal = 0;
    r[i].adresse.ville[0] = '\0';
  }
  return r;
}

Contact *resize_repertoire(Contact *c, unsigned int n2) 
{
  Contact *c2 = (Contact *)realloc(c, n2 * sizeof(Contact));
  if (c2 == NULL) {
    printf("Probleme d'allocation\n");
    return NULL;
  }
  return c2;
}

void ecrire(Contact *r, unsigned int n,char *nom_fichier) 
{
  FILE *f = fopen(nom_fichier, "w");
  if (f == NULL) {
    printf("Impossible d'ouvrir le fichier %s \n", nom_fichier);
    return;
  }
  fwrite(r, sizeof(Contact), n, f);
  fclose(f);
}

void lire(char *nom_fichier, Contact **r, unsigned int *n)
{
  Contact c;
  *r = cree_repertoire(1);
  FILE *f = fopen(nom_fichier, "r");
  if (f == NULL)  {
    printf("Impossible d'ouvrir le fichier %s \n", nom_fichier);
    return;
  }
  unsigned int i = 0;
  *n = 1;
  unsigned int nblu = fread(&c, sizeof(Contact), 1, f);
  if (nblu == 1) {
    (*r)[i] = c;
  }
  while(!feof(f)) {
    nblu = fread(&c, sizeof(Contact), 1, f);
    if(nblu == 1) {
      (*n)++;
      i++;
      *r=resize_repertoire(*r, *n);
      (*r)[i] = c;
    }
  }
  fclose(f);
}

void afficher_contact(const Contact *c) 
{
  if (c == NULL) return;
  printf("Nom: %s \nPrenom: %s\n", c->nom, c->prenom);
  printf("Date de naissance: %d/%d/%d\n", c->date_naissance.jour, c->date_naissance.mois, c->date_naissance.annee);
  printf("Telephone: %s\n", c->telephone); 
  printf("Adresse: %s %d %s\n", c->adresse.rue, c->adresse.code_postal, c->adresse.ville);
}

