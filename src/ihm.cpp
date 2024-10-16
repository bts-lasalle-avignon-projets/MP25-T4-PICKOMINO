#include <iostream>
#include "joueur.h"
#include "donnees.h"

int afficherNombreDeJoueur(int nombreDeJoueur)
{
    int nombreDeJoueur;
    std::cout << "Veuillez indiquer le nombre de joueurs ( entre 2 et 7 ): " << std::endl;
    std::cin >> nombreDeJoueur;
    return nombreDeJoueur;
}
