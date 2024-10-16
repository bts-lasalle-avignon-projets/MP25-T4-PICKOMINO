#ifndef PLATEAU_H
#define PLATEAU_H

//#define DEBUG_PLATEAU

#include "donnees.h"

int  obtenirSuiteDeDes();
int  demanderValeur();
bool rechercherEtGarder(int desGarder[NB_DES],
                        int desObtenue[NB_DES],
                        int valeurGardee,
                        int desEnJeu);
void garderDES(int desGarder[NB_DES], int desObtenue[NB_DES], int desEnJeu);
bool verifierNombreDesGarder(int desGarder[NB_DES]);
bool verifierLancer(int desGarder[NB_DES], int& desEnJeu);
int  calculerScore(int desGarder[NB_DES]);

#endif