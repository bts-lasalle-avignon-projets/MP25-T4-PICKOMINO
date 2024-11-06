#ifndef IHM_H
#define IHM_H

#include <string>

#include "plateau.h"

void afficherPlateau(Plateau& plateau);
void afficherBrochette(EtatPickomino pickominos[]);
void afficherDes(int desObtenus[], int nbDes);
void afficherDesGardes(int desGardes[], int nbDes);
void afficherScore(int score);
void afficherPioche(int pickomino);

void afficherErreurEntree();
void afficherValeurDejaGardee();
void afficherTousDesGardes();
void afficherLancerArrete();
void afficherLancerNul();

char demanderValeurDe();
bool demander(const std::string& message);

#endif // IHM_H
