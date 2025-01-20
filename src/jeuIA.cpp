#include "jeuIA.h"
#include "ihm.h"
#include <ctime>   // pour time
#include <cstdlib> // pour srand

#ifdef DEBUG_JEUIA
#include <iostream>
#endif

bool estValeurGardee(int valeur, const Joueur& joueur)
{
    if(valeur == ID_VERS)
    {
        return true;
    }
    else if(valeur >= 1 && valeur <= 5)
    {
        for(int i = 0; i < joueur.sommet; ++i)
        {
            if(joueur.pilePickominos[i] == valeur)
            {
                return true;
            }
        }
    }
    return false;
}

char choisirValeurDeIA(Plateau& plateau, Joueur& joueur)
{
    char priorites[] = { '6', '5', '4', '3', '2', '1' };

    for(size_t i = 0; i < sizeof(priorites) / sizeof(priorites[0]); ++i)
    {
        char valeurChoisie = priorites[i];

        if(estValeurGardee(valeurChoisie == '6' ? ID_VERS : valeurChoisie - '0', joueur))
        {
            continue;
        }

        for(int j = 0; j < plateau.desEnJeu; ++j)
        {
            if((valeurChoisie == '6' && plateau.desObtenus[j] == ID_VERS) ||
               (valeurChoisie >= '1' && valeurChoisie <= '5' &&
                plateau.desObtenus[j] == valeurChoisie - '0'))
            {
                return valeurChoisie;
            }
        }
    }

    return 'V';
}

bool reglesIA(Plateau& plateau, Joueur& joueur)
{
    int  score = calculerScore(plateau.desGardes);
    bool aUnV  = false;

    for(int i = 0; i < NB_DES; i++)
    {
        if(plateau.desGardes[i] == ID_VERS)
        {
            aUnV = true;
        }
    }

    if(aUnV && score >= 21)
    {
        return false;
    }

    return true;
}

void initialiserJeuIA(Jeu& jeu)
{
    srand(time(NULL));
    jeu.nbJoueursReels  = 0;
    jeu.nbJoueursTotaux = 0;

    saisirNombreDeJoueursIA(jeu.nbJoueursReels, jeu.nbJoueursTotaux);
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

int jouerTourIA(Plateau& plateau, Joueur joueurs[], int nbJoueurs, Joueur& joueur)
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
            if(reglesIA(plateau, joueur))
            {
                jeuActif = false;
            }
            else
            {
                if(estJoueurIA(joueur))
                {
                    char valeurChoisie = choisirValeurDeIA(plateau, joueur);
                    afficherChoixIA("IA", valeurChoisie);
                    if(reglesIA(plateau, joueur))
                    {
                        jeuActif = false;
                    }
                }
            }
        }
    }

    return etatTour;
}

void jouerJeuIA()
{
    Jeu jeu;
    initialiserJeuIA(jeu);

    creerLesPilesDesJoueurs(jeu.joueurs, jeu.nbJoueurs);
    jeu.plateau.numeroJoueur = JOUEUR_DEBUT;
    do
    {
        initialiserPlateau(jeu.plateau, jeu.nbJoueurs);
        Joueur& joueurActuel = jeu.joueurs[jeu.plateau.numeroJoueur];
        if(estJoueurIA(joueurActuel))
        {
            jouerTourIA(jeu.plateau, jeu.joueurs, jeu.nbJoueurs, joueurActuel);
        }
        else
        {
            jouerTour(jeu.plateau, jeu.joueurs, jeu.nbJoueurs, joueurActuel);
        }
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