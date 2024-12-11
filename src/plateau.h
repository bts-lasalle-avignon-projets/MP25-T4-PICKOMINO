#ifndef PLATEAU_H
#define PLATEAU_H

// #define DEBUG_PLATEAU

#include "donnees.h"
#include "joueur.h"

enum EtatPickomino
{
    RETOURNE   = -1,
    DISPONIBLE = 0,
};

struct Plateau
{
    int           numeroJoueur;
    int           desGardes[NB_DES];
    int           desObtenus[NB_DES];
    int           desEnJeu;
    EtatPickomino pickominos[NB_PICKOMINOS];
};

void initialiserPlateau(Plateau& plateau, int nbJoueurs);
void initialiserBrochette(Plateau& plateau);
void lancerDes(Plateau& plateau);
bool garderDes(Plateau& plateau);
int  calculerScore(int desGardes[NB_DES]);
bool estDejaGarde(int valeur, int desGardes[NB_DES], int nbDes);
bool contientV(int desGardes[NB_DES]);
bool verifierLancerNul(int desObtenus[NB_DES], int desGardes[NB_DES], int desEnJeu);
int  convertirValeurDe(char valeurDe);
int  piocherPickomino(Plateau& plateau, int score, Joueur joueurs[NB_JOUEURS_MAX], int nbJoueurs);
int  trouverMeilleurPickomino(const Plateau& plateau, int score);
void ajouterPickominoAuJoueur(Joueur& joueur, int pickomino, Plateau& plateau);
void rendreDernierPickomino(Joueur& joueur, Plateau& plateau);
void retournerPickominos(Plateau& plateau);
int  trouverPickominoPile(Joueur        joueurs[NB_JOUEURS_MAX],
                          int           nbJoueurs,
                          const Joueur& joueurExclu,
                          int           scoreJoueur);
int  picorerJoueur(Joueur&        joueur,
                   Joueur         joueurs[NB_JOUEURS_MAX],
                   int            nbJoueurs,
                   int            pickominoVole,
                   const Plateau& plateau);
#endif // PLATEAU_H