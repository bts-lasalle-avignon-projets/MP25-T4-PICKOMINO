#include "doctest.h"
#include "plateau.h"
#include "ihm.h"
#include <sstream>
#include <iostream>

// Simuler les flux d'entrée et de sortie
std::istringstream simulatedInput;
std::ostringstream simulatedOutput;

// Fonction pour simuler l'entrée d'un entier
void simulerEntree(const std::string& entreeSimulee)
{
    simulatedInput.str("");                 // Réinitialise le flux simulé
    simulatedInput.clear();                 // Efface l'état du flux
    simulatedInput.str(entreeSimulee);      // Injecte la chaîne simulée dans le flux
    std::cin.rdbuf(simulatedInput.rdbuf()); // Redirige std::cin vers simulatedInput
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

    simulerEntree("3\n"); // Simuler la saisie de l'entier 3

    // Essayer de garder la valeur 3, présente parmi les dés obtenus
    CHECK(garderDes(plateau) == true);
    CHECK(plateau.desGardes[0] == 3); // Le premier dé gardé est la valeur 3
    CHECK(plateau.desEnJeu == 4);     // Un dé a été retiré des dés en jeu
}

TEST_CASE("Garder un dé incorrecte")
{
    // Initialisation
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

    int valeur = 6; // 6 n'est pas dans desObtenus

    bool resultat = estPasDansLesDesLances(plateau, valeur);

    // Vérifications
    // La fonction ne devrait pas avoir réussi à garder un dé
    CHECK(resultat == true);

    // Aucune modification du plateau ne doit avoir lieu
    CHECK(plateau.desEnJeu == 5); // Les dés en jeu restent inchangés
    for(int i = 0; i < NB_DES; i++)
    {
        CHECK(plateau.desGardes[i] == 0); // Aucun dé gardé
    }
}

TEST_CASE("Le dé est déjà garder")
{
    Plateau plateau;
    plateau.desEnJeu     = 5;
    plateau.desGardes[0] = 1;
    plateau.desGardes[1] = 2;
    plateau.desGardes[2] = 3;

    int valeur = 3;

    bool resultat = estDejaGarde(valeur, plateau.desGardes, NB_DES - plateau.desEnJeu);
    CHECK(resultat == true);

    // Aucune modification du plateau ne doit avoir lieu
    CHECK(plateau.desEnJeu == 5); // Les dés en jeu restent inchangés
    for(int i = 0; i < NB_DES - plateau.desEnJeu; i++)
    {
        CHECK(plateau.desGardes[i] == i + 1); // Aucun dé gardé suplémentaire ou modifier
    }
}

TEST_CASE("Garder un ver :")
{
    Plateau plateau;
    plateau.desEnJeu      = 8;
    plateau.desObtenus[0] = 1;
    plateau.desObtenus[1] = 2;
    plateau.desObtenus[2] = 3;
    plateau.desObtenus[3] = 4;
    plateau.desObtenus[4] = 5;
    plateau.desObtenus[5] = 5;
    plateau.desObtenus[6] = ID_VERS;
    plateau.desObtenus[7] = 5;
    for(int i = 0; i < NB_DES; i++)
    {
        plateau.desGardes[i] = 0; // Aucun dé gardé au départ
    }

    simulerEntree("v\n");

    bool resultat = garderDes(plateau);
    CHECK(resultat == true);
    CHECK(plateau.desEnJeu == 7);
    CHECK(plateau.desGardes[0] == ID_VERS);
    for(int i = 1; i < NB_DES; i++)
    {
        CHECK(plateau.desGardes[i] == 0); // Aucun dé gardé supplémentaire
    }
}
