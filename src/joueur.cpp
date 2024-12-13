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
        joueurs[i].sommet = 0;

#ifdef DEBUG_JOUEUR
        std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
        std::cout << "Nombre de pile = " << i << std::endl;
#endif
        for(int j = 0; j < NB_PICKOMINOS; j++)
        {
            joueurs[i].pilePickominos[j] = VALEUR_DE_INCONNUE;
        }
    }
}