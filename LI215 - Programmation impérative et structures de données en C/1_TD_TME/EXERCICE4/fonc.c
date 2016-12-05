#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init(int *tab, int taille) {
  const int MAX = 100;
  int i;


  for(i = 0 ; i < taille ; i++)
    tab[i] = rand() % MAX;
  
}

void somme(int *tab1, int *tab2, int *tab3, int taille) {
  int i;

  for(i = 0 ; i < taille ; i++)
    tab3[i] = tab2[i] + tab1[i];
}

int main() {
  srand(time(NULL));
  int a[10];
  int b[10];
  int c[10];
  int i;
  
  init(a, 10);
  init(b, 10);
  init(c, 10);

  for(i = 0 ; i < 10 ; i++)
    printf("%d || %d || %d\n", a[i], b[i], c[i]);

  puts("\n\n");
  somme(a, b, c, 10);
  
  for(i = 0 ; i < 10 ; i++)
   printf("%d || %d || %d\n", a[i], b[i], c[i]);

}
