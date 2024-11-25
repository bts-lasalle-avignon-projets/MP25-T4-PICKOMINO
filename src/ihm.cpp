#include "ihm.h"
#include "donnees.h"

#include <iostream>

int saisirNombreDeJoueurs()
{
    int nombreDeJoueurs;

    do
    {
        std::cout << "Veuillez indiquer le nombre de joueurs (entre " << NB_JOUEURS_MIN << " et "
                  << NB_JOUEURS_MAX << ") : ";
        std::cin >> nombreDeJoueurs;
    } while(nombreDeJoueurs < NB_JOUEURS_MIN || nombreDeJoueurs > NB_JOUEURS_MAX);

    return nombreDeJoueurs;
}

void afficherPlateau(Plateau& plateau)
{
    afficherJoueur(plateau.numeroJoueur);
    // @todo afficher la pile du joueur et le nombre de vers obtenus
    afficherBrochette(plateau.pickominos);
    afficherDes(plateau.desObtenus, plateau.desEnJeu);
    afficherDesGardes(plateau.desGardes, NB_DES - plateau.desEnJeu);
}

void afficherJoueur(int numeroJoueur)
{
    std::cout << "Joueur " << (numeroJoueur + 1) << std::endl;
}

void afficherBrochette(EtatPickomino pickominos[NB_PICKOMINOS])
{
    std::cout << "Brochette :";
    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        if(pickominos[i] == EtatPickomino::DISPONIBLE)
        {
            std::cout << " " << (i + VALEUR_PICKOMINO_MIN);
        }
        else if(pickominos[i] == EtatPickomino::RETOURNE)
        {
            std::cout << " X";
        }
    }
    std::cout << std::endl;
}

void afficherDes(int desObtenus[NB_DES], int nbDes)
{
    std::cout << "Lancer des dés : ";
    for(int i = 0; i < nbDes; i++)
    {
        std::cout << (desObtenus[i] == ID_VERS ? "V" : std::to_string(desObtenus[i])) << " ";
    }
    std::cout << std::endl;
}

void afficherDesGardes(int desGardes[NB_DES], int nbDes)
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

void afficherPioche(int pickomino)
{
    std::cout << "Vous piochez : " << pickomino << std::endl << std::endl;
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
    std::cout << "Le lancer est nul !" << std::endl << std::endl;
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
