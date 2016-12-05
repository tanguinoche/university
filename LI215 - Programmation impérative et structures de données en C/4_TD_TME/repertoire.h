#ifndef _REPERTOIRE_H
#define _REPERTOIRE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct _Date {
  char jour;
  char mois;
  short annee;
} Date;

typedef struct _Adresse {
  char rue[51];
  int code_postal;
  char ville[26];
} Adresse;

typedef struct _Contact {
  char nom[31];
  char prenom[31];
  Date date_naissance;
  char telephone[21];
  Adresse adresse;
} Contact;

void set_nom_prenom(Contact *c, 
		    char *nom, char *prenom);
Contact *nouveau_contact(void);
void liberer_contact(Contact *);
Contact *cree_repertoire(int n);
Contact *resize_repertoire(Contact *c, unsigned int n2);
void ecrire(Contact *r, unsigned int n,char *nom_fichier);
void lire(char *nom_fichier, Contact **r, unsigned int *n);
void afficher_contact(const Contact *c);
Contact *ajouter(Contact *rep, unsigned int *n, Contact *c);

#endif
