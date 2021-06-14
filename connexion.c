#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef _CONNEXION_
#define _CONNEXION
#include "abr.h"
#endif

Un_elem *lire_connexions(char *nom_fichier, Une_ligne *liste_ligne, Un_nabr *abr_sta){

    FILE* connexion = NULL;
	connexion = fopen(nom_fichier,"rw");
	
	if (connexion == NULL){

		printf("Erreur d'ouverture du fichier dans la fonction lire_connexions dans exo4.c !\n");
		return NULL;
	}
    
	Un_elem *tete = NULL;
    tete = (Un_elem*) malloc(sizeof(Un_elem));

    if(tete == NULL){

        printf("Impossible d'allouer de la mémoire à tete dans la fonction lire_connexions dans le programme exo4.c\n");
		fclose(connexion);
        return NULL;
    }

	char *ligne = NULL;
	char *p_line;
    size_t longueur = 0;
	Un_elem *temp_tete = tete;
	Un_elem *temp = tete;

	while (getline(&ligne, &longueur, connexion) != -1){

        p_line = NULL;

		p_line = strtok(ligne,";");

        temp = tete;

        tete->truc = NULL;
        tete->truc = (Un_truc*) malloc(sizeof(Un_truc));

        if(tete->truc == NULL){

            printf("Impossible d'allouer de la mémoire à tete->truc dans la fonction lire_connexions dans le programme exo4.c\n");
            fclose(connexion);
            return NULL;
        }

        tete->truc->type = 1;

        tete->truc->data.con.sta_dep = chercher_station(abr_sta,p_line);

        p_line = strtok(NULL,";");

        tete->truc->data.con.sta_arr = chercher_station(abr_sta,p_line);

        p_line = strtok(NULL,";");

        tete->truc->data.con.ligne = chercher_ligne(liste_ligne,p_line);

        p_line = strtok(NULL,";");

        tete->truc->user_val = 0.0;

        tete->truc->user_val = (float) atof(p_line);

        tete->suiv = NULL;

        tete->suiv = (Un_elem*) malloc(sizeof(Un_elem));

        if(tete->suiv == NULL){

            printf("Impossible d'allouer de la mémoire à tete->suiv dans la fonction lire_connexions dans le programme exo4.c\n");
            fclose(connexion);
            return NULL;
        }

        tete = tete->suiv;
        tete->truc = NULL;
	}

	free(tete);
	free(ligne);
	temp->suiv = NULL;
    fclose(connexion);

    tete = NULL;
    tete = temp_tete;
    Un_truc *sta = NULL;

    while(tete != NULL){

        sta = chercher_station(abr_sta,tete->truc->data.con.sta_dep->data.sta.nom);

        if(sta->data.sta.tab_con == NULL && sta != NULL){

            sta->data.sta.nb_con++;
            sta->data.sta.tab_con = (Un_truc**) malloc(sizeof(Un_truc*));

            if(sta->data.sta.tab_con == NULL){

                printf("Impossible de malloc tab_con dans la fonction lire_connexion dans exo.4c\n");
                return NULL;
            }

            *(sta->data.sta.tab_con) = tete->truc;
        }

        else if(sta != NULL){

            sta->data.sta.nb_con++;
            sta->data.sta.tab_con = (Un_truc**) realloc(sta->data.sta.tab_con,sta->data.sta.nb_con*sizeof(Un_truc*));

            if(sta->data.sta.tab_con == NULL){

                printf("Impossible de realloc tab_con dans la fonction lire_connexion dans exo.4c\n");
                return NULL;
            }

            *(sta->data.sta.tab_con + sta->data.sta.nb_con - 1) = tete->truc;
        }

        sta = NULL;
        sta = chercher_station(abr_sta,tete->truc->data.con.sta_arr->data.sta.nom);

        if(sta->data.sta.tab_con == NULL && sta != NULL){

            sta->data.sta.nb_con++;
            sta->data.sta.tab_con = (Un_truc**) malloc(sizeof(Un_truc*));

            if(sta->data.sta.tab_con == NULL){

                printf("Impossible de malloc tab_con dans la fonction lire_connexion dans exo.4c\n");
                return NULL;
            }

            *(sta->data.sta.tab_con) = tete->truc;
        }

        else if(sta != NULL){

            sta->data.sta.nb_con++;
            sta->data.sta.tab_con = (Un_truc**) realloc(sta->data.sta.tab_con,sta->data.sta.nb_con*sizeof(Un_truc*));

            if(sta->data.sta.tab_con == NULL){

                printf("Impossible de realloc tab_con dans la fonction lire_connexion dans exo.4c\n");
                return NULL;
            }

            *(sta->data.sta.tab_con + sta->data.sta.nb_con - 1) = tete->truc;
        }

        tete = tete->suiv;
        sta = NULL;
    }

    return temp_tete;
}