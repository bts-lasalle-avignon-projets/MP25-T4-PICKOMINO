#ifndef JEU_H
#define JEU_H

#include "joueur.h"
#include "plateau.h"

// #define DEBUG_JEU
//   #define SIMULATION

#define VERSION "1.0"

#define LANCER_NUL     1
#define LANCER_TERMINE 0

struct Jeu
{
    int     nbJoueurs;
    int     nbJoueursReels; // Nombre de joueurs réels pour IA
    int     nbJoueursIA;
    int     nbJoueursTotaux; // Nombre total de joueurs pour IA (réels + IA)
    Joueur  joueurs[NB_JOUEURS_MAX];
    Plateau plateau;
};

void initialiserJeu(Jeu& jeu);
void jouerJeu();
int  jouerTour(Plateau& plateau, Joueur joueurs[], int nbJoueurs, Joueur& joueur);
bool estPartieFinie(Plateau& plateau);
int  calculerVerPickomino(int pickomino);
int  calculerNbDeVerDuJoueur(Joueur& joueur);
void calculerScoreFinalDesJoueurs(int nbJoueurs, Joueur joueurs[]);

#endif // JEU_H