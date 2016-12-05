#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

double ArchiPi(uint64_t n)
{
  if(n > 4) {
  	double tmp = ArchiPi(n/2);
  	return sqrt(2 * (1 - sqrt( 1 - (tmp * tmp)/4)));
  	}
return sqrt(2);
}

double ArchiPiBis(uint64_t n)
{
  if(n > 4) {
  	double tmp = ArchiPiBis(n/2);
     return sqrt((((tmp*tmp)/4) / (2 * (1 + sqrt(1 - (tmp*tmp)/4)))) * 4);
     }
  return sqrt(2);
}


int main(){
  int i;
  uint64_t n=2;
  
    for(i=1; i<=30; i++) {
    printf("Resultat calcul pour n=2^%d : %.23f\n", i, n*ArchiPi(n)/2);
    n = (2<<i);
    }
    
    printf("\n\n");
    	
    n = 2;
    for(i=1; i<=30; i++) {
    printf("Resultat calcul pour n=2^%d : %.23f\n", i, n*ArchiPiBis(n)/2);
    n = (2<<i);
    }  
    
    printf("Et le fameux M_PI :           %.23f !!\n", M_PI);
      return 0;
}


/* La suite des Ln semble bien converger vers Pi */
