#ifndef IHM_H
#define IHM_H

#include <string>

#include "donnees.h"
#include "plateau.h"
#include "joueur.h"
#include "jeu.h"

int saisirNombreDeJoueurs();

void afficherPlateau(Plateau& plateau, Joueur& joueur);
void afficherPile(Joueur* joueurs, int nbJoueurs);
void afficherJoueur(Joueur& joueur);
void afficherBrochette(EtatPickomino pickominos[NB_PICKOMINOS]);
void afficherDes(int desObtenus[NB_DES], int nbDes);
void afficherDesGardes(int desGardes[NB_DES], int nbDes);
void afficherScore(int score);
void afficherPioche(int pickomino);
void afficherPicorer(int pickomino);

void afficherErreurEntree();
void afficherValeurDejaGardee();
void afficherTousDesGardes();
void afficherLancerArrete();
void afficherLancerNul();
void afficherScoreFinal(int nbjoueurs, Joueur joueurs[]);
void afficherErreurValeurIndisponible();

void demanderNomJoueur(int nbJoueurs, Joueur joueurs[]);
char demanderValeurDe();
bool demander(const std::string& message);

#endif // IHM_H
