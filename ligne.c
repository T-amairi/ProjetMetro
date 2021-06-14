#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ligne.h"
//#include "aqrtopo.h"

Une_ligne* lire_lignes(char* nom_fichier){
	
	FILE* metro = NULL;
	metro = fopen(nom_fichier,"rw");
	
	if (metro == NULL){

		printf("Erreur d'ouverture ! \n");
		exit(EXIT_FAILURE);
	}

	Une_ligne *tete = NULL;
    tete = (Une_ligne*) malloc(sizeof(Une_ligne));

    if(tete == NULL){

        printf("Impossible d'allouer de la mémoire à tete dans la fonction lire_lignes dans le programme exo3.c\n");
		fclose(metro);
        return NULL;
    }

	char *ligne = NULL;
	char *p_line;
    size_t longueur = 0;
	Une_ligne *temp_tete = tete;
	Une_ligne *temp = tete;

	while (getline(&ligne, &longueur, metro) != -1){

		temp = tete;

		p_line = NULL;

		p_line = strtok(ligne,",");

		tete->code = NULL;
		tete->code = (char*) malloc((strlen(p_line) + 1)*sizeof(char));

		if(tete->code == NULL){

			printf("Impossible d'allouer de la mémoire à tete->nom dans la fonction lire_lignes dans le programme exo3.c\n");
			fclose(metro);
        	return NULL;
		}

		strcpy(tete->code,p_line);

		p_line = strtok(NULL,",");

		tete->vitesse = (float) atof(p_line);

		p_line = strtok(NULL,",");

		tete->intervalle = (float) atof(p_line);

		p_line = strtok(NULL,",");

		tete->color = NULL;
		tete->color = (char*) malloc((strlen(p_line) + 1)*sizeof(char));

		if(tete->color == NULL){

			printf("Impossible d'allouer de la mémoire à tete->couleur_hexa dans la fonction lire_lignes dans le programme exo3.c\n");
			fclose(metro);
        	return NULL;
		}

		strcpy(tete->color,p_line);

		tete->suiv = NULL;

		tete->suiv = (Une_ligne*) malloc(sizeof(Une_ligne));

    	if(tete->suiv == NULL){

			printf("Impossible d'allouer de la mémoire à tete->suivant dans la fonction lire_lignes dans le programme exo3.c\n");
			fclose(metro);
			return NULL;
    	}

        tete = tete->suiv;
	}

	free(tete);
	free(ligne);
	temp->suiv = NULL;
	fclose(metro);
	return temp_tete;
}

void afficher_lignes(Une_ligne *ligne){

   	while (ligne != NULL){

        printf("%s,%f,%f,%s\n",ligne->code,ligne->vitesse,ligne->intervalle,ligne->color);
        ligne = ligne->suiv;
    }
    	
    return;
}
	
Une_ligne *chercher_ligne(Une_ligne *ligne, char *code){
	
	while (ligne != NULL){

		if (strcmp(ligne->code,code) == 0){

			//printf("Ligne trouvée : %s,%f,%f,%s\n",ligne->code,ligne->vitesse,ligne->intervalle,ligne->color);
			return ligne;	
		}
		
		ligne = ligne->suiv;		
	}

	printf("La ligne désignée n'existe pas\n");
	return NULL;
}	
			
void detruire_lignes(Une_ligne *ligne){

	Une_ligne* temp = ligne;
	
	while(temp != NULL){

		ligne = ligne->suiv;
		free(temp->code);
		free(temp->color);
		free(temp);
		temp = NULL;
		temp = ligne;
	}

	return;
}



