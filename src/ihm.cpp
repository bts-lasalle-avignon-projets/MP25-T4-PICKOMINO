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
        std::cout << std::endl;
    } while(nombreDeJoueurs < NB_JOUEURS_MIN || nombreDeJoueurs > NB_JOUEURS_MAX);

    return nombreDeJoueurs;
}

void afficherPlateau(Plateau& plateau, Joueur& joueur)
{
    afficherJoueur(joueur);
    afficherBrochette(plateau.pickominos);
    afficherDes(plateau.desObtenus, plateau.desEnJeu);
    afficherDesGardes(plateau.desGardes, NB_DES - plateau.desEnJeu);
}

void afficherPile(Joueur joueurs[], int nbJoueurs)
{
    for(int numeroJoueur = 0; numeroJoueur < nbJoueurs; numeroJoueur++) // Iterer sur chaque joueur
    {
        if(joueurs[numeroJoueur].sommet <= 0) // Si le joueur n'a pas de pile
        {
            std::cout << "La pile du joueur " << numeroJoueur + 1 << " est vide." << std::endl;
        }
        else // Si le joueur a des éléments dans sa pile
        {
            std::cout << "Pile du joueur " << numeroJoueur + 1 << ": ";
            for(int i = 0; i < joueurs[numeroJoueur].sommet;
                i++) // Affiche chaque élément de la pile
            {
                std::cout << joueurs[numeroJoueur].pilePickominos[i] << " ";
            }
            std::cout << std::endl;
        }
    }
}

void afficherJoueur(Joueur& joueur)
{
    std::cout << "Joueur " << joueur.nom << std::endl;
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
    std::cout << std::endl << std::endl;
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


void afficherScoreFinal(int nbjoueurs, Joueur joueurs[])
{
    for(int i = 0; i < nbjoueurs; i++)
    {
        std::cout << "Score final du joueur" << i + 1 << " : " << joueurs[i].scoreFinal
                  << std::endl;
}
void demanderNomJoueur(int nbJoueurs, Joueur joueurs[])
{
    for(int i = 0; i < nbJoueurs; i++)
    {
        std::cout << "Selectionner Pseudo du Joueur " << (i + 1) << " : ";
        std::cin >> joueurs[i].nom;

    }
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
        std::cout << std::endl;
        reponse = tolower(reponse);
    } while(choixValides.find(reponse) == std::string::npos);

    return (reponse == 'o' || reponse == 'O');
}
