#include <stdlib.h>
#include <stdio.h>
#include "abr.h"

Un_noeud *AjouterABR(Un_noeud **abr, int v, void *data)
{
  if((*abr) == NULL){
    (*abr) = (Un_noeud*)malloc(sizeof(Un_noeud));
    (*abr)->v = v;
    (*abr)->data = data;
    (*abr)->g = NULL;
    (*abr)->d = NULL;
    return (*abr);
  }
  
  if((*abr)->v < v) return(AjouterABR(&((*abr)->d), v, data));
  if((*abr)->v > v) return(AjouterABR(&((*abr)->g), v, data));
  return NULL;
}

Un_noeud *ExtraireABR(Un_noeud *abr, Un_noeud *n)
{
  
  Un_noeud *tmp;
  if(abr->v < n->v)
    return (ExtraireABR(abr->d, n)); 
  if(abr->v > n->v)
    return (ExtraireABR(abr->g, n)); 
  if(n == abr) {							
    if((abr->g != NULL) && (abr->d != NULL)) { 
      tmp = n->d;
      if(tmp->g == NULL){				
	n->v = tmp->v;
	n->data = tmp->data;
	n->d = tmp->d;
	return n;
      }
      while(tmp->g->g != NULL)			      
	tmp = tmp->g;
      n->v = (tmp->g)->v;
      n->data = (tmp->g)->data;
      if ((tmp->g)->d != NULL)   
	(tmp->g) = (tmp->g)->d;
      else{
	tmp->g = NULL;
	return n;
      }								
    }else if((n->d == NULL) && (n->g != NULL))				
      return n->g;
  }			
  return NULL;
}

void ItererABR(Un_noeud *abr, void (*fonc)(Un_noeud *, void *), void *arg)
{
  if((abr) && (fonc)){
    ItererABR(abr->g, fonc, arg);
    fonc(abr, arg);
    ItererABR(abr->d, fonc, arg);
  }
}

void DetruireABR(Un_noeud *abr, void (*detfonc)(void *))
{
  if(abr != NULL){
    DetruireABR(abr->g, detfonc);
    DetruireABR(abr->d, detfonc);
    detfonc(abr->data);
    free(abr);    
  }	
}

Un_noeud *ChercherABR(Un_noeud *abr, int vr)
{
  if(abr == NULL)
    return NULL;
  if((abr->v) < vr)
    return ChercherABR(abr->d, vr);
  if((abr->v) > vr)
    return ChercherABR(abr->g, vr);
  return abr;			
}

void AfficherNoeud(Un_noeud *n, void *flux)
{
  if(n) fprintf(flux, "%d", n->v);
}

void AfficherABR(Un_noeud *abr, FILE *flux)
{
  if(abr != NULL) {
    ItererABR(abr, AfficherNoeud, flux);
  }
}	

int hauteur(Un_noeud *abr)
{
  int hsg, hsd;
  if(abr == NULL)
    return 0;
  hsg = hauteur(abr->g);
  hsd = hauteur(abr->d);
  if(hsg > hsd)
    return hsg+1;
  return hsd+1;
  
}

Un_noeud *RotGABR(Un_noeud *abr)
{
  if((abr == NULL) || (abr->d == NULL))
    return abr;
  Un_noeud *aux2 = (abr->d)->g;
  Un_noeud *la = (abr->d);   
  Un_noeud *aux1 = abr;		
  la->g = aux1;				
  (la->g)->d = aux2;	
  return la;
}


Un_noeud *RotDABR(Un_noeud *abr)
{
  if((abr == NULL) || (abr->g == NULL))
    return abr;
  Un_noeud *aux2 = (abr->g)->d;
  Un_noeud *la = (abr->g);   
  Un_noeud *aux1 = abr;		
  la->d = aux1;				
  (la->d)->g = aux2;	
  return la;
}

int EstAVL(Un_noeud *avl)
{
  int cpt = 0, cpt2 = 0;
  while((avl->g != NULL) && (avl->d != NULL)) {
    cpt = EstAVL(avl->g)+1;
    cpt2 = EstAVL(avl->d)+1;
  }
  
  cpt = hauteur(avl)-cpt;
  cpt2 = hauteur(avl)-cpt2;
  if((cpt > 1) || (cpt2 > 1))
    return 0;
  return 1;
}

int NbNoeuds (Un_noeud *abr)
{
  if(abr == NULL)
    return 0;
  return 1 + NbNoeuds(abr->g) + NbNoeuds(abr->d);	
}

Un_noeud *ABR2AVL(Un_noeud *abr)
{
  int ngg, ngd, ndg, ndd;
  int diff;
  if (!abr) return NULL ;
  while (1) {
    if(abr->g) {
      ngg = NbNoeuds(abr->g->g);
      ngd = NbNoeuds(abr->g->d); 
    } 
    else { ngg = 0; ngd = 0; }
    
    if(abr->d) { 
	    	ndg = NbNoeuds(abr->d->g);
	    	ndd = NbNoeuds(abr->d->d); 
    } 
    else { ndg = 0; ndd = 0; }
    
    diff = ndg + ndd - ngg - ngd;
    if ((diff <= 1) && (diff >= -1)) break ;
    
    if (diff > 1) {
      if( diff > ndg +1 ) 
	abr = RotGABR (abr);
      else 
	abr->d = RotDABR(abr->d);
    }
    if (diff < -1) {
      if((-diff) > ngd+1 ) 
	abr = RotDABR(abr);
      else 
	abr->g = RotGABR(abr->g);
    }
    
  }
  abr->g = ABR2AVL(abr->g);
  abr->d = ABR2AVL(abr->d);
  return abr;
}

