#include <stdlib.h>
#include<stdio.h>


typedef struct
{
  unsigned int dim;
  int *coeffs;
} noyau_t;

noyau_t *creer_noyau(unsigned int dim) {
  noyau_t *noya;
  
  noya->coeffs = (int *) malloc (dim*dim*sizeof (int )) ;
  printf("cccc\n"); 
  noya->dim = dim ;
  
  //printf("dim --> %d \n",noy->dim);
  return noya;
}

main(){
  noyau_t *noy;
  int i, j;
  unsigned int c = 3 ;
  noy = creer_noyau(c);
  
  for(i = 0 ; i < noy->dim ; i++){
    for(j = 0 ; j < noy->dim ; j++)
      printf("%d\t", noy->coeffs[i * noy->dim + j]);
    printf("\n");
  }
  
}
