#include "dijkstra.h"
#include "animation.h"
#include <stdlib.h>

/**
 * cout : calcule le coût pour rejoindre le noeud suivant depuis le noeud
 * courant. Ce coût est égal à la distance euclidienne entre les deux noeuds,
 * plus le dénivelé entre ces deux noeuds s'il est positif.
 * 
 * Pré-conditions :
 *  - dans_les_bornes(grille, courant)
 *  - dans_les_bornes(grille, suivant)
 * Post-conditions :
 *  - cout > 0, potentiellement infini (INFINITIY)
 *
 * @param grille heightmap contenant les hauteurs
 * @param courant noeud duquel on part pour calculer le coût
 * @param suivant noeud auquel on arrive pour calculer le coût
 * @return coût pour passer de courant à suivant
 */
static float cout(grille_t grille, coord_t courant, coord_t suivant) {
    float cout_total = 0;
    float denivele = get_hauteur(grille, suivant) - get_hauteur(grille, courant);
    if (denivele > 0){
        cout_total = distance_euclidienne(courant, suivant) + denivele;
    } else {
        cout_total = distance_euclidienne(courant, suivant);
    }
    return cout_total;
}

/**
 * construire_chemin_vers - Construit le chemin depuis le noeud de départ donné vers le
 * noeud donné. On passe un chemin en entrée-sortie de la fonction, qui est mis à jour
 * par celle-ci.
 *
 * Ce sous-programme fonctionne récursivement :
 *  1. Si le noeud est égal au noeud de départ, on a fini
 *  2. Sinon, on construit le chemin du départ au noeud précédent (appel récursif)
 *  3. Dans tous les cas, on ajoute le noeud au chemin, avec les caractéristiques associées dans visites
 *
 * @param chemin [in/out] chemin dans lequel enregistrer les étapes depuis le départ vers noeud
 * @param visites [in] liste des noeuds visités créée par l'algorithme de Dijkstra
 * @param source noeud de départ du chemin
 * @param noeud noeud vers lequel on veut construire le chemin depuis le départ
 */
static void construire_chemin_vers(liste_noeud_t* chemin, liste_noeud_t* visites, coord_t source, coord_t noeud){
    if (!memes_coord(source, noeud) && get_x(noeud) >= 0){
        coord_t precedent = precedent_noeud_liste(visites, noeud);
        float cout_noeud = cout_noeud_liste(visites, noeud);
        construire_chemin_vers(chemin, visites, source, precedent);
        inserer_noeud_liste(chemin, noeud, precedent, cout_noeud);
    }
}

float dijkstra(
        grille_t grille, 
        coord_t source, coord_t destination, 
        float seuil,
        liste_noeud_t** chemin
    ) {
    /* Partie D */

    /* D1 */
    liste_noeud_t* A_Visiter = creer_liste();
    liste_noeud_t* Visites = creer_liste();
    inserer_noeud_liste(A_Visiter, source, source, 0.0);

    /* D2 */
    while (!est_vide_liste(A_Visiter)){

        /* D2.1 */
        coord_t noeud_courant = min_noeud_liste(A_Visiter);

        /* D2.2 */
        float cout_nc = cout_noeud_liste(A_Visiter, noeud_courant);
        coord_t precedent_nc = precedent_noeud_liste(A_Visiter, noeud_courant);
        inserer_noeud_liste(Visites, noeud_courant, precedent_nc, cout_nc);

        /* D2.3 */
        supprimer_noeud_liste(A_Visiter, noeud_courant);

        /* D2.4 */
        coord_t* voisins = (coord_t *) malloc(4*sizeof(coord_t));
        int nombre_voisins = (int) get_voisins(grille, noeud_courant, seuil, &voisins);
        for (int i = 0; i < nombre_voisins; i++){
            if (!contient_noeud_liste(Visites, voisins[i])){

                /* D2.4.1 */
                float delta_prime = cout_noeud_liste(Visites, noeud_courant) + cout(grille, noeud_courant, voisins[i]);
                
                /* D2.4.2 */
                float delta = cout_noeud_liste(Visites, voisins[i]);

                /* D2.4.3 */
                if (delta_prime < delta){
                    inserer_noeud_liste(A_Visiter, voisins[i], noeud_courant, delta_prime);
                } 
            }
        }
    }
    /* Partie C */
    construire_chemin_vers(*chemin, Visites, source, destination);
    detruire_liste(&A_Visiter);
    detruire_liste(&Visites);

    return cout_noeud_liste(Visites,destination);
}


