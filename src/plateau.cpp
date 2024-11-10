#include "plateau.h"
#include "ihm.h"
#include "donnees.h"
#include <ctime>   // pour time
#include <cstdlib> // pour rand

#ifdef DEBUG_PLATEAU
#include <iostream>
#endif

void initialiserPlateau(Plateau& plateau, int nbJoueurs)
{
    plateau.numeroJoueur = (plateau.numeroJoueur + 1) % nbJoueurs;
    plateau.desEnJeu     = NB_DES;
    for(int i = 0; i < NB_DES; i++)
    {
        plateau.desGardes[i]  = 0;
        plateau.desObtenus[i] = 0;
    }
}

void initialiserBrochette(Plateau& plateau)
{
    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        plateau.pickominos[i]            = EtatPickomino::DISPONIBLE;
        plateau.proprietairePickomino[i] = -1;
    }
}

void lancerDes(Plateau& plateau)
{
#ifdef DEBUG_PLATEAU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "desEnJeu = " << plateau.desEnJeu << std::endl;
#endif

    for(int i = 0; i < plateau.desEnJeu; i++)
    {
        plateau.desObtenus[i] = (rand() % NB_FACES) + 1;
    }
}

bool garderDes(Plateau& plateau)
{
    int  valeurGardee;
    bool dejaGardee = false;

    do
    {
        valeurGardee = convertirValeurDe(demanderValeurDe());
        if(valeurGardee == VALEUR_DE_INCONNUE)
        {
#ifdef DEBUG_PLATEAU
            std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
            std::cout << "valeurGardee = " << valeurGardee << std::endl;
#endif
            return false;
        }

        dejaGardee = estDejaGarde(valeurGardee, plateau.desGardes, NB_DES - plateau.desEnJeu);

        if(dejaGardee)
            afficherValeurDejaGardee();

    } while(dejaGardee);

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
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "desEnJeu = " << plateau.desEnJeu << std::endl;
#endif

    return gardeEffectuee;
}

int calculerScore(int desGardes[NB_DES])
{
    int score = 0;

    for(int i = 0; i < NB_DES; i++)
    {
        int valeur = (desGardes[i] == ID_VERS) ? VALEUR_VERS : desGardes[i];
        score += valeur;
    }

#ifdef DEBUG_PLATEAU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "score = " << score << std::endl;
#endif

    return score;
}

bool estDejaGarde(int valeur, int desGardes[NB_DES], int nbDes)
{
    for(int i = 0; i < nbDes; i++)
    {
        if(desGardes[i] == valeur)
            return true;
    }
    return false;
}

bool contientV(int desGardes[NB_DES])
{
    for(int i = 0; i < NB_DES; i++)
    {
        if(desGardes[i] == ID_VERS)
            return true;
    }
    return false;
}

bool verifierLancerNul(int desObtenus[NB_DES], int desGardes[NB_DES], int desEnJeu)
{
    bool lancerNul = true;
    for(int i = 0; i < desEnJeu; i++)
    {
        bool dejaGarde = estDejaGarde(desObtenus[i], desGardes, NB_DES - desEnJeu);
#ifdef DEBUG_PLATEAU
        std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
        std::cout << "valeur = " << desObtenus[i] << std::endl;
        std::cout << "dejaGarde = " << dejaGarde << std::endl;
#endif

        if(!dejaGarde)
        {
            lancerNul = false;
        }
    }
    return lancerNul;
}

int convertirValeurDe(char valeurDe)
{
    if(valeurDe == 'V' || valeurDe == 'v')
        return ID_VERS;
    else if(valeurDe >= '1' && valeurDe <= '5')
        return valeurDe - '0';
    return VALEUR_DE_INCONNUE;
}

int piocherPickominos(int      desGardes[NB_DES],
                      int      score,
                      Plateau& plateau,
                      int      numeroJoueur,
                      Joueur   joueurs[])
{
    if(!contientV(desGardes))
    {
        retourDernierPickomino(joueurs[numeroJoueur], plateau);
        return -1;
    }

    int meilleurPickomino = trouverMeilleurPickomino(score, plateau);
    if(meilleurPickomino == -1)
    {
        retourDernierPickomino(joueurs[numeroJoueur], plateau);
        return -1;
    }

    ajouterPickominoAuJoueur(joueurs[numeroJoueur], meilleurPickomino, plateau, numeroJoueur);
    return meilleurPickomino;
}

int trouverMeilleurPickomino(int score, Plateau& plateau)
{
    int meilleurScore     = VALEUR_PICKOMINO_MIN - 1;
    int meilleurPickomino = -1;

    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        int valeur = i + VALEUR_PICKOMINO_MIN;
        if(plateau.pickominos[i] == EtatPickomino::DISPONIBLE && valeur <= score &&
           valeur > meilleurScore)
        {
            meilleurScore     = valeur;
            meilleurPickomino = i;
        }
    }
    return meilleurPickomino;
}

void ajouterPickominoAuJoueur(Joueur& joueur, int pickomino, Plateau& plateau, int numeroJoueur)
{
    joueur.pileJoueur[joueur.compteur++]     = pickomino + VALEUR_PICKOMINO_MIN;
    plateau.pickominos[pickomino]            = EtatPickomino::RETOURNE;
    plateau.proprietairePickomino[pickomino] = numeroJoueur;
}

void retourDernierPickomino(Joueur& joueur, Plateau& plateau)
{
    if(joueur.compteur > 0)
    {
        int dernierPickomino = joueur.pileJoueur[--joueur.compteur] - VALEUR_PICKOMINO_MIN;
        joueur.pileJoueur[joueur.compteur]              = 0;
        plateau.pickominos[dernierPickomino]            = EtatPickomino::DISPONIBLE;
        plateau.proprietairePickomino[dernierPickomino] = -1;
    }
}
