#include "jeu.h"
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
    for(int i = 0; i < jeu.nbJoueurs; i++)
    {
        jeu.joueurs[i].score = 0;
#ifdef DEBUG_JEU
        std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
        std::cout << "scoreFinal = " << jeu.joueurs[i].score << std::endl;
#endif
    }
    creerLesPilesDesJoueurs(jeu.joueurs, jeu.nbJoueurs);
    initialiserBrochette(jeu.plateau);
}

void jouerJeu()
{
    Jeu jeu;

    afficherBienvenue();

    initialiserJeu(jeu);
    demanderNomJoueur(jeu.joueurs, jeu.nbJoueurs);
    jeu.plateau.numeroJoueur = JOUEUR_DEBUT;
    do
    {
        initialiserPlateau(jeu.plateau, jeu.nbJoueurs);
        jouerTour(jeu.plateau, jeu.joueurs, jeu.nbJoueurs, jeu.joueurs[jeu.plateau.numeroJoueur]);
#ifdef DEBUG_JEU
        for(int i = 0; i < jeu.nbJoueurs; ++i)
        {
            std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
            std::cout << "Pile du joueur " << i << " : Sommet = " << jeu.joueurs[i].sommet
                      << std::endl;
        }
#endif
    } while(!estPartieFinie(jeu.plateau));
    calculerScoreFinal(jeu.joueurs, jeu.nbJoueurs);
    afficherScoreFinal(jeu.joueurs, jeu.nbJoueurs);
    int indexGagnant = trouverGagnant(jeu.joueurs, jeu.nbJoueurs);
    afficherGagnant(jeu.joueurs[indexGagnant]);
}

int jouerTour(Plateau& plateau, Joueur joueurs[], int nbJoueurs, Joueur& joueur)
{
    bool jeuActif = true;
    int  etatTour = LANCER_TERMINE;
    int  score    = 0;

    while(jeuActif)
    {
        lancerDes(plateau);
        afficherPlateau(plateau, joueur);
        afficherPile(joueurs, nbJoueurs);
        afficherScore(score);

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

            score = calculerScore(plateau.desGardes);
            afficherScore(score);

            if(!demander("continuer à lancer des dés"))
            {
#ifdef SIMULATION
                // Simuler l'état initial du jeu
                joueurs[0].pilePickominos[joueurs[0].sommet++] = 22;
                score                                          = 22;

                // Débogage pour vérifier l'état initial
                std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__
                          << "] ";
                std::cout << "Simulation : joueur[1] pilePickominos = ";
                for(int i = 0; i < joueurs[0].sommet; ++i)
                {
                    std::cout << joueurs[0].pilePickominos[i] << " ";
                }
                std::cout << std::endl;
#endif
                int pickomino = piocherPickomino(plateau, score, joueurs, nbJoueurs);

#ifdef DEBUG_JEU
                std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__
                          << "] ";
                std::cout << "pickomino = " << pickomino << std::endl;
#endif

                if(pickomino != AUCUN_PICKOMINO)
                {
                    afficherPioche(pickomino);
                }
#ifdef DEBUG_JEU
                calculerScoreFinal(joueurs, nbJoueurs);
                afficherScoreFinal(nbJoueurs, joueurs);
                afficherGagnant(joueurs, nbJoueurs);
#endif
                jeuActif = false;
            }
        }
    }

    return etatTour;
}

bool estPartieFinie(const Plateau& plateau)
{
    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        if(plateau.pickominos[i] == EtatPickomino::DISPONIBLE)
            return false;
    }
    return true;
}

void calculerScoreFinal(Joueur joueurs[], int nbJoueurs)
{
    for(int i = 0; i < nbJoueurs; i++)
    {
        joueurs[i].score = 0;
#ifdef DEBUG_JEU
        std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
        std::cout << "score Final : " << joueurs[i].score << std::endl;
#endif
        for(int j = 0; j < joueurs[i].sommet; j++)
        {
            joueurs[i].score += ((joueurs[i].pilePickominos[j] - VALEUR_PICKOMINO_MIN) /
                                 NB_VERS_PICKOMINO::QUATRE_VERS) +
                                1;
        }
    }
}

int trouverGagnant(Joueur joueurs[], int nbJoueurs)
{
    int meilleurScore = joueurs[0].score;
    int pickominoMax  = trouverPickominoMax(joueurs[0]);
    int joueurGagnant = 0;

    for(int i = 1; i < nbJoueurs; i++)
    {
        if(joueurs[i].score > meilleurScore)
        {
            meilleurScore = joueurs[i].score;
            joueurGagnant = i;
            pickominoMax  = trouverPickominoMax(joueurs[i]);
        }
        else if(meilleurScore == joueurs[i].score)
        {
            int pickominoMaxAVerifier = trouverPickominoMax(joueurs[i]);
            if(pickominoMaxAVerifier > pickominoMax)
            {
                joueurGagnant = i;
                pickominoMax  = pickominoMaxAVerifier;
            }
        }
    }

    return joueurGagnant;
}

int trouverPickominoMax(Joueur joueur)
{
    int pickominoMax = joueur.pilePickominos[0];

    for(int i = 1; i < joueur.sommet; i++)
    {
        if(joueur.pilePickominos[i] > pickominoMax)
        {
            pickominoMax = joueur.pilePickominos[i];
        }
    }

    return pickominoMax;
}