#ifndef IHM_H
#define IHM_H

#include <string>

#include "donnees.h"
#include "plateau.h"

int saisirNombreDeJoueurs();

void afficherPlateau(Plateau& plateau);
void afficherJoueur(int numeroJoueur);
void afficherBrochette(EtatPickomino pickominos[NB_PICKOMINOS]);
void afficherDes(int desObtenus[NB_DES], int nbDes);
void afficherDesGardes(int desGardes[NB_DES], int nbDes);
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
