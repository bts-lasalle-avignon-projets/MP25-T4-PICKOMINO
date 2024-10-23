#ifndef IHM_H
#define IHM_H

#include <string>

#include "donnees.h"
#include "plateau.h"

int saisirNombreDeJoueurs();

void afficherPlateau(Plateau& plateau);
void afficherDes(int desObtenus[], int nbDes);
void afficherDesGardes(int desGardes[], int nbDes);
void afficherScore(int score);

void afficherErreurEntree();
void afficherValeurDejaGardee();
void afficherTousDesGardes();
void afficherLancerArrete();
void afficherLancerNul();

char demanderValeurDe();
bool demander(const std::string& message);

#endif // IHM_H
