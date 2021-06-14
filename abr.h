#include "liste.h"
#include "dijkstra.h"
typedef struct _un_nabr
{
  Un_truc *truc; //La station
  struct _un_nabr *g; //Fils gauche strictement inferieur
  struct _un_nabr *d; //Fils droit
} Un_nabr;

Un_nabr *creer_nabr(Un_truc *truc);
Un_nabr* inserer_abr(Un_nabr* abr, Un_nabr* n);
Un_nabr* construire_abr(Un_elem* liste_sta);
void detruire_abr(Un_nabr* abr);
Un_truc* chercher_station(Un_nabr* abr, char* nom);
Un_elem* lire_connexions(char* nom_fichier, Une_ligne* liste_ligne, Un_nabr* abr_sta);
