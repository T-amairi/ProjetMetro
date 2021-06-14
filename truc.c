#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "truc.h"

Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv){

    Un_truc *truc = NULL;
    truc = (Un_truc*) malloc(sizeof(Un_truc));

    if(truc == NULL){

        printf("Problème d'allocation à la fonction creer_truc\n");
        return NULL;
    }

    truc->coord = coord;
    truc->type = type;
    truc->data = data;
    truc->user_val = uv;

    return truc;
}

void detruire_truc(Un_truc *truc){

    if(truc == NULL){

        return;
    }

    if(truc->type == 1){

        free(truc);
        return;
    }

    free(((truc->data).sta).nom);

    free(((truc->data).sta).tab_con);
    
    free(truc);

    return;
}


