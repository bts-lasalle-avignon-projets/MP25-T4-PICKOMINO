#ifndef PLATEAU_H
#define PLATEAU_H

//#define DEBUG_PLATEAU

#include "donnees.h"

struct Plateau
{
    int desGardes[NB_DES];
    int desObtenus[NB_DES];
    int desEnJeu;
    int pickominos[NB_PICKOMINOS];
};

void initialiserPlateau(Plateau& plateau);
void lancerDes(Plateau& plateau);
bool garderDes(Plateau& plateau);
int  calculerScore(int desGardes[NB_DES]);
bool estDejaGarde(int valeur, int desGardes[NB_DES], int nbDes);
bool contientV(int desGardes[NB_DES]);
bool verifierLancerNul(int desObtenus[NB_DES], int desGardes[NB_DES], int desEnJeu);
int  convertirValeurDe(char valeurDe);

#endif // PLATEAU_H