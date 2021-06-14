#include "abr.h"

typedef struct _un_noeud
{
  Un_truc *truc; //Une station ou une connexion
  Une_coord limite_no; //Limite zone
  Une_coord limite_se; //Limite zone
  struct _un_noeud *no; //Fils pour quart NO
  struct _un_noeud *so; //Fils pour quart SO
  struct _un_noeud *ne; //Fils pour quart NE
  struct _un_noeud *se; //Fils pour quart SE
} Un_noeud;

Un_noeud* inserer_aqr(Un_noeud* aqr, Une_coord limite_no, Une_coord limite_se, Un_truc* truc);
Un_noeud* construire_aqr(Un_elem* liste);
void detruire_aqr(Un_noeud *aqr);
Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord);
void chercher_zone(Un_noeud *aqr, Un_elem **liste);
Un_truc* extraire_deb_liste(Un_elem** liste);
Un_truc* extraire_liste(Un_elem** liste, Un_truc* truc);
Un_noeud *chercher_noeud(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se);


