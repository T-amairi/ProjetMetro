#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abr.h"


Un_nabr *creer_nabr(Un_truc *truc)
{
  Un_nabr* abr = (Un_nabr*) malloc(sizeof(Un_nabr));
  abr->truc=truc;
  abr->g=NULL;
  abr->d=NULL;
  return abr;
}

Un_nabr* inserer_abr(Un_nabr* abr, Un_nabr* n)
{
  if(abr == NULL)
    return n;
  else
  {
    if(strcmp(abr->truc->data.sta.nom,n->truc->data.sta.nom) > 0)
      abr->g = inserer_abr(abr->g,n);
    else
      abr->d = inserer_abr(abr->d,n);
  }
  return abr;
}

Un_nabr* construire_abr(Un_elem* liste_sta)
{
  Un_nabr* abr = NULL;
  Un_elem* temp = liste_sta;
  while(temp != NULL)
  {
    Un_nabr* maillon = creer_nabr(temp->truc);
    abr = inserer_abr(abr, maillon);
    temp = temp->suiv;
  }
  return abr;
}

void detruire_abr(Un_nabr* abr)
{
  if(abr == NULL)
    return;
  detruire_abr(abr->g);
  detruire_abr(abr->d);
  
  free(abr);
}

Un_truc *chercher_station(Un_nabr *abr,char *nom){


  while(abr!=NULL){

    if(strcmp(nom,abr->truc->data.sta.nom) == 0){
      return abr->truc;
    }
    else if(strcmp(nom,abr->truc->data.sta.nom)<0){
      abr=abr->g;
    }
    else{
      abr=abr->d;
    }
  }

  return NULL;
}

