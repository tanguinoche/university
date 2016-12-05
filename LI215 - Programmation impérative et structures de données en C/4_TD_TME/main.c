#include<stdlib.h>
#include<stdio.h>
#include "repertoire.c"


int main () 
{
Contact *c1 = nouveau_contact(); 
set_nom_prenom(c1, "abc", "def");   
Contact *rep = cree_repertoire(5);
Contact *rep_new = resize_repertoire(rep, 10);
ecrire(rep, 5, "test.txt");
lire("test.txt", rep[0], 5);
}
