#include <cini.h>

#define MAXCOMPTES 15

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

int creerCompte(int nbCl) {
  if(nbCl<MAXCOMPTES) {
    return nbCl+1;
  } else {
    return -1;
  }
}

float remunere(int montant) {
  if(montant>0) {
    montant+=montant/100*5;
    return montant;
  } else {
    return montant;
  }
}

float consulte(float comptes[], int numCompte) {
  return comptes[numCompte];
}

int main() {

    float comptes[MAXCOMPTES]= {150.5, 160, 12, 1200, 655};
    bool autoris[MAXCOMPTES]= {true, false, true, true, false};
    int nbCl = 5, minimumPos, testCreerCompte, i, compte;
    float moyenneComptes, montant;
//Affichage tableau initial.
    afficheTab(comptes, nbCl);

//Test question 1 : La moyenne des comptes.
    moyenneComptes=moyenne(comptes, nbCl);
    printf("La moyenne des comptes est %f.\n", moyenneComptes);

//Test question 2 : L'indice de la valeur minimum.
    minimumPos=minPos(comptes, nbCl);
    if(minimumPos>=0) {
      printf("L'indice de la solde minimale qui n'est pas a decouvert est %d.\n", minimumPos);
    } else {
      printf("Tous les comptes sont a decouvert.\n");
    }

//Test question 3 : Création d'un nouveau compte.
    testCreerCompte=creerCompte(nbCl);
    if(testCreerCompte==-1) {
      printf("Nombre de comptes maximum deja atteint : impoossible de creer un novueau compte.\n");
    } else {
      nbCl=testCreerCompte;
      printf("Veuillez indiquer le montant du nouveau compte souhaite : ");
      if(scanf("%f", &montant) != 1) {
        printf("Erreur dans la fonction creerCompte : le montant rentre par l'utilisateur doit etre un float.\n");
        exit(1);
      }
      comptes[nbCl-1]=montant;
      printf("\nUn %deme compte a ete cree.\n", nbCl);
    }
    afficheTab(comptes, nbCl);

//Test question 4 : Rémunération de 5% des comptes avec solde positive.
    for(i=0 ; i<nbCl ; i++) {
      comptes[i]=remunere(comptes[i]);
    }
    printf("Offre de la banque : comptes a solde positive remuneres a 5%%.\n");
    afficheTab(comptes, nbCl);

//Test question 5 : Consulter son compte.
    printf("Veuillez indiquer le numero(indice) du compte a consulter : ");
    if(scanf("%d", &compte) != 1) {
      printf("\nErreur dans la fonction main : le numero de compte rentre par l'utilisateur doit etre un entier.\n");
      exit(1);
    }
    if(compte>=0 && compte<nbCl) {
      montant=consulte(comptes, compte);
      printf("\nCompte numero %d - solde : %f.\n", compte, montant);
    } else {
      printf("\nCe compte n'existe pas.\n");
    }

    return 0;
  }
