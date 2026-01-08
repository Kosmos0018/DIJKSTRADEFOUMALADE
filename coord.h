#ifndef COORD_H
#define COORD_H

#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>

/**
 * Type coord_t représentant une heightmap, caractérisé par
 *  - une abscisse (entière)
 *  - une ordonnée (entière)
 */
typedef struct coord_t {
    int x;
    int y;
} coord_t;

// TODO : typedef pour éviter d'écrire "struct coord_t" partout


/**
 * creer_coord : crée un coord_t à partir d'une abscisse et ordonnée données.
 *
 * Pré-conditions : 
 * Post-conditions : 
 *          
 * @param abscisse largeur de la grille (taille selon l'axe des X)
 * @param ordonnee profondeur de la grille (taille selon l'axe des Y)
 * @return point nouvellement créé
 */
coord_t creer_coord(int abscisse, int ordonnee);

/**
 * get_x : récupère l'abscisse du point choisi.
 *
 * Pré-conditions : point créé avec creer_coord
 * Post-conditions : 
 *
 * @param point point dont on veut l'abscisse
 * @return abscisse du point
 */
int get_x(coord_t point);

/**
 * get_y : récupère l'ordonnée du point choisi.
 *
 * Pré-conditions : point créé avec creer_coord
 * Post-conditions : 
 *
 * @param point point dont on veut l'ordonnée
 * @return ordonnée du point
 */
int get_y(coord_t point);

/**
 * set_x : modifie l'abscisse du point choisi.
 *
 * Pré-conditions : point créé avec creer_coord
 * Post-conditions : x = get_x(point)
 *
 * @param point point dont on veut modifier l'abscisse
 * @param x nouvelle abscisse du point
 */
void set_x(coord_t* point, int x);

/**
 * set_y : modifie l'ordonnée du point choisi.
 *
 * Pré-conditions : point créé avec creer_coord
 * Post-conditions : y = get_y(point)
 *
 * @param point point dont on veut modifier l'ordonnée
 * @param x nouvelle ordonnée du point
 */
void set_y(coord_t* point, int y);

/**
 * memes_coord : test si deux points sont identiques.
 *
 * Pré-conditions : p1 et p2 points créés avec creer_coord
 * Post-conditions : Vrai => get_x(p1) = get_x(p2) et get_y(p1) = get_y(p2) 
 *
 * @param p1 point que l'on veut comparer
 * @param p2 point que l'on veut comparer
 * @return true ssi p1 est identique à p2
 */
bool memes_coord(coord_t p1, coord_t p2);

/**
 * translation : crée le point translaté de point par la translation d'abscisse dx et d'ordonnée dy.
 *
 * Pré-conditions : point point créé avec creer_coord
 * Post-conditions : get_x(point_translate) = get_x(point) + dx et get_y(point_translate) = get_y(point) + dy
 *
 * @param point point que l'on veut translater
 * @param dx translation d'abscisse
 * @param dy translation d'ordonnée
 * @return point_translate
 */
coord_t translation(coord_t point, int dx, int dy);

/**
 * distance_euclidienne : calcule la distance entre deux points.
 *
 * Pré-conditions : p1 et p2 points créés avec creer_coord
 * Post-conditions : distance = sqrt((get_x(p1) - get_x(p2))**2 + (get_y(p1) - get_y(p2))**2)
 *
 * @param p1 point dont on veut la distance avec p2
 * @param p2 point dont on veut la distance avec p1
 * @return distance entre p1 et p2
 */
float distance_euclidienne(coord_t p1, coord_t p2);

#endif