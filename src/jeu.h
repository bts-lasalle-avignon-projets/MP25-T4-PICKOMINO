#ifndef JEU_H
#define JEU_H

#include "plateau.h"

#define DEBUG_JEU
#define SIMULATION

void initialiserJeu();
void jouerJeu();
int jouerTour(Plateau& plateau);

#endif // JEU_H
