#include <cini.h>

#define MAX 20

int main(int argc, char **argv)
{
  int i=0, lastCh=0;
  char chaine[MAX];

  //On récupère la chaine de caractères, max de caractères définit en define.
  printf("Veuillez rentrer la chaine de caractere.\n");
  if(fgets(chaine, MAX, stdin) == NULL) {
    printf("Erreur");
    exit(1);
  }
  printf("La chaine de caracteres saisie est : \n%s\n", chaine);

  //On cherche le dernier caractère qui nous intéresse.
  for(i=0 ; i<=MAX; i++) {
    if(chaine[i] == '\0') {
      lastCh=i-2; //-1 pour le terminant \0 et -1 pour la sortie de boucle (car i est à nouveau incrémenté).
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

