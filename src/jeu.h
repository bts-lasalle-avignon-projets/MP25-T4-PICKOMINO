#ifndef JEU_H
#define JEU_H

#include "plateau.h"

#define DEBUG_JEU
#define SIMULATION

#define LANCER_NUL     1
#define LANCER_TERMINE 0

void initialiserJeu();
void jouerJeu();
int  jouerTour(Plateau& plateau);

#endif // JEU_H
