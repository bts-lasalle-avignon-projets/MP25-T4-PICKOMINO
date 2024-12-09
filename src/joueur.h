#ifndef JOUEUR_H
#define JOUEUR_H

#include "donnees.h"

//#define DEBUG_JOUEUR

struct Joueur
{
    int pilePickominos[NB_PICKOMINOS];
    int sommet;
};

void creerLesPilesDesJoueurs(Joueur joueurs[NB_JOUEURS_MAX], int nbJoueurs);

#endif