#include "coord.h"

// TODO : implanter le module coord

coord_t creer_coord(int abscisse, int ordonnee){
    coord_t point;
    point.x = abscisse;
    point.y = ordonnee;
    return point;
}

int get_x(coord_t point){
    return point.x;
}

int get_y(coord_t point){
    return point.y;
}

void set_x(coord_t* point, int x){
    point->x = x;
}

void set_y(coord_t* point, int y){
    point->y = y;
}

bool memes_coord(coord_t p1, coord_t p2){
    return (get_x(p1) == get_x(p2) && get_y(p1) == get_y(p2));
}

coord_t translation(coord_t point, int dx, int dy){
    coord_t point_translate = creer_coord(point.x + dx, point.y + dy);
    return point_translate;
}

float distance_euclidienne(coord_t p1, coord_t p2){
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}