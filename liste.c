#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "abr.h"

Un_elem* inserer_liste_trie(Un_elem* liste, Un_truc* truc){

    Un_elem* nv_element = (Un_elem*) malloc(sizeof(Un_elem));

    nv_element->truc = truc;
    nv_element->suiv = NULL;
    
    if(liste == NULL){

	    return nv_element;
    }

	if(truc->user_val <= liste->truc->user_val){

		nv_element->suiv = liste;
		return nv_element;
	}

	Un_elem* temp = liste;

	while(temp->suiv != NULL){

		if(temp->suiv->truc->user_val > truc->user_val){

			nv_element->suiv = temp->suiv;
			temp->suiv = nv_element;
			return liste;
		}

		temp = temp->suiv;
	}

	temp->suiv = nv_element;

	return liste;
}

void ecrire_liste( FILE *flux, Un_elem *liste){

    if(flux == NULL){

        printf("Impossible d'ouvrir le fichier dans la fonction ecrire_liste dans le programme liste.c\n");
        return;
    }

    while(liste != NULL){

        fprintf(flux,"%f,%f,%s",(liste->truc->coord).lon,(liste->truc->coord).lat,((liste->truc->data).sta).nom);
        liste = liste->suiv;
    }

    fclose(flux);
    return;
}

void detruire_liste(Un_elem *liste){

    Un_elem *temp = liste;
    
    while(liste != NULL){

        liste = liste->suiv;
        free(temp);
        temp = NULL;
        temp = liste;    
    }

    return;
}

void detruire_liste_et_truc(Un_elem *liste){

    Un_elem *temp = liste;
    
    while(liste != NULL){

        liste = liste->suiv;
        detruire_truc(temp->truc);
        free(temp);
        temp = NULL;
        temp = liste;   
    }

    return;
}

Un_elem *lire_stations( char *nom_fichier){

    FILE *fichier = NULL;

    fichier = fopen(nom_fichier,"rw");

    if(fichier == NULL){

        printf("Impossible d'ouvrir le fichier dans la fonction lire_stations dans le programme liste.c\n");
        return NULL;
    }

    Un_elem *tete = NULL;
    tete = (Un_elem*) malloc(sizeof(Un_elem));

    if(tete == NULL){

        printf("Impossible d'allouer de la mémoire à tete dans la fonction lire_stations dans le programme liste.c\n");
        fclose(fichier);
        return NULL;
    }

    tete->truc = NULL;
    tete->truc = (Un_truc*) malloc(sizeof(Un_truc));

    if(tete->truc == NULL){

        printf("Impossible d'allouer de la mémoire à tete->truc dans la fonction lire_stations dans le programme liste.c\n");
        fclose(fichier);
        return NULL;
    }

    tete->truc->type = 0;
    tete->truc->user_val = 0.0;
    ((tete->truc->data).sta).nb_con = 0;
    ((tete->truc->data).sta).tab_con = NULL;
    ((tete->truc->data).sta).nom = NULL;
    ((tete->truc->data).sta).con_pcc = NULL;

    tete->suiv = NULL;

	char *ligne = NULL;
	char *p_line;
    size_t longueur = 0;
	Un_elem *temp_tete = tete;
    Un_elem *temp = tete;

	while (getline(&ligne, &longueur, fichier) != -1){

        temp = tete;

		p_line = NULL;

		p_line = strtok(ligne,";");

		((tete->truc->data).sta).nom = NULL;
		((tete->truc->data).sta).nom = (char*) malloc((strlen(p_line) + 1)*sizeof(char));

		if(((tete->truc->data).sta).nom == NULL){

			printf("Impossible d'allouer de la mémoire à tete->data->nom dans la fonction lire_stations dans le programme liste.c\n");
			fclose(fichier);
        	return NULL;
		}

		strcpy(((tete->truc->data).sta).nom,p_line);

        p_line = strtok(NULL,";");

		(tete->truc->coord).lat = (float) atof(p_line);

		p_line = strtok(NULL,";");

        (tete->truc->coord).lon = (float) atof(p_line);

        tete->suiv = NULL;

		tete->suiv = (Un_elem*) malloc(sizeof(Un_elem));

    	if(tete->suiv == NULL){

			printf("Impossible d'allouer de la mémoire à tete->suiv dans la fonction lire_stations dans le programme liste.c\n");
			fclose(fichier);
			return NULL;
    	}

        tete->suiv->truc = NULL;
        tete->suiv->truc = (Un_truc*) malloc(sizeof(Un_truc));

        if(tete->suiv->truc == NULL){

            printf("Impossible d'allouer de la mémoire à tete->suiv->truc dans la fonction lire_stations dans le programme liste.c\n");
            fclose(fichier);
            return NULL;
        }

        tete = tete->suiv;
        tete->truc->type = 0;
        tete->truc->user_val = 0.0;
        ((tete->truc->data).sta).nb_con = 0;
        ((tete->truc->data).sta).tab_con = NULL;
        ((tete->truc->data).sta).nom = NULL;
        ((tete->truc->data).sta).con_pcc = NULL;
	}

    free(tete->truc);
    free(tete);
    free(ligne);
    temp->suiv = NULL;
    fclose(fichier);
    return temp_tete;
}

void limites_zone(Un_elem *liste, Une_coord *limite_no, Une_coord *limite_se){

    float lon_min = 0;
    float lon_max = 0;
    float lat_min = 0;
    float lat_max = 0;

    while(liste != NULL){

        if((liste->truc->coord).lon > lon_max){

            lon_max = (liste->truc->coord).lon;
        }

        if((liste->truc->coord).lon < lon_min){

            lon_min = (liste->truc->coord).lon;
        }

        if((liste->truc->coord).lat > lat_max){

            lat_max = (liste->truc->coord).lat;
        }

        if((liste->truc->coord).lat < lat_min){

            lat_min = (liste->truc->coord).lat;
        }

        liste = liste->suiv;
    }

    limite_no->lon = lon_min;
    limite_no->lat = lat_max;

    limite_se->lon = lon_max;
    limite_se->lat = lat_min;

    return;
}

Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc){

    Un_elem *nv_tete = NULL;
    nv_tete = (Un_elem*) malloc(sizeof(Un_elem));

    if(nv_tete == NULL){

        printf("Impossible d'allouer de la mémoire à nv_tete dans la fonction inserer_deb_liste dans le programme liste.c\n");
        return NULL;
    }

    nv_tete->truc = truc;
    nv_tete->suiv = liste;

    return nv_tete;
}

