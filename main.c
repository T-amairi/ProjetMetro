#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "aqrtopo.h"


int main(int argc, char **argv)
{
   
    if (argc != 3)
    {
        fprintf(stderr,"Veuillez saisir le noms des stations de départ et d'arrivée entre guillemets séparé par un espace svp\n");
        exit(EXIT_FAILURE);
    }

    Un_elem *station = lire_stations("base_de_donnees.csv");
    Une_ligne *ligne = lire_lignes("lignes_metro.csv");
    Un_nabr *abr = construire_abr(station);
    Un_elem *connexion = lire_connexions("connexions.csv",ligne,abr);
    
    char* dept = argv[2];
    
    char *nom = malloc((strlen(dept) + 1)*sizeof(char));
    strcpy(nom,dept);
    nom[strlen(dept)] = '\0';

    Un_truc *dep = chercher_station(abr,nom);
    free(nom);
    nom = NULL;

    char* arrv = argv[1];
    nom = malloc((strlen(arrv) + 1)*sizeof(char));
    strcpy(nom,arrv);
    nom[strlen(arrv)] = '\0';

    dijkstra(station,dep);

    Un_truc *arr = chercher_station(abr,nom);
    Un_elem *chemin = cherche_chemin(arr);
    Un_elem *temp_chemin = chemin;
    Un_elem *temp_chemin2 = chemin;
    Un_elem *temp_chemin3 = chemin;
    char *nom_ligne = NULL;
    //char *nom_station = NULL;
    char *nom_ligne_temp = NULL;
    int test = 0;
    Un_truc *sta1;
    Un_truc *sta2;
    Un_truc *sta3;
    int c = 0;

    while(chemin != NULL){

        printf("%s\n",chemin->truc->data.sta.nom);
        chemin = chemin->suiv;
    }

    chemin = temp_chemin;

    for(unsigned int i = 0; i < chemin->truc->data.sta.nb_con ; i++){

        if(strcmp((*(chemin->truc->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,chemin->suiv->truc->data.sta.nom) == 0 && strcmp((*(chemin->truc->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,chemin->truc->data.sta.nom) == 0){

            nom_ligne = (*(chemin->truc->data.sta.tab_con + i))->data.con.ligne->code;
        }
    }

    nom_ligne_temp = nom_ligne;

    while(chemin->suiv != NULL){

        test = 0;

        for(unsigned int i = 0; i < chemin->truc->data.sta.nb_con ; i++){

            if(strcmp((*(chemin->truc->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,chemin->suiv->truc->data.sta.nom) == 0 && strcmp((*(chemin->truc->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,chemin->truc->data.sta.nom) == 0){

                if(strcmp(nom_ligne,(*(chemin->truc->data.sta.tab_con + i))->data.con.ligne->code) == 0){

                    test = 1;
                    break;
                }
            }
        }
        
        if(test == 0){

            sta1 = chemin->truc;
            sta2 = temp_chemin2->truc;
            sta3 = sta1;

            while(c != 2){

                for(unsigned int i = 0; i < sta1->data.sta.nb_con ; i++){

                    if(strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,sta1->data.sta.nom) == 0 && strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,sta2->data.sta.nom) != 0){

                        if(strcmp(nom_ligne,(*(sta1->data.sta.tab_con + i))->data.con.ligne->code) == 0){

                            sta2 = sta1;
                            sta1 = (*(sta1->data.sta.tab_con + i))->data.con.sta_arr;
                            c = sta1->data.sta.nb_con;
                            break;
                        }
                    } 
                }

                if(strcmp(sta1->data.sta.nom,sta3->data.sta.nom) != 0){

                    sta3 = sta1;
                }

                else{

                    c = 0;

                    for(unsigned int i = 0; i < sta1->data.sta.nb_con ; i++){

                        if(strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,sta1->data.sta.nom) == 0 || strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,sta2->data.sta.nom) != 0 || strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,sta1->data.sta.nom) == 0 || strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,sta2->data.sta.nom) != 0){

                            if(strcmp(nom_ligne,(*(sta1->data.sta.tab_con + i))->data.con.ligne->code) == 0){

                                c++;
                            }
                        } 
                    }
                }
            }

            break;
        }

        c = 0;
        temp_chemin2 = chemin;
        chemin = chemin->suiv;
    }

    if(test == 1){

        sta1 = chemin->truc;
        sta2 = temp_chemin2->truc;
        sta3 = sta1;

        while(c != 2){

            for(unsigned int i = 0; i < sta1->data.sta.nb_con ; i++){

                if(strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,sta1->data.sta.nom) == 0 && strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,sta2->data.sta.nom) != 0){

                    if(strcmp(nom_ligne,(*(sta1->data.sta.tab_con + i))->data.con.ligne->code) == 0){

                        sta2 = sta1;
                        sta1 = (*(sta1->data.sta.tab_con + i))->data.con.sta_arr;
                        c = sta1->data.sta.nb_con;
                        break;
                    }
                } 
            }

            if(strcmp(sta1->data.sta.nom,sta3->data.sta.nom) != 0){

                sta3 = sta1;
            }

            else{

                c = 0;

                for(unsigned int i = 0; i < sta1->data.sta.nb_con ; i++){

                    if(strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,sta1->data.sta.nom) == 0 || strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,sta2->data.sta.nom) != 0 || strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,sta1->data.sta.nom) == 0 || strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,sta2->data.sta.nom) != 0){

                        if(strcmp(nom_ligne,(*(sta1->data.sta.tab_con + i))->data.con.ligne->code) == 0){

                            c++;
                        }
                    } 
                }
            }
        }
    }

    test = 0;
    c = 0;
    chemin = temp_chemin;
    nom_ligne = nom_ligne_temp;
    
    printf("Trajet pour aller de %s à %s : \n",arr->data.sta.nom,dep->data.sta.nom);
    printf("\n");
    printf("Prendre le %s direction %s à la station %s\n",nom_ligne,sta1->data.sta.nom,chemin->truc->data.sta.nom);
    printf("\n");

    while(chemin != NULL){

        if(chemin->suiv != NULL){

            for(unsigned int i = 0; i < chemin->truc->data.sta.nb_con ; i++){

                if(strcmp((*(chemin->truc->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,chemin->suiv->truc->data.sta.nom) == 0 && strcmp((*(chemin->truc->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,chemin->truc->data.sta.nom) == 0){

                    if(strcmp(nom_ligne,(*(chemin->truc->data.sta.tab_con + i))->data.con.ligne->code) == 0){

                        test = 1;
                        break;
                    }
                }
            }
        }
        
        temp_chemin2 = chemin;

        if(chemin->suiv != NULL && test == 0){

            for(unsigned int i = 0; i < chemin->truc->data.sta.nb_con ; i++){

                if(strcmp((*(chemin->truc->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,chemin->suiv->truc->data.sta.nom) == 0 && strcmp((*(chemin->truc->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,chemin->truc->data.sta.nom) == 0){

                    if(strcmp(nom_ligne,(*(chemin->truc->data.sta.tab_con + i))->data.con.ligne->code) != 0){

                        printf("%s, ",chemin->truc->data.sta.nom);
                        printf("ligne %s\n",nom_ligne);
                        printf("\n");
                        nom_ligne = (*(chemin->truc->data.sta.tab_con + i))->data.con.ligne->code;
                        sta1 = chemin->truc;
                        sta2 = temp_chemin3->truc;
                        sta3 = sta1;

                        while(c != 2){

                            for(unsigned int i = 0; i < sta1->data.sta.nb_con ; i++){

                                if(strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,sta1->data.sta.nom) == 0 && strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,sta2->data.sta.nom) != 0){

                                    if(strcmp(nom_ligne,(*(sta1->data.sta.tab_con + i))->data.con.ligne->code) == 0){

                                        sta2 = sta1;
                                        sta1 = (*(sta1->data.sta.tab_con + i))->data.con.sta_arr;
                                        c = sta1->data.sta.nb_con;
                                        break;
                                    }
                                } 
                            }

                            if(strcmp(sta1->data.sta.nom,sta3->data.sta.nom) != 0){

                                sta3 = sta1;
                            }

                            else{

                                c = 0;

                                for(unsigned int i = 0; i < sta1->data.sta.nb_con ; i++){

                                    if(strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,sta1->data.sta.nom) == 0 || strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,sta2->data.sta.nom) != 0 || strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,sta1->data.sta.nom) == 0 || strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,sta2->data.sta.nom) != 0){

                                        if(strcmp(nom_ligne,(*(sta1->data.sta.tab_con + i))->data.con.ligne->code) == 0){

                                            c++;
                                        }
                                    } 
                                }
                            }
                        }

                        while(c != 2){

                            for(unsigned int i = 0; i < sta1->data.sta.nb_con ; i++){

                                if(strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,sta1->data.sta.nom) == 0 && strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,sta2->data.sta.nom) != 0){

                                    if(strcmp(nom_ligne,(*(sta1->data.sta.tab_con + i))->data.con.ligne->code) == 0){

                                        sta2 = sta1;
                                        sta1 = (*(sta1->data.sta.tab_con + i))->data.con.sta_arr;
                                        c = sta1->data.sta.nb_con;
                                        break;
                                    }
                                } 
                            }

                            if(strcmp(sta1->data.sta.nom,sta3->data.sta.nom) != 0){

                                sta3 = sta1;
                            }

                            else{

                                c = 0;

                                for(unsigned int i = 0; i < sta1->data.sta.nb_con ; i++){

                                    if(strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,sta1->data.sta.nom) == 0 || strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,sta2->data.sta.nom) != 0 || strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_arr->data.sta.nom,sta1->data.sta.nom) == 0 || strcmp((*(sta1->data.sta.tab_con + i))->data.con.sta_dep->data.sta.nom,sta2->data.sta.nom) != 0){

                                        if(strcmp(nom_ligne,(*(sta1->data.sta.tab_con + i))->data.con.ligne->code) == 0){

                                            c++;
                                        }
                                    } 
                                }
                            }
                        }
        

                        printf("Correspondance à %s ligne %s direction %s\n",chemin->truc->data.sta.nom,nom_ligne,sta1->data.sta.nom);
                        printf("\n");
                        nom_ligne = (*(chemin->truc->data.sta.tab_con + i))->data.con.ligne->code;
                        break;
                    }
                }
            }
        }

        printf("%s, ",chemin->truc->data.sta.nom);
        printf("ligne %s\n",nom_ligne);

        test = 0;
        c = 0;
        temp_chemin3 = chemin;
        chemin = chemin->suiv;
    }

    printf("\n");
    printf("Vous êtes arrivé !\n");
    printf("\n");
    printf("Temps de trajet estimé : %.2f minutes\n",arr->user_val);

    chemin = temp_chemin;

    detruire_liste_et_truc(station);
    detruire_liste_et_truc(connexion);
    detruire_liste(chemin);
    detruire_abr(abr);
    detruire_lignes(ligne);
    free(nom);

    return 0;
}