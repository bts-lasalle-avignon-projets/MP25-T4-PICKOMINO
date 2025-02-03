#ifndef IHM_H
#define IHM_H

#include <string>

#include "donnees.h"
#include "plateau.h"
#include "joueur.h"
#include "jeu.h"

int  saisirNombreDeJoueurs();
void saisirNombreDeJoueursIA(int& nbJoueursReels, int& nbJoueursTotaux, int& nbJoueursIA);

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
void afficherErreurDeveloppement();
void afficherBienvenue();
void afficherValeurDejaGardee();
void afficherTousDesGardes();
void afficherLancerArrete();
void afficherLancerNul();
void afficherScoreFinal(Joueur joueurs[], int nbjoueurs);
void afficherErreurValeurIndisponible();
void afficherChoixIA(const std::string& nomJoueur, int valeurChoisie);
void afficherGagnant(Joueur joueur);
void afficherPDF();

void demanderNomJoueur(Joueur joueurs[], int nbJoueurs);
char demanderValeurDe();
bool demander(const std::string& message);
int  demanderEntier(const std::string& message);
int  demanderEntierDansIntervalle(const std::string& message, int valeurMin, int valeurMax);

void afficherMenu();
void choisirModeDeJeu(int choixUtilisateur);
void afficherLogo();

#endif // IHM_H
