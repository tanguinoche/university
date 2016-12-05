#ifndef GEOM
#define GEOM

/* Mettre a jours le chemin de ABR*/
#include "abr.h"

typedef struct Un_elem_
	{
	struct Une_forme_ *forme;
	struct Un_elem_ *suiv;
	} Un_elem;

typedef struct Un_point_
	{
	unsigned int id;
	int x;
	int y;
	Un_elem *lf;
	}Un_point;

typedef struct _une_couleur
	{
	unsigned char r;
	unsigned char v;
	unsigned char b;
	} Une_couleur;

typedef enum _un_type {SEG=1, COURB} Un_type;
typedef enum _un_etat {VIDE=1, DEB, CTL1, FIN, OK} Un_etat;

typedef struct Une_forme_
	{
	Un_type type;
	Une_couleur coul;
	Un_point **tabp;
	Un_etat etat;
	} Une_forme;

typedef struct Un_dessin_
	{
	Un_noeud *points;
	Un_noeud *abrx;
	Un_elem *formes;
	char *path;
	} Un_dessin;

/* les points */
Un_point *CreerPoint(unsigned int id, int x, int y);
Un_noeud *AjouterPoint(Un_noeud *abr, Un_point *p);
int VMax(Un_noeud *d);


/* Les Dessins */
Un_dessin *CreerDessin(char *path);
Un_dessin *OuvrirDessin(char *nomf);
void LimitesDessin(Un_dessin *d, int *xmin, int *xmax, int *ymin, int *ymax);
int EnregDessin(Un_dessin *d, char *nomf);
void DetruireDessin(Un_dessin *d);


/* Les Formes */
Une_forme *CreerForme(Un_type t, Une_couleur c, int nb_points);
Un_elem *AjouterForme(Un_elem *l, Une_forme *f);
Un_elem *ExtraireForme(Un_elem *l, Une_forme *f);
void DetruireForme(Une_forme *f);
void DetruireListe(Un_elem *liste, void (*detforme)(Une_forme *f));
int NbPForme(Une_forme *f);

/* ABRX */
Un_point *ChercherPointABRX(Un_dessin *d, int x, int y);
Un_noeud *AjouterPointABRX(Un_noeud *abrx, Un_point *p);
void ConstruireABRX(Un_dessin *d);
void DetruireABRX(Un_noeud *abrx);

#endif
