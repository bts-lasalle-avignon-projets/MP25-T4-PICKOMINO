#ifndef CLASSEMENT_H
#define CLASSEMENT_H

#define NB_CARACTERE 50

#include <string>

struct PartieClassement
{
    std::string nomJoueur;
    int         score;
};

// Déclarations des fonctions
int  chargerClassement(PartieClassement classement[], int maxParties);
void sauvegarderClassement(PartieClassement classement[], int nbParties);
void ajouterPartieClassement(PartieClassement   classement[],
                             int&               nbParties,
                             const std::string& nomJoueur,
                             int                score);
void trierClassement(PartieClassement classement[], int& nbParties);
bool verifierFichierVide();
#endif // CLASSEMENT_H
