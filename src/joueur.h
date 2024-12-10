#ifndef JOUEUR_H
#define JOUEUR_H

#include "donnees.h"

//#define DEBUG_JOUEUR

struct Joueur
{
    int pileJoueur[NB_PICKOMINOS];
    int compteur;
    int sommet;
    int scoreFinal;
};

void creerLesPilesDesJoueurs(Joueur joueurs[NB_JOUEURS_MAX], int nbJoueurs);
int  ajouterSommet(Joueur& joueur);
int  retirerSommet(Joueur& joueur);

#endif