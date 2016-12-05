Un_point* CreerPoint(unsigned int id, int x, int y){
  Un_point* p = malloc(sizeof(p));

  if(!p){
    fprintf(stderr,"Erreur allocation. (creerpoint)\n");
    return NULL;
  }

  p->x=x;
  p->y=y;
  p->id=id;
  p->lf=NULL;

  return p;
}	

Un_noeud* AjouterPoint(Un_noeud *abr, Un_point *p){
/* Coorecction .... if((AjouterABR(&abr, p->id, p) == NULL) { fprintf erreur id déja utilisé, exit(1) } return abr ; */
  if(abr == NULL) // Il n'existe pas d'arbre/de noeud : On le crée et on réessaie
    {
     AjouterNoeud(); /* à faire ??? */
     return AjouterPoint(abr, p);
    }
  if(abr->v == p->id) // Le point existe déjà
    {
     return NULL;
    }
  if(abr->v > p-<id) // On va à gauche
    {
 	return AjouterPoint(abr->g, p);
 	}
  if(abr->v < p->id) //On va à droite
    {
     return AjouterPoint(abr->d, p);
    }
  if(abr->v == 0) //C'est là qu'on insère notre point
    {
      abr->v = p->id;
      return p;
    }	
}	

int VMax(Un_noeud *d)
{
if(n == NULL) return 0;
  while(d->d) //Tant qu'il y a un fils droit
    {
      d = d->d
    }
  return d->v;
}

void DetPoint(void *pv)
{
Un_point *p = pv;
DetruireListe(p->lf, NULL);
free(p);
}

Une_forme CreerForme(Un_type t, Une_couleur c, int nb_points)
{if(t == null) ....
f->type = t;
f->c = c;
f->tbp = malloc(size(Un_point*)*nb_points);
if(f->tabp == NULL) ...
f->etat = VIDE;
return f;
}

Un_elem *AjouterForme(Un_elem *l, Une_forme *f)
{
Un_element *ne = malloc(sizeof(element));
if ...
ne->forme = f;
ne->suiv = l;
return ne;
}

Un_elem *ExtraireForme(Un_elem *l, Une forme*f)
{
Un_elem *nl = l;
if(l==NULL) return NULL;
if(l->forme==f) { nl = ->suiv; free(l); return nl; }
while((nl->suiv) && (nl->forme != f)) {
 nl = nl->suiv;
if(nl->suiv) {
Un_elemnt *nlbis = n->suiv;
nl->suiv = nl->suiv->suiv;
free(nlbis);
}return l;
}


DetruireListe(Un_elem *liste, void (*detforme) (void *f)
{
while(liste) {
Un_elem *suiv = liste->suiv;
detforme(liste->forme);
free(lisre);
liste = suiv;
}

Un_dessin *CreerDessin(char *path)
{
Un_dessin *d = calloc(sizeof(Un_dessin), 1);
if(d == NULL) ...
d->path = strdup(path);
return d;
}


 void EcritPoint(Un_noeud *n, void *fch) { //fini
   FILE *f = fopen(fch, "w");
   fprintf(f, "#Les Points\n");
   fprintf(f, "P %d %d %d\n", n->data->id, n->data->x, n->data->y);
   fclose(f);

 }

 void EcritForme(Un_elem *e, void*fch) { //fini
      FILE *f = fopen(fch, "w");
   fprintf(f, "#Les Formes\n");
   //Segment
   if(!strcmp(e->forme->type, "S"))
     fprintf(f, "%c %u %u %u %d %d\n", e->forme->type, e->forme->coul.r, e->forme->coul.v, e->forme->coul.b, e->forme->tabp[0]->id, e->forme->tabp[1]->id);

   //Courbe
   if(!strcmp(e->forme->type, "C"))
     fprintf(f, "%c %u %u %u %d %d %d %d\n", e->forme->type, e->forme->coul.r, e->forme->coul.v, e->forme->coul.b, e->forme->tabp[0]->id, e->forme->tabp[1]->id, e->forme->tabp[2], e->forme->tabp[3]->id);
   fclose(f);
 }

 void ItererElem(Un_elem *e, void(* fonc)(void *), void *arg) { //fini
   if((e) && (fonc)){
     ItererElem(e->suiv, EcritForme, arg);
     EcritForme(e, arg);
   }
 }
	      

 int EnregDessin(Un_dessin *d, char *nomf)
 {
   FILE *f;
   f = fopen(nomf, "w");
   
   if (!f)
     {
       fprintf(stderr, "impossible d'ouvrir le fichier %s\n", nomf);
       return 0;
     }
   
   fprintf(f, "# Fichier genere par schema\n");
   fclose(f);
   
   ItererABR(d->points, EcritPoint, f);
   
   ItererElem(d->formes, EcritForme, f);
 }

 /////////////////////////////Ouvrir dessin//////////////////////////////

 int LirePoint(Un_dessin *d, char *s)
 {

 }

 int LireForme(Un_dessin *d, char *s)
 {
Une_couleur *c = malloc(sizeof(Une_couleur));
c->r = s[2];
c->v = s[4];
c->b = s[6];

unsigned int nb_pts = (s[0] == 'S')?2:4;

CreerForme(s[0], c, nb_pts);
 }

 Un_dessin *OuvrirDessin(char *nomf)
 {
   FILE *f;
   Un_dessin *d;

   d = CreerDessin(nomf);
   //Test

   f = fopen(nomf, "r");
   if (!f)
     {
       fprintf(stderr, "impossible d'ouvrir le fichier %s\n", nomf);
       return NULL;
     }
   char buffer[64];
   while(fgets(buffer, 64, f) != NULL) {
     if(buffer[0] == '#')
       continue;
     if(buffer[0] == 'P')
       if(LirePoint(d, buffer) == 0)) { fprintf(stderr, "Tentative d'ouverture d'un fichier corrompu : %s\n"); return NULL; }
     else
       if(LireForme(d, buffer) == 0)) { fprintf(stderr, "Tentative d'ouverture d'un fichier corrompu : %s\n"); return NULL; }
   }
   fclose(f);

   return d;

 }
