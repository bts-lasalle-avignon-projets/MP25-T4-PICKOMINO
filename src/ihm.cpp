#include "ihm.h"
#include "donnees.h"
#include <iostream>
#include <string>

void afficherPlateau(Plateau& plateau)
{
    afficherDes(plateau.desObtenus, plateau.desEnJeu);
    afficherDesGardes(plateau.desGardes, NB_DES - plateau.desEnJeu);
}

void afficherDes(int desObtenus[], int nbDes)
{
    std::cout << "Lancer des dés : ";
    for(int i = 0; i < nbDes; i++)
    {
        std::cout << (desObtenus[i] == ID_VERS ? "V" : std::to_string(desObtenus[i])) << " ";
    }
    std::cout << std::endl;
}

void afficherDesGardes(int desGardes[], int nbDes)
{
    std::cout << "Dés gardés : ";
    if(nbDes == 0)
    {
        std::cout << "aucun";
    }
    else
    {
        for(int i = 0; i < nbDes; i++)
        {
            if(desGardes[i] != 0)
            {
                std::cout << (desGardes[i] == ID_VERS ? "V" : std::to_string(desGardes[i])) << " ";
            }
        }
    }

    std::cout << std::endl;
}

void afficherScore(int score)
{
    std::cout << "Votre score : " << score << std::endl;
}

void afficherErreurEntree()
{
    std::cout << "Entrée invalide !" << std::endl;
}

void afficherValeurDejaGardee()
{
    std::cout << "Vous avez déjà gardé cette valeur !" << std::endl;
}

void afficherTousDesGardes()
{
    std::cout << "Tous les dés sont gardés ! Aucune relance." << std::endl;
}

void afficherLancerArrete()
{
    std::cout << "Vous ne pouvez plus relancer !" << std::endl;
}

void afficherLancerNul()
{
    std::cout << "Le lancer est nul !" << std::endl;
}

char demanderValeurDe()
{
    char valeur;

    do
    {
        std::cout << "Choisir une valeur à garder : ";
        std::cin >> valeur;
    } while((valeur < '1' || valeur > '5') && valeur != 'V' && valeur != 'v');

    return valeur;
}

bool demander(const std::string& message)
{
    char              reponse;
    const std::string choixValides = "on";

    do
    {
        std::cout << "Voulez-vous " << message << " ? (oO/nN) ";
        std::cin >> reponse;
        reponse = tolower(reponse);
    } while(choixValides.find(reponse) == std::string::npos);

    return (reponse == 'o' || reponse == 'O');
}
