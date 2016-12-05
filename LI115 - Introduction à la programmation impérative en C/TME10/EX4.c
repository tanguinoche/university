#include <cini.h>

void supprime_espaces(char chaine[], int *nb, int i) {
  if(chaine[i]==' ') {
    int j;
    for(j=i ; chaine[j]!='\0' ; j++) {
      chaine[j]=chaine[j+1];
    }
    *nb+=1;
  }
}


int main () {
  char phrase[] = "Je mange du gateau.";
  int i, nb=0;

  for(i=0 ; phrase[i]!='\0' ; i++) {
    supprime_espaces(phrase, &nb, i);
  }

  printf("Nombre d'espaces supprimes : %d\n", nb);
  printf("Phrase modifiee : \n");

  for(i=0 ; phrase[i]!='\0' ; i++) {
    printf("%c", phrase[i]);
  }

  return 0;
}
