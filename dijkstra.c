#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "aqrtopo.h"

Un_truc *extraire_deb_liste(Un_elem **liste){

    Un_truc *temp = (*liste)->truc;
    Un_elem *tete = *liste;
    *liste = (*liste)->suiv;
    tete->suiv = NULL;
    free(tete);
    return temp;
}

Un_truc *extraire_liste(Un_elem **liste, Un_truc *truc){

    if(strcmp(truc->data.sta.nom,(*(liste))->truc->data.sta.nom) == 0){

        return extraire_deb_liste(liste);
    } 

    Un_elem *tete = *liste;
    Un_elem *temp = *liste;
    Un_truc *r_truc;

    tete = tete->suiv;

    while(tete != NULL){

        if(tete->suiv == NULL){
  
            if(strcmp(truc->data.sta.nom,tete->truc->data.sta.nom) == 0){

                r_truc = tete->truc;
                temp->suiv = NULL;
                free(tete);
                return r_truc;
            }

            return NULL;
        }

        if(strcmp(truc->data.sta.nom,tete->truc->data.sta.nom) == 0){

            temp->suiv = tete->suiv;
            r_truc = tete->truc;
            tete->suiv = NULL;
            free(tete);
            return r_truc;
        }

        temp = tete;
        tete = tete->suiv;
    }

    return NULL;
}


void dijkstra(Un_elem *liste_sta, Un_truc *sta_dep){

    Un_elem *Q = NULL;
    Q = (Un_elem*) malloc(sizeof(Un_elem));
    
    if(strcmp(sta_dep->data.sta.nom,liste_sta->truc->data.sta.nom) == 0){

        sta_dep->user_val = FLT_MAX;
        Q->truc = sta_dep;
    }

    else{

        liste_sta->truc->user_val = FLT_MAX;
        Q->truc = liste_sta->truc;
    }

    Q->suiv = NULL;
    liste_sta = liste_sta->suiv;
    Un_elem *temp = liste_sta;

    while(temp != NULL){ 

        if(temp->truc == sta_dep){

            sta_dep->user_val = 0.0;
            Q = inserer_liste_trie(Q,temp->truc);
        }

        else{

            temp->truc->user_val = 99999;
            Q = inserer_liste_trie(Q,temp->truc);
        }

        temp=temp->suiv;
    }

    Un_truc *sta;
    unsigned int i;
    unsigned int j;
    float temps_correspondance = 0.0;
    Un_truc *temp_con;
    
    while(Q != NULL){

        sta = extraire_deb_liste(&Q);

        for(i = 0 ; i < sta->data.sta.nb_con ; i++){

            if(strcmp((*(sta->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,sta->data.sta.nom) == 0){

                if(strcmp((*(sta->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,"Châtelet") == 0 || strcmp((*(sta->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,"Gare du Nord") == 0 || strcmp((*(sta->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,"Gare de Lyon") == 0 || strcmp((*(sta->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,"Nation") == 0 || strcmp((*(sta->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,"Saint-Lazare") == 0 || strcmp((*(sta->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,"Gare d'Austerlitz") == 0){

                    temps_correspondance = 7.0;
                }

                else{

                    temps_correspondance = 2.0;
                }

                if(sta->data.sta.con_pcc != NULL){

                    for(j = 0 ; j < sta->data.sta.nb_con ; j++){

                        temp_con = (*(sta->data.sta.tab_con + j));

                        if(strcmp(temp_con->data.con.sta_arr->data.sta.nom,sta->data.sta.con_pcc->data.sta.nom) == 0 && strcmp(temp_con->data.con.sta_dep->data.sta.nom,sta->data.sta.nom) == 0){

                            if(strcmp(temp_con->data.con.ligne->code,(*(sta->data.sta.tab_con + i))->data.con.ligne->code) == 0){

                                temps_correspondance = 0.0;
                                break;
                            }
                        }     
                    }
                }

                else{

                    temps_correspondance = 0.0;
                }

                if((*(sta->data.sta.tab_con + i))->data.con.sta_arr->user_val > sta->user_val + (*(sta->data.sta.tab_con + i))->user_val + temps_correspondance){

                    (*(sta->data.sta.tab_con + i))->data.con.sta_arr->user_val = sta->user_val + (*(sta->data.sta.tab_con + i))->user_val + temps_correspondance + 0.16;

                    (*(sta->data.sta.tab_con + i))->data.con.sta_arr->data.sta.con_pcc =  sta;

                    Un_truc *extrait = extraire_liste(&Q,(*(sta->data.sta.tab_con + i))->data.con.sta_arr);

                    if(extrait != NULL){

                        Q = inserer_liste_trie(Q,extrait);   
                    }
                }    
            }
        }  
    }

    return;
}

Un_elem *cherche_chemin(Un_truc *sta_arr){

    Un_elem *tete = NULL;
    tete = (Un_elem*) malloc(sizeof(Un_elem));

    if(tete == NULL){

        printf("Impossible d'allouer de la mémoire à tete dans la fonction cherche_chemin.c\n");
        return NULL;
    }

    tete->truc = sta_arr;
    tete->suiv = NULL;
    Un_elem* temp = tete;

    sta_arr = sta_arr->data.sta.con_pcc;
    
    while(sta_arr->user_val != 0.0){

        tete->suiv = (Un_elem*) malloc(sizeof(Un_elem));

        if(tete == NULL){

            printf("Impossible d'allouer de la mémoire à tete->suiv dans la fonction cherche_chemin.c\n");
            return NULL;
        }

        tete = tete->suiv;
        tete->truc = sta_arr;
        tete->suiv = NULL;
        sta_arr = sta_arr->data.sta.con_pcc;
    }

    tete->suiv = (Un_elem*) malloc(sizeof(Un_elem));

    if(tete == NULL){

        printf("Impossible d'allouer de la mémoire à tete->suiv dans la fonction cherche_chemin.c\n");
        return NULL;
    }

    tete = tete->suiv;
    tete->truc = sta_arr;
    tete->suiv = NULL;

    return temp;
}







    










