#include "jeuIA.h"
#include "ihm.h"
#include <ctime>   // pour time
#include <cstdlib> // pour srand
#include <sstream>

std::istringstream simulatedInput;
std::ostringstream simulatedOutput;

#ifdef DEBUG_JEUIA
#include <iostream>
#endif

void simulerEntree(const std::string& entreeSimulee)
{
    simulatedInput.str("");                 // Réinitialise le flux simulé
    simulatedInput.clear();                 // Efface l'état du flux
    simulatedInput.str(entreeSimulee);      // Injecte la chaîne simulée dans le flux
    std::cin.rdbuf(simulatedInput.rdbuf()); // Redirige std::cin vers simulatedInput
}

void initialiserJeuIA(Jeu& jeu)
{
    srand(time(NULL));
    jeu.nbJoueursReels  = 0;
    jeu.nbJoueursTotaux = 0;
    saisirNombreDeJoueursIA(jeu.nbJoueursReels, jeu.nbJoueursTotaux, jeu.nbJoueursIA);

#ifdef DEBUG_JEUIA
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "Nombre de joueurs humains : " << jeu.nbJoueursReels << std::endl;
    std::cout << "Nombre total de joueurs : " << jeu.nbJoueursTotaux << std::endl;
#endif

    for(int i = 0; i < jeu.nbJoueursTotaux; ++i)
    {
        jeu.joueurs[i].estIA = (i >= jeu.nbJoueursReels);
        jeu.joueurs[i].nom =
          jeu.joueurs[i].estIA ? "IA " + std::to_string(i + 1) : std::to_string(i + 1);
        jeu.joueurs[i].scoreFinal = 0;
        jeu.joueurs[i].sommet     = 0;
    }

    creerLesPilesDesJoueurs(jeu.joueurs, jeu.nbJoueursTotaux);
    initialiserBrochette(jeu.plateau);
}

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

bool garderDesIA(Plateau& plateau, Joueur& joueur)
{
#ifdef DEBUG_JEUIA
    std::cout << "GarderDesIA" << std::endl;
#endif
    int  valeurGardee;
    bool dejaGardee = false;

    do
    {
        valeurGardee = choisirValeurDeIA(plateau, joueur);
#ifdef DEBUG_JEUIA
        std::cout << "valeurGardee : " << valeurGardee << std::endl;
#endif
        if(estPasDansLesDesLances(plateau, valeurGardee))
        {
            continue;
        }

        dejaGardee = estDejaGarde(valeurGardee, plateau.desGardes, NB_DES);
        if(dejaGardee)
        {
            continue;
        }

    } while(dejaGardee || estPasDansLesDesLances(plateau, valeurGardee));

    bool gardeEffectuee = false;
    int  nbDesGardes    = 0;

    for(int i = 0; i < plateau.desEnJeu; i++)
    {
        if(plateau.desObtenus[i] == valeurGardee)
        {
            for(size_t j = 0; j < NB_DES; j++)
            {
                if(plateau.desGardes[j] == 0)
                {
                    plateau.desGardes[j] = valeurGardee;
                    ++nbDesGardes;
                    gardeEffectuee = true;
                    break;
                }
            }
        }
    }

    plateau.desEnJeu -= nbDesGardes;

#ifdef DEBUG_PLATEAU
    std::cout << "desEnJeu = " << plateau.desEnJeu << std::endl;
#endif

    return gardeEffectuee;
}

int choisirValeurDeIA(Plateau& plateau, Joueur& joueur)
{
    int priorites[] = { 6, 5, 4, 3, 2, 1 };

    bool versDejaChoisi = false;

    for(size_t i = 0; i < sizeof(priorites) / sizeof(priorites[0]); ++i)
    {
#ifdef DEBUG_JEUIA
        std::cout << "Je suis dans la boucle pour la valeur : " << priorites[i] << std::endl;
#endif
        int valeurChoisie = priorites[i];

        bool dejaGardee = estDejaGarde(valeurChoisie, plateau.desGardes, NB_DES);
        if(dejaGardee)
        {
            continue;
        }

        for(int j = 0; j < plateau.desEnJeu; ++j)
        {
            if(valeurChoisie == ID_VERS)
            {
                if(plateau.desObtenus[j] == ID_VERS && !versDejaChoisi)
                {
                    versDejaChoisi = true;
                    return valeurChoisie;
                }
            }
            else if(plateau.desObtenus[j] == valeurChoisie)
            {
                return valeurChoisie;
            }
        }
    }

    return -1;
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
            if(score >= 21)
            {
                return true;
            }
        }
    }

    if(aUnV && score >= 21)
    {
        return true;
    }

    return false;
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
            garderDesIA(plateau, joueur);
            score = calculerScore(plateau.desGardes);
#ifdef DEBUG_JEUIA
            std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
            std::cout << "Le score est de : " << score << std::endl;
#endif
            if(reglesIA(plateau, joueur))
            {
#ifdef DEBUG_JEUIA
                std::cout << "Je respecte la règle et termine le tour." << std::endl;
#endif
                jeuActif = false;
            }
        }
    }

    return etatTour;
}

void jouerJeuIA()
{
    Jeu jeu;
    initialiserJeuIA(jeu);

    creerLesPilesDesJoueurs(jeu.joueurs, jeu.nbJoueursTotaux);
    jeu.plateau.numeroJoueur = JOUEUR_DEBUT;
    do
    {
        initialiserPlateau(jeu.plateau, jeu.nbJoueursTotaux);
        Joueur& joueurActuel = jeu.joueurs[jeu.plateau.numeroJoueur];
        if(estJoueurIA(joueurActuel))
        {
#ifdef DEBUG_JEUIA
            std::cout << "JouerTourIA" << std::endl;
#endif
            jouerTourIA(jeu.plateau, jeu.joueurs, jeu.nbJoueursTotaux, joueurActuel);
        }
        else
        {
            jouerTour(jeu.plateau, jeu.joueurs, jeu.nbJoueursTotaux, joueurActuel);
        }
#ifdef DEBUG_JEUIA
        for(int i = 0; i < jeu.nbJoueursTotaux; ++i)
        {
            std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
            std::cout << "Pile du joueur " << i << " : Sommet = " << jeu.joueurs[i].sommet
                      << std::endl;
        }
#endif
    } while(!estPartieFinie(jeu.plateau));
    calculerScoreFinalDesJoueurs(jeu.nbJoueursTotaux, jeu.joueurs);
    afficherScoreFinal(jeu.nbJoueursTotaux, jeu.joueurs);
}