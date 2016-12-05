#include <cini.h>

#define MAX 20

int main(int argc, char **argv)
{
  int i=0, lastCh=0;
  char chaine[MAX];

  //On r�cup�re la chaine de caract�res, max de caract�res d�finit en define.
  printf("Veuillez rentrer la chaine de caractere.\n");
  if(fgets(chaine, MAX, stdin) == NULL) {
    printf("Erreur");
    exit(1);
  }
  printf("La chaine de caracteres saisie est : \n%s\n", chaine);

  //On cherche le dernier caract�re qui nous int�resse.
  for(i=0 ; i<=MAX; i++) {
    if(chaine[i] == '\0') {
      lastCh=i-2; //-1 pour le terminant \0 et -1 pour la sortie de boucle (car i est � nouveau incr�ment�).
      break;
    }
  }

  char miroir[lastCh];
  for(i=0 ; i<=lastCh ; i++){
  miroir[lastCh-i]=chaine[i];
  }
  printf("La chaine de caracteres miroir est : \n%s\n", miroir);

	return 0;
}

