#ifndef JEU_H
#define JEU_H

#include "plateau.h"

//#define DEBUG_JEU
#define SIMULATION

#define LANCER_NUL     1
#define LANCER_TERMINE 0

struct Jeu
{
    int     nbJoueurs;
    Plateau plateau;
};

void initialiserJeu(Jeu& jeu);
void jouerJeu();
int  jouerTour(Plateau& plateau);
bool estPartieFinie(Plateau& plateau);

#endif // JEU_H
