#include "jeu.h"
#include "plateau.h"
#include "ihm.h"
#include <ctime>   // pour time
#include <cstdlib> // pour srand

#ifdef DEBUG_JEU
#include <iostream>
#endif

void initialiserJeu()
{
    srand(time(NULL));
    // @todo initialiser les données du jeu
}

void jouerJeu()
{
    Plateau plateau;

    initialiserJeu();
    initialiserBrochette(plateau);

#ifdef SIMULATION

    int nbJoueurs = saisirNombreDeJoueurs();
#ifdef DEBUG_JEU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "nbJoueurs = " << nbJoueurs << std::endl;
#endif
    do
    {
        initialiserPlateau(plateau);
        jouerTour(plateau);
    } while (!verifierEtatPickominos(plateau));
#endif
}

int jouerTour(Plateau& plateau)
{
    bool jeuActif = true;
    int etatTour = LANCER_TERMINE;
    int score = 0;

    while (jeuActif)
    {
        lancerDes(plateau);
        afficherPlateau(plateau);

        if (verifierLancerNul(plateau.desObtenus, plateau.desGardes, plateau.desEnJeu))
        {
            afficherLancerNul();
            etatTour = LANCER_NUL;
            jeuActif = false;
        }
        else
        {
            if (!garderDes(plateau))
            {
                afficherValeurDejaGardee();
            }
            score = calculerScore(plateau.desGardes);
            afficherScore(score);

            if (!demander("continuer à lancer des dés"))
            {
                afficherPioche(piocherPickominos(plateau.desGardes, score, plateau));
                jeuActif = false;
            }
        }
    }

    return etatTour;
}

bool verifierEtatPickominos(Plateau& plateau)
{
    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        if(plateau.pickominos[i] == EtatPickomino::DISPONIBLE)
            return false;
    }
    return true;
}

