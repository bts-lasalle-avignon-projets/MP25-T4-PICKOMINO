#include "joueur.h"
#include "donnees.h"
#include "ihm.h"

#ifdef DEBUG_JOUEUR
#include <iostream>
#endif

void creerLesPilesDesJoueurs(Joueur joueurs[NB_JOUEURS_MAX], int nbJoueurs)
{
    for(int i = 0; i < nbJoueurs; i++)
    {
        joueurs[i].compteur = 0;
    }
}
