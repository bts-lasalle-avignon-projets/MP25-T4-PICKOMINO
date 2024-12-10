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
        plateau.pickominos[i] = EtatPickomino::DISPONIBLE;
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

int piocherPickomino(Plateau& plateau, int score, Joueur joueurs[NB_JOUEURS_MAX], int nbJoueurs)
{
    if(!contientV(plateau.desGardes))
    {
        rendreDernierPickomino(joueurs[plateau.numeroJoueur], plateau);
        return AUCUN_PICKOMINO;
    }
    int pickominoPile = picorerJoueur(joueurs[plateau.numeroJoueur], joueurs, nbJoueurs, score);
#ifdef DEBUG_PLATEAU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "pickomino Pile : " << pickominoPile << std::endl;
#endif
    if(pickominoPile != AUCUN_PICKOMINO)
    {
        return pickominoPile;
    }

    int meilleurPickomino = trouverMeilleurPickomino(plateau, score);
    if(meilleurPickomino != AUCUN_PICKOMINO)
    {
        ajouterPickominoAuJoueur(joueurs[plateau.numeroJoueur], meilleurPickomino, plateau);
        return meilleurPickomino;
    }

    rendreDernierPickomino(joueurs[plateau.numeroJoueur], plateau);
    return AUCUN_PICKOMINO;
}

int trouverMeilleurPickomino(Plateau& plateau, int score)
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
#ifdef DEBUG_PLATEAU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "meilleurPickomino = " << meilleurPickomino << std::endl;
#endif

    return meilleurPickomino;
}

void ajouterPickominoAuJoueur(Joueur& joueur, int pickomino, Plateau& plateau)
{
#ifdef DEBUG_PLATEAU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "sommet = " << joueur.sommet << std::endl;
#endif
    joueur.pilePickominos[joueur.sommet++] = pickomino + VALEUR_PICKOMINO_MIN;
    plateau.pickominos[pickomino]          = EtatPickomino(plateau.numeroJoueur + 1);
#ifdef DEBUG_PLATEAU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "pickomino = " << pickomino << std::endl;
#endif
}

void rendreDernierPickomino(Joueur& joueur, Plateau& plateau)
{
#ifdef DEBUG_PLATEAU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "joueur.compteur = " << joueur.sommet;

#endif
    if(joueur.sommet > 0)
    {
        int dernierPickomino = joueur.pilePickominos[--joueur.sommet] - VALEUR_PICKOMINO_MIN;
#ifdef DEBUG_PLATEAU
        std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
        std::cout << "dernierPickomino = " << dernierPickomino << std::endl;
#endif
        plateau.pickominos[dernierPickomino] = EtatPickomino::DISPONIBLE;
        retournerPickominos(plateau);
    }
}

void retournerPickominos(Plateau& plateau)
{
    int valeur = VALEUR_DE_INCONNUE;
    int index  = VALEUR_DE_INCONNUE;

    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        if(plateau.pickominos[i] == EtatPickomino::DISPONIBLE)
        {
            int valeurPickomino = i + VALEUR_PICKOMINO_MIN;
            if(valeur == VALEUR_DE_INCONNUE || valeurPickomino > valeur)
            {
                valeur = valeurPickomino;
                index  = i;
            }
        }
    }
    if(index != VALEUR_DE_INCONNUE)
    {
        plateau.pickominos[index] = EtatPickomino::RETOURNE; // On retourne ce Pickomino
    }
}
int picorerJoueur(Joueur& joueur, Joueur joueurs[NB_JOUEURS_MAX], int nbJoueurs, int scoreJoueur)
{
    for(int i = 0; i < nbJoueurs; ++i)
    {
        if(&joueurs[i] != &joueur)
        {
            int sommetPickomino = joueurs[i].pilePickominos[joueurs[i].sommet - 1];
            if(sommetPickomino == scoreJoueur) // Vérifier que le sommet correspond au score
            {
                // Retirer le Pickomino du joueur cible
                joueurs[i].sommet--;

                // Ajouter le Pickomino au joueur actuel
                joueur.pilePickominos[joueur.sommet++] = sommetPickomino;

#ifdef DEBUG_PLATEAU
                std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__
                          << "] ";
                std::cout << "Joueur a picoré le Pickomino " << sommetPickomino << " du joueur "
                          << i << std::endl;
#endif

                return sommetPickomino; // Retourner le Pickomino volé
            }
        }
    }

#ifdef DEBUG_PLATEAU
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "Aucun Pickomino correspondant au score " << scoreJoueur
              << " n'a été trouvé pour picorer." << std::endl;
#endif

    return AUCUN_PICKOMINO; // Aucun vol possible
}
