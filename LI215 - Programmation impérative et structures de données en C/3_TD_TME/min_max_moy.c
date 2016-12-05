#include <stdio.h>

void min_max_moy(int tab[], int taille, int* max, int* min, double* moy)
{
    int i;
    int min_temp = tab[0];
    int max_temp = tab[0];
    int somme = tab[0];
    for(i = 0 ; i < taille ; i++) {
        if(max_temp < tab[i])
                max_temp = tab[i];
        if(min_temp > tab[i])
            min_temp = tab[i];
        somme += tab[i];
    }
    *max = max_temp;
    *min = min_temp;
    *moy = (double)(somme / taille);
    printf("max = %d, min = %d, moy = %d \n", *max, *min, *moy);
 }
 
 int main () 
{
    int tab[5] = {5, 6, 7, 8, 21};
    int mini, maxi;
    double moyenne;
    int taille = 5;
    min_max_moy(tab, taille, &mini, &maxi, &moyenne);
    return 0;
 }
