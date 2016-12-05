#include <stdio.h>
#include <stdlib.h>
#include "fact.h"

int main(int argc, char *argv[]) {


  if(argc != 3){
    fprintf(stderr,"Nombre d'arguments incorrect.\n");
    return 1;
  }
  
  if(!strcmp(argv[1], "recursif"))
    printf(" resultat : %d.\n", fact_recursif(atoi(argv[2])));
  
  else
    if(!strcmp(argv[1], "iteratif"))
      printf(" resultat : %d.\n", fact_iteratif(atoi(argv[2])));
    else
      puts("Veuillez lancer le programme avec le nombre factoriel à calculer, puis \"iteratif\" ou \"recursif\" selon le mode souhaite.\n");

  return 0;
}
