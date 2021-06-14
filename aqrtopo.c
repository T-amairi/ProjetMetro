#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aqrtopo.h"

Un_noeud *inserer_aqr(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se, Un_truc *truc){

    Un_noeud *tete = aqr;

    Un_noeud *nv_noeud = NULL;

    nv_noeud = (Un_noeud*) malloc(sizeof(Un_noeud));

    if(nv_noeud == NULL){

        printf("Impossible d'allouer de la mémoire à nv_noeud dans la fonction inserer_aqr dans le programme aqrtopo.c\n");
        return NULL;
    }

    nv_noeud->truc = truc;
    nv_noeud->limite_no = limite_no;
    nv_noeud->limite_se = limite_se;
    nv_noeud->no = NULL;
    nv_noeud->so = NULL;
    nv_noeud->ne = NULL;
    nv_noeud->se = NULL;

    Un_noeud *no = tete->no;
    Un_noeud *so = tete->so;
    Un_noeud *ne = tete->ne;
    Un_noeud *se = tete->se;

    float m_1 = (float) ((nv_noeud->limite_no).lon + (nv_noeud->limite_se).lon)/2.0;
    float m_2 = (float) ((nv_noeud->limite_no).lat + (nv_noeud->limite_se).lat)/2.0;

  

    if((no == NULL) && ((nv_noeud->truc->coord).lat < m_2) && ((nv_noeud->truc->coord).lon > m_1)){

        (nv_noeud->limite_no).lat = m_2;
        (nv_noeud->limite_no).lon = m_1;
        aqr->no = nv_noeud;
        return tete;
    }

    else if((so == NULL) && ((nv_noeud->truc->coord).lat < m_2) && ((nv_noeud->truc->coord).lon < m_1)){

        (nv_noeud->limite_no).lat = m_2;
        (nv_noeud->limite_se).lon = m_1;
        aqr->so = nv_noeud;
        return tete;
    }

    else if((ne == NULL) && ((nv_noeud->truc->coord).lat > m_2) && ((nv_noeud->truc->coord).lon > m_1)){

        (nv_noeud->limite_se).lat = m_2;
        (nv_noeud->limite_no).lon = m_1;
        aqr->ne = nv_noeud;
        return tete;
    }

    else if((se == NULL) && ((nv_noeud->truc->coord).lat > m_2) && ((nv_noeud->truc->coord).lon < m_1)){

        (nv_noeud->limite_se).lat = m_2;
        (nv_noeud->limite_se).lon = m_1;
        aqr->se = nv_noeud;
        return tete;
    }

    else if((no != NULL) && ((nv_noeud->truc->coord).lat < m_2) && ((nv_noeud->truc->coord).lon > m_1)){

        (nv_noeud->limite_no).lat = m_2;
        (nv_noeud->limite_no).lon = m_1;

        Une_coord limite_no_v2 = nv_noeud->limite_no; 
        Une_coord limite_se_v2 = nv_noeud->limite_se; 

        free(nv_noeud);
        return inserer_aqr(aqr->no,limite_no_v2,limite_se_v2,truc);
    }

    else if((so != NULL) && ((nv_noeud->truc->coord).lat < m_2) && ((nv_noeud->truc->coord).lon < m_1)){

        (nv_noeud->limite_no).lat = m_2;
        (nv_noeud->limite_se).lon = m_1;

        Une_coord limite_no_v2 = nv_noeud->limite_no; 
        Une_coord limite_se_v2 = nv_noeud->limite_se; 

        free(nv_noeud);
        return inserer_aqr(aqr->so,limite_no_v2,limite_se_v2,truc);
    }

    else if((ne != NULL) && ((nv_noeud->truc->coord).lat > m_2) && ((nv_noeud->truc->coord).lon > m_1)){

        (nv_noeud->limite_se).lat = m_2;
        (nv_noeud->limite_no).lon = m_1;

        Une_coord limite_no_v2 = nv_noeud->limite_no; 
        Une_coord limite_se_v2 = nv_noeud->limite_se; 

        free(nv_noeud);
        return inserer_aqr(aqr->ne,limite_no_v2,limite_se_v2,truc);
    }

    else if((se != NULL) && ((nv_noeud->truc->coord).lat > m_2) && ((nv_noeud->truc->coord).lon < m_1)){

        (nv_noeud->limite_se).lat = m_2;
        (nv_noeud->limite_se).lon = m_1;

        Une_coord limite_no_v2 = nv_noeud->limite_no; 
        Une_coord limite_se_v2 = nv_noeud->limite_se; 

        free(nv_noeud);
        return inserer_aqr(aqr->se,limite_no_v2,limite_se_v2,truc);
    }

    return tete;
}

Un_noeud *construire_aqr(Un_elem *liste){

    Une_coord limite_no;
    Une_coord limite_se;

    Une_coord *p_limite_no = &limite_no;
    Une_coord *p_limite_se = &limite_se;

    limites_zone(liste,p_limite_no,p_limite_se);

    Un_noeud *tete = NULL;

    tete = (Un_noeud*) malloc(sizeof(Un_noeud));

    if(tete == NULL){

        printf("Impossible d'allouer de la mémoire à tete dans la fonction construire_aqr dans le programme aqrtopo.c\n");
        return NULL;
    }

    tete->truc = liste->truc; 
    tete->limite_no = limite_no;
    tete->limite_se = limite_se;

    tete->no = NULL;
    tete->so = NULL;
    tete->ne = NULL;
    tete->se = NULL;

    liste = liste->suiv;

    while(liste != NULL){

        inserer_aqr(tete,limite_no,limite_se,liste->truc);
        liste = liste->suiv;
    }

    return tete;
}

