#define _GNU_SOURCE
#include "grille.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

grille_t creer_grille(int largeur, int profondeur){
    float * tableau_hauteur = (float *) calloc(largeur * profondeur, sizeof(float));
    grille_t grille;
    grille.largeur = largeur;
    grille.profondeur = profondeur;
    grille.tableau_hauteur = tableau_hauteur;
    return grille;
}

void detruire_grille(grille_t grille){
    free(grille.tableau_hauteur);
}

bool dans_les_bornes(grille_t grille, coord_t position){
    int x = get_x(position);
    int y = get_y(position);
    return (0 <= x && 0 <= y && x < grille.largeur && y < grille.profondeur);
}

int get_largeur(grille_t grille){
    return grille.largeur;
}

int get_profondeur(grille_t grille){
    return grille.profondeur;
}

coord_t inferieur_gauche(grille_t grille){
    return creer_coord(0,grille.profondeur - 1);
}

coord_t superieur_droit(grille_t grille){
    return creer_coord(grille.largeur - 1, 0);
}

/**
 * coord_lin : fonction statique (de module) qui transforme des coordonnées
 * cartésiennes dans la grille en coordonnées "linéaires" permettant d'adresser
 * le tableau contenu dans la grille.
 *
 * @param grille grille avec le bon système de coordonnées
 * @param position position dans la grille en coordonnées cartésiennes entières
 * @return position dans le tableau en coordonnée linéaire
 */
static size_t coord_lin(grille_t grille, coord_t position) {
    int i = get_x(position);
    int j = get_y(position);
    return (size_t) (j*grille.largeur+i);
}

void set_hauteur(grille_t grille, coord_t position, float hauteur){
    grille.tableau_hauteur[coord_lin(grille,position)] = hauteur;
}

float get_hauteur(grille_t grille, coord_t position){
    return grille.tableau_hauteur[coord_lin(grille,position)];
}

size_t get_voisins(grille_t grille, coord_t position, float seuil, coord_t** voisins){
    coord_t * liste = (coord_t *) malloc(4*sizeof(coord_t));
    int tab_x[4] = {-1,0,1,0};
    int tab_y[4] = {0,-1,0,1};
    size_t nombre_voisins = 0;
    float hauteur = get_hauteur(grille,position);

    for (int i = 0; i < 4; i++){
        coord_t voisin = translation(position,tab_x[i],tab_y[i]);

        if (dans_les_bornes(grille,voisin)){
            float hauteur_voisin = get_hauteur(grille,voisin);
            
            if ((hauteur_voisin - hauteur)*(hauteur_voisin - hauteur) <= seuil*seuil){
                liste[nombre_voisins] = voisin;
                nombre_voisins++;
            }
        }
    }
    *voisins = liste;
    return nombre_voisins;
}










