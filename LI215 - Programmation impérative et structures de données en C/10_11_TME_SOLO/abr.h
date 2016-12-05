#ifndef ABR
#define ABR
#include <stdio.h>

typedef struct Un_noeud_
	{
	int v;
	void *data;
	struct Un_noeud_ *g;
	struct Un_noeud_ *d;
	} Un_noeud;

Un_noeud *AjouterABR(Un_noeud **abr, int v, void *data);
Un_noeud *ChercherABR(Un_noeud *abr, int v);
Un_noeud *ExtraireABR(Un_noeud *abr, Un_noeud *n);
void DetruireABR(Un_noeud *abr, void (*detfonc)(void *));
void ItererABR(Un_noeud *abr, void (*fonc)(Un_noeud *, void *), void *arg);
void AfficherABR(Un_noeud *abr, FILE *flux);

int hauteur(Un_noeud *abr);

Un_noeud *RotGABR(Un_noeud *abr);
Un_noeud *RotDABR(Un_noeud *abr);

int EstAVL(Un_noeud *avl);
Un_noeud *ABR2AVL(Un_noeud *abr);

#endif
