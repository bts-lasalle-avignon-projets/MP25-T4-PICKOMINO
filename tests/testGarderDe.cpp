#include "doctest.h"
#include "plateau.h"
#include "ihm.h"
#include <sstream>
#include <iostream>

// Simuler les flux d'entrée et de sortie
std::istringstream simulatedInput;
std::ostringstream simulatedOutput;

// Fonction pour simuler l'entrée d'un entier
void simulerEntree(int nombreSimule)
{
    simulatedInput.str(""); // Réinitialise le flux simulé
    simulatedInput.clear(); // Efface l'état du flux
    simulatedInput.str(
      std::to_string(nombreSimule)); // Convertir l'entier en chaîne et réinjecter dans le flux
    std::cin.rdbuf(simulatedInput.rdbuf()); // Rediriger std::cin vers simulatedInput
}

TEST_CASE("Garder un dé valide")
{
    Plateau plateau;
    plateau.desEnJeu      = 5;
    plateau.desObtenus[0] = 1;
    plateau.desObtenus[1] = 2;
    plateau.desObtenus[2] = 3;
    plateau.desObtenus[3] = 4;
    plateau.desObtenus[4] = 5;

    for(int i = 0; i < NB_DES; i++)
    {
        plateau.desGardes[i] = 0; // Aucun dé gardé au départ
    }

    simulerEntree(3); // Simuler la saisie de l'entier 3

    // Essayer de garder la valeur 3, présente parmi les dés obtenus
    CHECK(garderDes(plateau) == true);
    CHECK(plateau.desGardes[0] == 3); // Le premier dé gardé est la valeur 3
    CHECK(plateau.desEnJeu == 4);     // Un dé a été retiré des dés en jeu
}