void detruire_aqr(Un_noeud *aqr){

    if (aqr != NULL){

        detruire_aqr(aqr->no);
        detruire_aqr(aqr->so);
        detruire_aqr(aqr->ne);
        detruire_aqr(aqr->se);
        free(aqr);
    }

    return;
}

Un_truc *chercher_aqr(Un_noeud *aqr, Une_coord coord){

    if(aqr == NULL){

        printf("Le truc cherché n'existe pas dans le quadtree\n");
        return NULL;
    }

    if(((aqr->truc->coord).lon == coord.lon) && ((aqr->truc->coord).lat == coord.lat)){

        return aqr->truc;
    }

    if(aqr->no != NULL){

        if((aqr->no->limite_no).lat > coord.lat && (aqr->no->limite_no).lon < coord.lon && (aqr->no->limite_se).lat < coord.lat && (aqr->no->limite_se).lon > coord.lon){

            return chercher_aqr(aqr->no,coord);
        }
    }

    if(aqr->so != NULL){

        if((aqr->so->limite_no).lat > coord.lat && (aqr->no->limite_se).lon > coord.lon && (aqr->no->limite_se).lat < coord.lat && (aqr->no->limite_no).lon < coord.lon){

            return chercher_aqr(aqr->so,coord);
        }
    }

    if(aqr->ne != NULL){

        if((aqr->ne->limite_se).lat < coord.lat && (aqr->ne->limite_no).lon < coord.lon && (aqr->no->limite_no).lat > coord.lat && (aqr->no->limite_se).lon > coord.lon){

            return chercher_aqr(aqr->ne,coord);
        }
    }

    if(aqr->se != NULL){

        if((aqr->se->limite_se).lat < coord.lat && (aqr->se->limite_se).lon > coord.lon && (aqr->no->limite_no).lat < coord.lat && (aqr->no->limite_no).lon < coord.lon){

            return chercher_aqr(aqr->se,coord);
        }
    }

    return NULL;
}

Un_noeud *chercher_noeud(Un_noeud *aqr, Une_coord limite_no, Une_coord limite_se){

    if(aqr == NULL){

        printf("Le noeud cherché n'existe pas dans le quadtree\n");
        return NULL;
    }

    if(limite_se.lat == (aqr->limite_se).lat && limite_se.lon == (aqr->limite_se).lon && limite_no.lon == (aqr->limite_no).lon && limite_no.lat == (aqr->limite_no).lat){

        return aqr;
    }

    if(aqr->no != NULL){

        if((aqr->limite_se).lat == limite_se.lat && (aqr->limite_no).lat > limite_no.lat && (aqr->limite_se).lon == limite_se.lon && (aqr->limite_no).lon < limite_no.lon){

            chercher_noeud(aqr->no,limite_no,limite_se);
        }
    }

    else if(aqr->so != NULL){

        if((aqr->limite_se).lat == limite_se.lat && (aqr->limite_no).lat > limite_no.lat && (aqr->limite_se).lon > limite_se.lon && (aqr->limite_no).lon == limite_no.lon){

            chercher_noeud(aqr->so,limite_no,limite_se);
        }
    }

    else if(aqr->ne != NULL){

        if((aqr->limite_se).lat < limite_se.lat && (aqr->limite_no).lat == limite_no.lat && (aqr->limite_se).lon == limite_se.lon && (aqr->limite_no).lon < limite_no.lon){

            chercher_noeud(aqr->ne,limite_no,limite_se);
        }
    }

    else if(aqr->se != NULL){

        if((aqr->limite_se).lat < limite_se.lat && (aqr->limite_no).lat == limite_no.lat && (aqr->limite_se).lon > limite_se.lon && (aqr->limite_no).lon == limite_no.lon){

            chercher_noeud(aqr->se,limite_no,limite_se);
        } 
    }

    return NULL;
}

void chercher_zone(Un_noeud *aqr, Un_elem **liste){

    if(aqr == NULL){

        return;
    }

    if(*liste == NULL){

        *liste = (Un_elem*) malloc(sizeof(Un_elem));
        (*liste)->truc = aqr->truc;
        (*liste)->suiv = NULL;

        if(aqr->no != NULL){

            chercher_zone(aqr->no,liste);
        }

        if(aqr->so != NULL){

            chercher_zone(aqr->so,liste);
        }

        if(aqr->ne != NULL){

            chercher_zone(aqr->ne,liste);   
        }

        if(aqr->se != NULL){

            chercher_zone(aqr->se,liste);
        }

        return;
    }

    Un_elem *nv_liste = NULL;
    nv_liste = (Un_elem*) malloc(sizeof(Un_elem));

    if(nv_liste == NULL){

        printf("Impossible d'allouer de la mémoire à nv_liste dans la fonction chercher_zone\n");
        return;
    }

    nv_liste->truc = aqr->truc;
    nv_liste->suiv = *liste;
    *liste = nv_liste;

    if(aqr->no != NULL){

        chercher_zone(aqr->no,liste);
    }

    if(aqr->so != NULL){

        chercher_zone(aqr->so,liste);
    }

    if(aqr->ne != NULL){

        chercher_zone(aqr->ne,liste);   
    }

    if(aqr->se != NULL){

        chercher_zone(aqr->se,liste); 
    }

    return;
}

