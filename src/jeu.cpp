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
        jeu.joueurs[i].scoreFinal = 0;
#ifdef DEBUG_JEU
        std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
        std::cout << "scoreFinal = " << jeu.joueurs[i].scoreFinal << std::endl;
#endif
    }
    creerLesPilesDesJoueurs(jeu.joueurs, jeu.nbJoueurs);
    initialiserBrochette(jeu.plateau);
}

void jouerJeu()
{
    Jeu jeu;

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
    calculerScoreFinalDesJoueurs(jeu.nbJoueurs, jeu.joueurs);
    afficherScoreFinal(jeu.nbJoueurs, jeu.joueurs);
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

#ifdef DEBUG_JEU
                int totalVers = calculerNbDeVerDuJoueur(joueur);
                std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__
                          << "] ";
                std::cout << "Nombre total de vers du joueur : " << totalVers << std::endl;
#endif

                if(pickomino != AUCUN_PICKOMINO)
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

int calculerVerPickomino(int pickomino)
{
    int valeurPickominoEnVer = 0;
    if(pickomino >= VALEUR_PICKOMINO_MIN &&
       pickomino <= LIMITE_PICKOMINO::VALEUR_PICKOMINO_MAX_UN_VER)
    {
        valeurPickominoEnVer = NB_VERS_PICKOMINO::UN_VER;
    }
    if(pickomino > LIMITE_PICKOMINO::VALEUR_PICKOMINO_MAX_UN_VER &&
       pickomino <= LIMITE_PICKOMINO::VALEUR_PICKOMINO_MAX_DEUX_VERS)
    {
        valeurPickominoEnVer = NB_VERS_PICKOMINO::DEUX_VERS;
    }
    if(pickomino > LIMITE_PICKOMINO::VALEUR_PICKOMINO_MAX_DEUX_VERS &&
       pickomino <= LIMITE_PICKOMINO::VALEUR_PICKOMINO_MAX_TROIS_VERS)
    {
        valeurPickominoEnVer = NB_VERS_PICKOMINO::TROIS_VERS;
    }
    if(pickomino > LIMITE_PICKOMINO::VALEUR_PICKOMINO_MAX_TROIS_VERS &&
       pickomino <= VALEUR_PICKOMINO_MAX)
    {
        valeurPickominoEnVer = NB_VERS_PICKOMINO::QUATRE_VERS;
    }
    return valeurPickominoEnVer;
}

int calculerNbDeVerDuJoueur(Joueur& joueur)
{
    int nbDeVerTotal = 0;

    for(int i = 0; i <= joueur.sommet; i++)
    {
        int pickomino = joueur.pilePickominos[i];
        nbDeVerTotal += calculerVerPickomino(pickomino);
    }

    return nbDeVerTotal;
}

void calculerScoreFinalDesJoueurs(int nbJoueurs, Joueur joueurs[])
{
    for(int i = 0; i < nbJoueurs; i++)
    {
        int nbDeVerFinalDuJoueur = calculerNbDeVerDuJoueur(joueurs[i]);
        joueurs[i].scoreFinal += nbDeVerFinalDuJoueur;
#ifdef DEBUG_JEU
        std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
        std::cout << "Score total des vers calculé : " << joueurs[i].scoreFinal << std::endl;
#endif
    }
}