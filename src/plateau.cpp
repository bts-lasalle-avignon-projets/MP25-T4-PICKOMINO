#include "plateau.h"
#include "ihm.h"
#include "donnees.h"
#include <ctime>     // pour time
#include <cstdlib>   // pour srand et rand
#include <algorithm> // pour any_of

#ifdef DEBUG_PLATEAU
#include <iostream>
#endif

int lancerDes(int desObtenue[NB_DES], int desEnJeu)
{
    srand(time(NULL));
#ifdef DEBUG_PLATEAU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "desEnJeu = " << desEnJeu << std::endl;
#endif

    for(int i = 0; i < desEnJeu; i++)
    {
        int valeur    = (rand() % NB_FACES) + 1;
        desObtenue[i] = valeur;
    }
    return 0;
}

int convertirIdVers(char valeur)
{
    if(valeur == 'V' || valeur == 'v')
        return ID_VERS;
    else if(valeur >= '1' && valeur <= '5')
        return valeur - '0';
    return -1;
}

bool contientV(int desGarder[NB_DES])
{
    for(int i = 0; i < NB_DES; i++)
    {
        if(desGarder[i] == ID_VERS)
            return true;
    }
    return false;
}

bool sontEgal(int des1[NB_DES], int des2[NB_DES])
{
    for(size_t i = 0; i < NB_DES; i++)
    {
        if(des1[i] != des2[i])
            return false;
    }
    return true;
}

bool peutRelancer(int desObtenue[NB_DES], int desGarder[NB_DES], int desEnJeu)
{
    if(sontEgal(desObtenue, desGarder))
        return false;

    for(int i = 0; i < desEnJeu; i++)
    {
        bool dejaGardee = std::any_of(desGarder, desGarder + NB_DES, [desObtenue, i](int v) {
            return v == desObtenue[i];
        });
        if(!dejaGardee)
            return true;
    }
    return false;
}

bool rechercherEtGarder(int desGarder[NB_DES],
                        int desObtenue[NB_DES],
                        int valeurGardee,
                        int desEnJeu)
{
    bool gardeEffectuee = false;
    for(int i = 0; i < desEnJeu; i++)
    {
        if(desObtenue[i] == valeurGardee)
        {
            for(size_t j = 0; j < NB_DES; j++)
            {
                if(desGarder[j] == 0)
                {
                    desGarder[j]   = valeurGardee;
                    gardeEffectuee = true;
                    break;
                }
            }
        }
    }
    return gardeEffectuee;
}

void garderDES(int desGarder[NB_DES], int desObtenue[NB_DES], int desEnJeu)
{
    int  valeurGardee;
    bool dejaGardee;
    do
    {
        valeurGardee = convertirIdVers(demanderValeur());
        if(valeurGardee == -1)
        {
            afficherErreurEntree();
            return;
        }

        dejaGardee = std::any_of(desGarder, desGarder + NB_DES, [valeurGardee](int v) {
            return v == valeurGardee;
        });
        if(dejaGardee)
            afficherValeurDejaGardee();

    } while(dejaGardee);

    rechercherEtGarder(desGarder, desObtenue, valeurGardee, desEnJeu);
    afficherDesGardes(desGarder, NB_DES);
}

int calculerScore(int desGarder[NB_DES])
{
    int score = 0;

    for(int i = 0; i < NB_DES; i++)
    {
        int valeur = (desGarder[i] == ID_VERS) ? VALEUR_VERS : desGarder[i];
        score += valeur;
    }

#ifdef DEBUG_PLATEAU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "score = " << score << std::endl;
#endif

    return score;
}

bool verifierNombreDesGarder(int desGarder[NB_DES], int& desEnJeu)
{
    int compteurDesGardes = 0;
    for(int i = 0; i < NB_DES; i++)
    {
        if(desGarder[i] != 0)
        {
            compteurDesGardes++;
        }
    }
    if(compteurDesGardes == NB_DES)
    {
        afficherTousDesGardes();
        return false;
    }
    else
    {
        desEnJeu = NB_DES - compteurDesGardes;
        return true;
    }
}

int jouerTour(int desGarder[NB_DES], int& desEnJeu)
{
    int desObtenue[NB_DES];
    lancerDes(desObtenue, desEnJeu);
    afficherDes(desObtenue, desEnJeu);

    if(!peutRelancer(desObtenue, desGarder, desEnJeu))
    {
        afficherJeuNul();
        return 0;
    }
    garderDES(desGarder, desObtenue, desEnJeu);
    calculerScore(desGarder);
    return 1;
}

int obtenirSuiteDeDes()
{
    int desGarder[NB_DES] = { 0 };
    int desEnJeu          = NB_DES;

    while(verifierNombreDesGarder(desGarder, desEnJeu))
    {
        if(jouerTour(desGarder, desEnJeu) == 0)
        {
            return 0;
        }
        if(!demanderContinuer())
        {
            break;
        }
    }

    if(!contientV(desGarder))
    {
        afficherJeuNul();
        return 0;
    }
#ifdef DEBUG_PLATEAU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "Le joueur peut piocher un pickomino " << std::endl;
#endif

    return 0;
}
