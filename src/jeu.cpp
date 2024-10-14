#include "jeu.h"
#include "ihm.h"

#include <ctime>   /* time()*/
#include <cstdlib> /* srand() et rand() */

#define NB_FACES 6

#ifdef DEBUG_JEU
#include <iostream>
#endif

int lancerDes(int desObtenue[NB_DES], int desEnJeu)
{
    srand(time(NULL));

#ifdef DEBUG_JEU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "desEnJeu = " << desEnJeu << std::endl;
#endif

    for(size_t i = 0; i < desEnJeu; i++)
    {
        int valeur    = (rand() % NB_FACES) + 1;
        desObtenue[i] = valeur;
    }

    return 0;
}

// joueur
int demanderValeur()
{
    char valeur;
    std::cout << "Choisir une valeur a garder : ";
    std::cin >> valeur;
    return valeur;
}

// nom pas bon
int convertirValeur(char valeur)
{
    if(valeur == 'V' || valeur == 'v')
        return 6;
    else if(valeur >= '1' && valeur <= '5')
        return valeur - '0';
    return -1;
}

bool rechercherEtGarder(int desGarder[NB_DES],
                        int desObtenue[NB_DES],
                        int valeurGardee,
                        int desEnJeu)
{
    for(size_t i = 0; i < NB_DES; i++)
    {
        if(desGarder[i] == valeurGardee)
        {
            return false;
        }
    }

    for(size_t i = 0; i < desEnJeu; i++)
    {
        if(desObtenue[i] == valeurGardee)
        {
            for(size_t j = 0; j < NB_DES; j++)
            {
                if(desGarder[j] == 0)
                {
                    desGarder[j] = valeurGardee;
                    break;
                }
            }
        }
    }
    return true;
}

void garderDES(int desGarder[NB_DES], int desObtenue[NB_DES], int desEnJeu)
{
    int valeurGardee = convertirValeur(demanderValeur());
    if(valeurGardee == -1)
    {
        std::cout << "Entree invalide." << std::endl;
        return;
    }

    int nombreAGarder;
    std::cout << "Combien de " << (valeurGardee == 6 ? "V" : std::to_string(valeurGardee))
              << " voulez-vous garder ? ";
    std::cin >> nombreAGarder;

    for(int i = 0; i < nombreAGarder; i++)
    {
        if(!rechercherEtGarder(desGarder, desObtenue, valeurGardee, desEnJeu))
        {
            std::cout << "Vous ne pouvez pas garder plus de dés de cette valeur." << std::endl;
            break;
        }
    }

    std::cout << "Vous avez garde : ";
    for(size_t i = 0; i < NB_DES; i++)
        if(desGarder[i] != 0)
            std::cout << (desGarder[i] == 6 ? "V" : std::to_string(desGarder[i])) << " ";
    std::cout << std::endl << std::endl;
}

bool verifierNombreDesGarder(int desGarder[NB_DES], int& desEnJeu)
{
    int compteurDesGardes = 0;
    for(size_t i = 0; i < NB_DES; i++)
    {
        if(desGarder[i] != 0)
        {
            compteurDesGardes++;
        }
    }
    if(compteurDesGardes == NB_DES)
    {
        std::cout << "Tous les dés sont gardés. Aucune relance." << std::endl;
        return false;
    }
    else
    {
        desEnJeu = NB_DES - compteurDesGardes;
        return true;
    }
}

int jouerJeu()
{
    int desObtenue[NB_DES];
    int desGarder[NB_DES] = { 0 };
    int desEnJeu          = NB_DES;
    while(verifierNombreDesGarder(desGarder, desEnJeu))
    {
        lancerDes(desObtenue, desEnJeu);
        afficherDes(desObtenue, desEnJeu);
        garderDES(desGarder, desObtenue, desEnJeu);
    }
    // score();
}
