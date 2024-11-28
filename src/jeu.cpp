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
    initialiserBrochette(jeu.plateau);
}

void jouerJeu()
{
    Jeu jeu;

    initialiserJeu(jeu);

    int joueurActif = 0;

    do
    {
        joueurActif = (joueurActif + 1) % jeu.nbJoueurs;

        initialiserPlateau(jeu.plateau, jeu.nbJoueurs);
        jouerTour(jeu.plateau, jeu.joueurs, jeu.joueurs[jeu.plateau.numeroJoueur]);
#ifdef DEBUG_JEU
        for(int i = 0; i < jeu.nbJoueurs; i++)
        {
            std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
            std::cout << "Pile du joueur " << i << " : Sommet = " << jeu.joueurs[i].sommet
                      << std::endl;
        }
#endif
    } while(!estPartieFinie(jeu.plateau));
}

int jouerTour(Plateau& plateau, Joueur joueurs[], Joueur& joueur)
{
    bool jeuActif = true;
    int  etatTour = LANCER_TERMINE;
    int  score    = 0;

    while(jeuActif)
    {
        lancerDes(plateau);       // Lancer les dés
        afficherPlateau(plateau); // Afficher l'état du plateau

        if(verifierLancerNul(plateau.desObtenus, plateau.desGardes, plateau.desEnJeu))
        {
            rendreDernierPickomino(joueur, plateau);
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

            score = calculerScore(plateau.desGardes); // Calcul du score
            afficherScore(score);                     // Afficher le score

            // Demander si le joueur veut continuer à lancer
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
                    afficherPioche(pickomino +
                                   VALEUR_PICKOMINO_MIN); // Afficher le Pickomino pioché
                }
                jeuActif = false;
            }
        }
    }

    return etatTour; // Retourner l'état du tour (LANCER_NUL ou LANCER_TERMINE)
}

bool estPartieFinie(Plateau& plateau)
{
    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        if(plateau.pickominos[i] == EtatPickomino::DISPONIBLE)
            return false; // Si des Pickominos sont encore disponibles, la partie n'est pas finie
    }
    return true; // Si aucun Pickomino n'est disponible, la partie est finie
}
