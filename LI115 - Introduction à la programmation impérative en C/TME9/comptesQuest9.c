

#include <cini.h>

#define MAXCOMPTES 15

float depotOuRetrait(bool depot, float montant, float comptes[], int compte){
	if(depot){
		comptes[compte]+=montant;
	}else{
		comptes[compte]-=montant;
	}
	return comptes[compte];
}


float depotOuRetrait2(int numC, float comptes[], float saisie, bool saisieB, bool autoris[]){
	if(autoris[numC]==true){

	}else{
	}
}

float consulte(float comptes[], int numCompte) {
  return comptes[numCompte];
}

float remunere(int montant) {
  if(montant>0) {
    montant+=montant/100*5;
    return montant;
  } else {
    return montant;
  }
}

int creerCompte(int nbCl) {
  if(nbCl<MAXCOMPTES && nbCl!=-1) {
    return nbCl+1;
  } else {
    return -1;
  }
}

int minPos(float valeurs[], int nbValeurs) {
  int minimum, i=0, minimumPos=-1;

  minimum=valeurs[0];
  for(i=0 ; i<nbValeurs ; i++) { //On parcourt les comptes.
    if(valeurs[i]>=0) { //On vérifie que le compte n'est pas à découvert.
      if(valeurs[i]<minimum) { //Si c'est un minimum, on note l'indice de sa position.
        minimum=valeurs[i];
        minimumPos=i;
      }
    }
  }

  return minimumPos;
}

void afficheTab(float tab[], int taille) {
  int i;

  for (i = 0; i < taille; i++) {
    printf("%f  ", tab[i]);
  }
  printf("\n");
}

float moyenne(float valeurs[], int nbValeurs) {
  int i;
  float somme=0, moyenne=0;

  if(nbValeurs>=1) {
    for(i=0 ; i<nbValeurs ; i++) {
      somme += valeurs[i];
    }
    moyenne=somme/nbValeurs;
    return moyenne;
  } else {
    printf("Erreur dans la fonction moyenne : nombre de valeurs incorrect.\n");
    return -1;
  }
}

int main() {

  float comptes[MAXCOMPTES]= {150.5, 160, 12, 1200, 655};
  bool autoris[MAXCOMPTES]= {true, false, true, true, false};
  int nbCl = 5;
  int choix, numC, numB;
  float saisie;
  int imin, i=0;
  bool b, saisieB;

  do {

    /* affichage du menu */
    printf("\n\t 0 : Quitter\n\n");
    printf("Operations sur les comptes : \n");
    printf("\t 1 : Moyenne des montants\n");
    printf("\t 2 : Minimum solde positif\n");
    printf("\t 3 : Creation d'un compte\n");
    printf("\t 4 : Remuneration des comptes\n\n");
    printf("Operations sur UN compte\n");
    printf("\t 5 : Consultation du solde\n");
    printf("\t 6 : Depot ou retrait\n");

    if (scanf("%d", &choix) != 1) {
      printf("Erreur fatale a la saisie\n");
      exit(1);
    }

    if (choix !=0) {
      /* affichage des comptes */
      afficheTab(comptes, nbCl);

      /* Il faut effectuer l'operation */
      switch (choix) {

      case 1 :
        /* affichage de la moyenne des montants */
        printf("Moyenne des comptes : %f\n", moyenne(comptes, nbCl));
        break;

      case 2 :
        /* affichage du numero du client ayant le plus petit solde positif
           et solde de son compte */
        imin = minPos(comptes, nbCl);
        if (imin==-1) {
          printf("Tous les comptes sont a decouvert\n");
        }
        else {
          printf("Le client ayant le solde positif minimum est %d", imin);
          printf(", il dispose de %f euros\n", comptes[imin]);
        }
        break;

      case 3 :
        /* Saisie d'un nouveau compte client */
        printf("Veuillez saisir le montant du nouveau compte : \n");
        if (scanf("%f", &saisie) != 1) {
          printf("Erreur fatale a la saisie\n");
          exit(1);
        }
        /* ajout de ce compte */
        nbCl = creerCompte(nbCl);

        if (nbCl == -1) {
          printf("Il n'y a plus de compte disponible.\n");
        }
        else {
          printf("Comptes apres creation : \n");
          comptes[nbCl]=saisie;
          afficheTab(comptes, nbCl);
        }
        break;

      case 4 :
        /* Remuneration des comptes */
        for(i=0 ; i<nbCl ; i++) {
          comptes[i]=remunere(comptes[i]);
        }
        afficheTab(comptes, nbCl);
        break;

      case 5 :
        /* Consultation du solde */
        printf("Veuillez saisir votre numero de compte : \n");
        if (scanf("%d", &numC) != 1) {
          printf("Erreur fatale a la saisie\n");
          exit(1);
        }

        if (numC < nbCl) { /* le numero de compte doit etre valide */
          printf("vous disposez de %f euros\n", comptes[i]);
        }
        break;

      case 6 :
        /* Realisation d'un virement ou d'un retrait */
        printf("Veuillez saisir votre numero de compte : \n");
        if (scanf("%d", &numC) != 1) {
          printf("Erreur fatale a la saisie\n");
          exit(1);
        }
        printf("veuillez saisir le montant : \n");
        if (scanf("%f", &saisie) != 1) {
          printf("Erreur fatale a la saisie\n");
          exit(1);
        }
        printf("1 : depot\n2 : retrait\n");
        if (scanf("%d", &numB) != 1) {
          printf("Erreur fatale a la saisie\n");
          exit(1);
        }
        /* conversion de l'entier saisi en sa valeur booleenne correspondante */
        if ( numB == 1) {
          saisieB = true;
        }
        else {
          saisieB = false;
        }

        if (numC < nbCl) { /* le numero de compte doit etre valide */
          b = depotouRetrait2(numC, comptes, saisie, saisieB, autoris);
          if (b) {
            printf("L'operation a ete correctement effectuee\n");
          }
          else {
            printf("L'operation a echoue");
          }
        }
        afficheTab(comptes, nbCl);
        break;
      }
    }

  } while (choix !=0);

  printf("Au revoir\n");
  return 0;
}
