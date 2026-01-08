#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>

struct liste_noeud_t{
    coord_t noeud;
    float dist;
    coord_t prec;
    struct liste_noeud_t * cellule_suivante;
};

liste_noeud_t* creer_liste(){
    liste_noeud_t* sentinelle = (liste_noeud_t *) malloc(sizeof(liste_noeud_t));
    sentinelle->cellule_suivante = NULL;
    return sentinelle;
}

void detruire_liste(liste_noeud_t** liste_ptr){
    if (*liste_ptr != NULL){
        detruire_liste(&((*liste_ptr)->cellule_suivante));
        free(*liste_ptr);
        *liste_ptr = NULL;
    }
}

bool est_vide_liste(const liste_noeud_t* liste){
    return (liste->cellule_suivante == NULL);
}

bool contient_noeud_liste(const liste_noeud_t* liste, coord_t noeud){
    if (est_vide_liste(liste)){
        return false;
    } else if (memes_coord(liste->noeud,noeud)){
        return true;
    } else {
        return contient_noeud_liste(liste->cellule_suivante,noeud);
    }
}

bool contient_arrete_liste(const liste_noeud_t* liste, coord_t noeud, coord_t destination){
    if (est_vide_liste(liste)){
        return false;
    } else if (memes_coord(liste->noeud,destination) && memes_coord(liste->prec,noeud)){
        return true;
    } else {
        return contient_arrete_liste(liste->cellule_suivante,noeud,destination);
    }
}

float cout_noeud_liste(const liste_noeud_t* liste, coord_t noeud){
    if (est_vide_liste(liste)){
        return INFINITY;
    } else if (memes_coord(liste->noeud,noeud)){
        return liste->dist;
    } else {
        return cout_noeud_liste(liste->cellule_suivante, noeud);
    }
}

coord_t precedent_noeud_liste(const liste_noeud_t* liste, coord_t noeud){
    if (est_vide_liste(liste)){
        return creer_coord(-1,-1);
    } else if (memes_coord(liste->noeud,noeud)){
        return liste->prec;
    } else {
        return precedent_noeud_liste(liste->cellule_suivante, noeud);
    }
}

coord_t min_noeud_liste(const liste_noeud_t* liste){
    if (est_vide_liste(liste)){
        return creer_coord(-1,-1);
    }
    else if (est_vide_liste(liste->cellule_suivante)){
        return liste->noeud;
    } else {
        coord_t noeud_min_suiv = min_noeud_liste(liste->cellule_suivante);
        if (cout_noeud_liste(liste->cellule_suivante, noeud_min_suiv) > liste->dist){
            return liste->noeud;
        } else {
            return noeud_min_suiv;
        }
    }
}

void inserer_noeud_liste(liste_noeud_t* liste, coord_t noeud, coord_t precedent, float cout){
    if (est_vide_liste(liste)){
        liste->noeud = noeud;
        liste->prec = precedent;
        liste->dist = cout;
        liste->cellule_suivante = creer_liste();
    } else if (memes_coord(liste->noeud, noeud)){
        liste->prec = precedent;
        liste->dist = cout;
    } else {
        inserer_noeud_liste(liste->cellule_suivante, noeud, precedent, cout);
    }
}

void supprimer_noeud_liste(liste_noeud_t* liste, coord_t noeud){
    if (!est_vide_liste(liste)){
        if (memes_coord(liste->noeud,noeud)){
            liste_noeud_t* tmp = liste->cellule_suivante;
            liste->noeud = tmp->noeud;
            liste->dist = tmp->dist;
            liste->prec = tmp->prec;
            liste->cellule_suivante = tmp->cellule_suivante;
            tmp->cellule_suivante = NULL;
            detruire_liste(&tmp);
        } else {
            supprimer_noeud_liste(liste->cellule_suivante, noeud);
        }
    }
}