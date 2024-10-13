#ifndef JEU_H
#define JEU_H

#include<ctime>
#include<cstdlib>

#define NB_DES 8

int lancerDES(int desObtenue[NB_DES]);
int jouerJeu();
int afficherDES(int desObtenue[NB_DES]);
int demanderValeur();
bool rechercherEtGarder(int desGarder[NB_DES], int desObtenue[NB_DES], int valeurGardee);
void garderDES(int desGarder[NB_DES], int desObtenue[NB_DES]);
bool nombreDesGarder(int desGarder[NB_DES]);
bool verifierLancer(int desGarder[NB_DES]);
int score();
#endif