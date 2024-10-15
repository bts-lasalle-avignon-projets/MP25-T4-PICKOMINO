#ifndef IHM_H
#define IHM_H

#include <string>

void afficherDemandeValeur();
void afficherErreurEntree();
void afficherDemandeNombreAGarder(const std::string& valeur);
void afficherDesGardes(int desGarder[], int taille);
void afficherTousDesGardes();
int demanderValeur();
int obtenirNombreAGarder();
void afficherValeurDejaGardee();
void afficherDes(int desObtenue[], int desEnJeu);
void afficherLancerArrete();
void afficherJeuNul();
bool demanderContinuer();
#endif
