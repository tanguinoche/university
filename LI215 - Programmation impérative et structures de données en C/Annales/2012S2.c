#include <stdio.h>
#include <stdlib.h>

typedef struct _elem_mot {
  char *mot;
  struct _elem_mot *suivant;
} Elem_mot;


typedef struct _tab_mots {
  Elem_mot **tab;
  unsigned int taille;
}Tab_mot;

int fonction_de_hachage(const char *mot, int taille) {
  unsigned int i=0;
  itn cpt = 0;
  while(mot[i]) {
    cpt =+ mot[i++];
  }
  return cpt%taille;
}

Elem_mot *creer_elem_mot(char *mot) {
  Elem_mot *el = malloc(sizeof(Elem_mot));
  el->mot = strdup(mot);
  el->suivant = NULL;
  return el;
}

Elem_mot *ajouter_mot(char *mot, Elem_mot *liste_mot) {
  if(liste_mot == NULL) {
    return creer_elem(mot);
  }

  if(!strcmp(liste_mot->mot, mot)) {
    return NULL;
  }

  if(liste_mot->suivant) {
    return ajouter_mot(mot, liste_mot->suivant);
  }else{
   liste->suivant = creer_elem_mot(mot);
  }

  return liste_mot;
}

Tab_mot *creer_table(unsigned int taille) {
  Tab_mot *lexique = malloc(sizeof(Tab_mot));

  lexique->tab = malloc(taille*sizeof(Elem_mot *));
  lexique->taille = taille;

  int i;
  for(i = 0 ; i < taille ; i++) {
    lexique->tab[i] = NULL;
  }
  return lexique;
}

void ajouter_mot_dans_table(Tab_mots *lex, char *mot) {

  int i = fonction_de_hachage(mot, lex->taille);
  lex->tab[i] = ajouter_mot(mot, lex->tab[i]);
}

int est_dans_le_lexique(const Tab_mots *lex, const char *mot) {
  int ind = fonction_de_hachage(mot, lex->taille);
  int i;

  for(i = 0 ; i < lex->taille ; i++) {
    if(!strcmp(lex->tab[ind][i], mot)) { return 1; }
  }

  return 0;
}
