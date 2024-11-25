// jeu.cpp
#include "jeu.h"
#include "joueur.h"
#include "plateau.h"
#include "ihm.h"
#include <ctime>   // pour time
#include <cstdlib> // pour srand

#ifdef DEBUG_JEU
#include <iostream>
#endif

void initialiserJeu(Jeu& jeu)
{
    srand(time(NULL));
    jeu.nbJoueurs = saisirNombreDeJoueurs();
#ifdef DEBUG_JEU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "nbJoueurs = " << jeu.nbJoueurs << std::endl;
#endif
    creerLesPilesDesJoueurs(jeu.joueurs, jeu.nbJoueurs);
    jeu.plateau.numeroJoueur = -1;
    initialiserBrochette(jeu.plateau);
}

void jouerJeu()
{
    Jeu jeu;

    initialiserJeu(jeu);

    for(int i = 0; i < jeu.nbJoueurs; i++)
    {
        gererLeSommetDesPiles(jeu.joueurs[i]);
    }

    initialiserPlateau(jeu.plateau, jeu.nbJoueurs);

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
            // @todo si le lancer du joueur est nul : il doit remettre sur la brochette le dernier
            // Pickomino qu’il avait gagné et placé au-dessus de sa pile. Le Pickomino le plus élevé
            // sur la brochette est alors retourné face cachée et ne peut plus être récupéré.
            afficherLancerNul();
            etatTour = LANCER_NUL;
            jeuActif = false;
        }
        else
        {
            if(!garderDes(plateau))

            {
                afficherValeurDejaGardee();
            }
            score = calculerScore(plateau.desGardes);
            afficherScore(score);

            if(!demander("continuer à lancer des dés"))
            {
                int pickomino = piocherPickomino(plateau, score, joueurs);
#ifdef DEBUG_JEU
                std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__
                          << "] ";
                std::cout << "pickomino = " << pickomino << std::endl;
#endif
                if(pickomino != AUCUN_PICKOMINO)
                {
                    afficherPioche(pickomino + VALEUR_PICKOMINO_MIN);
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
