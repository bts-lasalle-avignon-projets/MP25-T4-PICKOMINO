#ifndef JOUEUR_H
#define JOUEUR_H
#include "donnees.h"

#define DEBUG_JOUEUR

struct Joueur
{
    int pileJoueur[NB_PICKOMINOS];
    int compteur;
    int sommet;
};

void creerLesPilesDesJoueurs(Joueur joueurs[NB_JOUEURS_MAX], int nbJoueurs);
int  gererLeSommetDesPiles(Joueur& joueur);
void ajouterPickominoAPile(Joueur& joueur, int pickomino);

#endif