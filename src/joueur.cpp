#include "joueur.h"

#ifdef DEBUG_JOUEUR
#include <iostream>
#endif

#define MIN_JOUEUR 2
#define MAX_JOUEUR 7

int selectionnerNombreDeJoueur()
{
    int nombreDeJoueur;
    std::cout << "Veuillez indiquer le nombre de joueurs ( entre 2 et 7 ): " << std::endl;
    std::cin >> nombreDeJoueur;
    if (nombreDeJoueur >= MIN_JOUEUR && nombreDeJoueur <= MAX_JOUEUR)
    {
        std::cout << "Vous avez selectionné: " << nombreDeJoueur << std::endl;
    }
    else
    {
        std::cout << "Veuillez saisir une valeur correcte." << std::endl;
    }
}
