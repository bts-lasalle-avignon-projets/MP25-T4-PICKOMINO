#ifndef JEU_H
#define JEU_H

#define DEBUG_JEU

#include "données.h"

int  jouerJeu();
int  demanderValeur();
bool rechercherEtGarder(int desGarder[NB_DES],
                        int desObtenue[NB_DES],
                        int valeurGardee,
                        int desEnJeu);
void garderDES(int desGarder[NB_DES], int desObtenue[NB_DES], int desEnJeu);
bool verifierNombreDesGarder(int desGarder[NB_DES]);
bool verifierLancer(int desGarder[NB_DES], int& desEnJeu);
// int score();

#endif