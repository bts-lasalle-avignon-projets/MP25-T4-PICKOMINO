#ifndef JOUEUR_H
#define JOUEUR_H

#include "donnees.h"

// #define DEBUG_JOUEUR
#include "string"

struct Joueur
{
    bool        estIA;
    int         score;
    int         scoreFinal;
    int         pilePickominos[NB_PICKOMINOS];
    int         sommet;
    std::string nom;
};

void creerLesPilesDesJoueurs(Joueur joueurs[NB_JOUEURS_MAX], int nbJoueurs);
bool estJoueurIA(const Joueur& joueur);

#endif