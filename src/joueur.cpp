#include "joueur.h"
#include "donnees.h"
#include "ihm.h"

#ifdef DEBUG_JOUEUR
#include <iostream>
#endif

void creerLesPilesDesJoueurs(Joueur joueurs[], int nbJoueurs)
{
    for(int i = 0; i < nbJoueurs; i++)
    {
        for(int j = 0; j < NB_PICKOMINOS; j++)
        {
            joueurs[i].pileJoueur[j] = 0;
        }
        joueurs[i].compteur = 0;
        joueurs[i].sommet   = 0;
#ifdef DEBUG_JOUEUR
        std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
        std::cout << "Nombre de pile = " << i << std::endl;
#endif
    }
}

int gererLeSommetDesPiles(Joueur& joueur)
{
    if(joueur.compteur > 0)
    {
        joueur.sommet = joueur.pileJoueur[joueur.compteur - 1];
    }
    else
    {
        joueur.sommet = 0;
    }

#ifdef DEBUG_JOUEUR
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "Le sommet du joueur est à: " << joueur.sommet << std::endl;
#endif

    return joueur.sommet;
}
