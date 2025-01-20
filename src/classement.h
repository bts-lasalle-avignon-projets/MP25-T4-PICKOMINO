#ifndef CLASSEMENT_H
#define CLASSEMENT_H

#define MAX_PARTIES 10

#include <cstdio>  // Pour FILE, fopen, fclose, fscanf, fprintf
#include <cstring> // Pour strcpy et memset

struct PartieClassement
{
    char nomJoueur[50];
    int  score;
};

// Déclarations des fonctions
int  chargerClassement(PartieClassement classement[], int maxParties);
void sauvegarderClassement(PartieClassement classement[], int nbParties);
void ajouterPartieClassement(PartieClassement classement[],
                             int*             nbParties,
                             const char*      nomJoueur,
                             int              score,
                             int              maxParties);
void afficherClassement(PartieClassement classement[], int nbParties);

#endif // CLASSEMENT_H
