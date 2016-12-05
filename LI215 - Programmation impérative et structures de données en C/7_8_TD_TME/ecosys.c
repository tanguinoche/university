#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ecosys.h"
#include <time.h>

Animal *creer_animal(int x, int y, float energie) 
{
  Animal *animal;
  animal = (Animal *)malloc(sizeof(Animal));
  animal->x = x;
  animal->y = y;
  animal->energie = energie;
  animal->precedent = NULL;
  animal->suivant = NULL;
  srand(time(NULL));
  animal->dir[0] = rand() % 3 - 1;
  animal->dir[1] = rand() % 3 - 1;
  return animal;
} 



Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) 
{
  if(liste) {
    animal->suivant = liste;
    liste->precedent = animal;
  } else {
    animal->suivant = liste;
  }
  return animal;
}


void ajouter_animal(int x, int y, Animal **liste_animal)  
{
  if((x < 0) || (y < 0) || (x >= SIZE_X) || (y >= SIZE_Y)){
  } else {
    Animal *animal = creer_animal(x, y, energie);
    *liste_animal = ajouter_en_tete_animal(*liste_animal, animal);
  }
}

void enlever_animal(Animal **liste, Animal *animal) 
{
  if(animal->suivant == NULL && animal->precedent == NULL) {
    free(animal);
  } else {
    if(animal->suivant == NULL){
      (animal->suivant)->precedent = animal->precedent;
      free(animal);
    } else {
      if(animal->precedent == NULL){
	*liste = animal->suivant;
	(animal->precedent)->suivant = NULL;
	free(animal);
      } else{
	(animal->suivant)->precedent = animal->precedent;
	(animal->precedent)->suivant = animal->suivant;
	free(animal);
      }
    }
  }	
  
}

unsigned int compte_animal_rec(Animal *la) 
{
  if(la == NULL){
    return 0;
  } else {
    return compte_animal_rec(la->suivant)+1;
  } 
}

unsigned int compte_animal_it(Animal *la) 
{
  unsigned int compteur = 0;
  while(la) {
    compteur++;
    la = la->suivant;
  }
  return compteur;
}

void bouger_animaux(Animal *la) 
{
  float p_ch_dir = 0.99;
  float nb_alea = rand()%1;
  
  if (nb_alea < p_ch_dir) {
    
    la->x = la->x + la->dir[0];
    la->y = la->y + la->dir[1];
  }
  
  if (la->x > SIZE_X) {
    la->x = la->x % SIZE_X;
  }
  
  if (la->y > SIZE_Y) {
    la->y = la->y % SIZE_Y;
  }
}

void reproduce(Animal **liste_animal) 
{
  float p_reproduce = 0.8;
  float nb_alea = rand()%1;
  Animal* ani = *liste_animal;
  
  while (ani != NULL) {
    ajouter_animal(ani->x , ani->y, liste_animal);
    if (nb_alea < p_reproduce) {
      ajouter_animal(ani->x , ani->y, liste_animal);
    }
    ani = ani->suivant;
  }
  
  ajouter_animal(ani->x , ani->y, liste_animal);
  if (nb_alea < p_reproduce) {
    ajouter_animal(ani->x , ani->y, liste_animal);
  }
}

void rafraichir_proies(Animal **liste_proie) 
{
  Animal* ani = *liste_proie;
  
  while (ani) {
    bouger_animaux (ani);
    
    ani->energie = ani->energie - d_proie;
    if (ani->energie < 0) {
      enlever_animal (liste_proie , ani);
    }
    reproduce(liste_proie);
  }
  ani = ani->suivant;
}

Animal *animal_en_XY(Animal *l, int x, int y) {
  /* a completer */
  return NULL;
} 

void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  /* a completer */
  
}

void afficher_ecosys(Animal *liste_proie,Animal *liste_predateur) {
  
  char* tab[20][20];
  int cpt_x = 0;
  int cpt_y = 0;
  
  while (cpt_x < 20) {
    
    while (cpt_y < 20) {
      tab[cpt_x][cpt_y] = ".";
      cpt_y++;
    }
    cpt_y=0;
    cpt_x++;
  }
  
  
  while (liste_proie) {
    if (strcmp (tab [liste_proie->x][liste_proie->y], "O") == 0) {
      tab[liste_proie->x][liste_proie->y] = "2";
    }
    else {
      tab[liste_proie->x][liste_proie->y] = "X";
    }
    liste_proie = liste_proie->suivant;
  }
  
  while (liste_predateur) {
    if (strcmp (tab [liste_predateur->x][liste_predateur->y], "X") == 0) {
      tab[liste_predateur->x][liste_predateur->y] = "2";
    }
    else {
      tab[liste_predateur->x][liste_predateur->y] = "O";
    }    
    liste_predateur = liste_predateur->suivant;
    
  }
  
  cpt_x = 0;
  cpt_y = 0;
  
  while( cpt_x < 20) {
    
    while( cpt_y < 20) {
      printf("%s  ", tab[cpt_x][cpt_y] );
      cpt_y++;
    }
    cpt_y = 0;
    cpt_x++;
    printf("\n");
  }
  
}
