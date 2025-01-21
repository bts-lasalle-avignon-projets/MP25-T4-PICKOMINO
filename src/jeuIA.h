#ifndef JEUIA_H
#define JEUIA_H
#define DEBUG_JEUIA
#include "joueur.h"
#include "plateau.h"
#include "jeu.h"

#define LANCER_NUL     1
#define LANCER_TERMINE 0

bool estValeurGardee(int valeur, const Joueur& joueur);
bool garderDesIA(Plateau& plateau, Joueur& joueur);
char choisirValeurDeIA(Plateau& plateau, Joueur& joueur);
bool reglesIA(Plateau& plateau, Joueur& joueur, bool& valeursGardees);
void initialiserJeuIA(Jeu& jeu);
int  jouerTourIA(Plateau& plateau, Joueur joueurs[], int nbJoueurs, Joueur& joueur);
void jouerJeuIA();
#endif