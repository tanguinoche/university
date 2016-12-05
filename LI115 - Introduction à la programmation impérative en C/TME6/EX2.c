#include <cini.h>

#define MAX 20

int main(int argc, char **argv)
{
  int i=0, lastCh=0, palindrome=0;
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

  /*Tester si une chaine de caract�re est un palindrome :
   * La premi�re lettre est �gale � la derni�re.
   * La n+1 premi�re est �gale � la n-1 derni�re.
   * etc...
   * Si deux caract�res ne sont pas �gaux, on renvoie FALSE et on quitte la boucle.
   * Pour conna�tre le milieu du mot, on utilise lastCh/2, il n'y a pas de soucis, car si lastCh=15, alors le r�sultat sera 7.
   * En effet, nous travaillons ici avec des types int.*/

  for(i=0 ; i<=(lastCh/2) ; i++){
  if(chaine[i] == chaine[lastCh-i]) {
    palindrome = 1;
  } else {
    palindrome = 0;
    break;
  }
}

if(palindrome){
	printf("Cette chaine est un palindrome.\n");
}else{
	printf("Cette chaine n'est pas un palindrome.\n");
}

return 0;
}
