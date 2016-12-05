#include <stdio.h>


/*Fonction récursive*/
void affiche(int n) 
{
  if(n >= 0){
    printf("%d\n", n);
    return affiche(n-1);
  }
}



int main (){
  int nb = 9;
  affiche(nb);
}

