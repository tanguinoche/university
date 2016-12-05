#include <cini.h>

#define ORIGINSEM    4
#define JORIGIN     15
#define MORIGIN     10
#define AORIGIN   1582

/*--------------------------------------------------------------*/

void affiche_jour (int no) {
   if (no == 0) { printf("lundi"); }
   if (no == 1) { printf("mardi"); }
   if (no == 2) { printf("mercredi"); }
   if (no == 3) { printf("jeudi"); }
   if (no == 4) { printf("vendredi"); }
   if (no == 5) { printf("samedi"); }
   if (no == 6) { printf("dimanche"); }
   if ( (no < 0) || (no > 6)) {
      printf("Cette valeur ne correspond pas a un jour de la semaine\n");
   }
}

/*--------------------------------------------------------------*/

void affiche_mois (int no) {
   if (no ==  1) { printf("janvier"); }
   if (no ==  2) { printf("fevrier"); }
   if (no ==  3) { printf("mars"); }
   if (no ==  4) { printf("avril"); }
   if (no ==  5) { printf("mai"); }
   if (no ==  6) { printf("juin"); }
   if (no ==  7) { printf("juillet"); }
   if (no ==  8) { printf("aout"); }
   if (no ==  9) { printf("septembre"); }
   if (no == 10) { printf("octobre"); }
   if (no == 11) { printf("novembre"); }
   if (no == 12) { printf("decembre"); }
   if ( (no < 1) || (no > 12)) {
      printf("Cette valeur ne correspond pas a un mois du calendrier\n");
   }
}

/*--------------------------------------------------------------*/

int main() {

  return 0;
}
