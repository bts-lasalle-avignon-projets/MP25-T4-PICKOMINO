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
    demanderNomJoueur(jeu.nbJoueurs, jeu.joueurs);
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
    afficherScoreFinal(jeu.nbJoueurs, jeu.joueurs);
    int indexGagnant = trouverGagant(jeu.joueurs, jeu.nbJoueurs);
    afficherGagnant(jeu.joueurs, indexGagnant);
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

bool estPartieFinie(Plateau& plateau)
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
            if(joueurs[i].pilePickominos[j] <= LIMITE_PICKOMINO::VALEUR_PICKOMINO_MAX_UN_VER)
            {
                joueurs[i].score += NB_VERS_PICKOMINO::UN_VER;
            }
            else if(joueurs[i].pilePickominos[j] <=
                    LIMITE_PICKOMINO::VALEUR_PICKOMINO_MAX_DEUX_VERS)
            {
                joueurs[i].score += NB_VERS_PICKOMINO::DEUX_VERS;
            }
            else if(joueurs[i].pilePickominos[j] <=
                    LIMITE_PICKOMINO::VALEUR_PICKOMINO_MAX_TROIS_VERS)
            {
                joueurs[i].score += NB_VERS_PICKOMINO::TROIS_VERS;
            }
            else
            {
                joueurs[i].score += NB_VERS_PICKOMINO::QUATRE_VERS;
            }
        }
    }
}

int trouverGagant(Joueur joueur[], int nbJoueur)
{
    int  meilleurScore = joueur[0].score; // Le score est initialement celui du joueur 1
    int  joueurGagnant = 0;
    bool egalite       = false;
    for(int i = 1; i < nbJoueur;
        i++) // i = 1 pour directement comparer le deuxième joueur au premier
    {
        if(joueur[i].score > meilleurScore)
        {
            meilleurScore = joueur[i].score;
            joueurGagnant = i;
            egalite       = false;
        }
        else if(meilleurScore == joueur[i].score)
        {
            egalite = true;
        }
    }

    if(egalite)
    {
        joueurGagnant = trouverPickoGagnant(joueur, nbJoueur);
    }

    return joueurGagnant;
}

int trouverPickoGagnant(Joueur joueur[], int nbJoueur)
{
    int pickoGagnant  = joueur[0].pilePickominos[0];
    int joueurGagnant = 0;
    for(int i = 0; i < nbJoueur; i++)
    {
        for(int j = 0; j < NB_PICKOMINOS; j++)
        {
            if(joueur[i].pilePickominos[j] > pickoGagnant)
            {
                pickoGagnant  = joueur[i].pilePickominos[j];
                joueurGagnant = i;
            }
        }
    }
    return joueurGagnant;
}