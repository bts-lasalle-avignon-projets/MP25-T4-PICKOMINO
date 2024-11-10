// jeu.cpp
#include "jeu.h"
#include "plateau.h"
#include "ihm.h"
#include "joueur.h"
#include <ctime>   // pour time
#include <cstdlib> // pour srand

#ifdef DEBUG_JEU
#include <iostream>
#endif

void initialiserJeu(Jeu& jeu)
{
    srand(time(NULL));
    jeu.nbJoueurs            = saisirNombreDeJoueurs();
    jeu.plateau.numeroJoueur = -1;

#ifdef DEBUG_JEU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "nbJoueurs = " << jeu.nbJoueurs << std::endl;
#endif
}

void jouerJeu()
{
    Jeu jeu;

    initialiserJeu(jeu);
    initialiserBrochette(jeu.plateau);

    do
    {
        initialiserPlateau(jeu.plateau, jeu.nbJoueurs);
        jouerTour(jeu.plateau, jeu.joueurs);
    } while(!estPartieFinie(jeu.plateau));
}

int jouerTour(Plateau& plateau, Joueur joueurs[])
{
    bool jeuActif = true;
    int  etatTour = LANCER_TERMINE;
    int  score    = 0;

    while(jeuActif)
    {
        lancerDes(plateau);
        afficherPlateau(plateau);

        if(verifierLancerNul(plateau.desObtenus, plateau.desGardes, plateau.desEnJeu))
        {
            afficherLancerNul();
            etatTour = LANCER_NUL;
            jeuActif = false;
        }
        else
        {
            if(!garderDes(plateau))
                afficherValeurDejaGardee();
            score = calculerScore(plateau.desGardes);
            afficherScore(score);

            if(!demander("continuer à lancer des dés"))
            {
                int pickomino = piocherPickominos(plateau.desGardes,
                                                  score,
                                                  plateau,
                                                  plateau.numeroJoueur,
                                                  joueurs);
                if(pickomino != -1)
                {
                    afficherPioche(pickomino);
                }
                jeuActif = false;
            }
        }
    }
    return etatTour;
}

bool estPartieFinie(Plateau& plateau)
{
    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        if(plateau.pickominos[i] == EtatPickomino::DISPONIBLE)
            return false;
    }
    return true;
}
