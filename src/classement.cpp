#include "classement.h"
#include <iostream>
#include <fstream>

int chargerClassement(PartieClassement classement[], int maxParties)
{
    FILE* fichier = fopen("classement.txt", "r");
    if(!fichier)
        return 0;

    int nbParties = 0;
    while(fscanf(fichier,
                 "%49[^,],%d\n",
                 classement[nbParties].nomJoueur,
                 &classement[nbParties].score) == 2 &&
          nbParties < maxParties)
    {
        nbParties++;
    }

    fclose(fichier);
    return nbParties;
}

void sauvegarderClassement(PartieClassement classement[], int nbParties)
{
    FILE* fichier = fopen("classement.txt", "w");
    if(!fichier)
    {
        perror("Erreur lors de la sauvegarde du classement");
        return;
    }

    for(int i = 0; i < nbParties; i++)
    {
        fprintf(fichier, "%s,%d\n", classement[i].nomJoueur, classement[i].score);
    }

    fclose(fichier);
}

void ajouterPartieClassement(PartieClassement classement[],
                             int*             nbParties,
                             const char*      nomJoueur,
                             int              score,
                             int              maxParties)
{
    // Ajouter la nouvelle partie
    if(*nbParties < maxParties)
    {
        strcpy(classement[*nbParties].nomJoueur, nomJoueur);
        classement[*nbParties].score = score;
        (*nbParties)++;
    }
    else if(score > classement[*nbParties - 1].score)
    {
        strcpy(classement[*nbParties - 1].nomJoueur, nomJoueur);
        classement[*nbParties - 1].score = score;
    }

    // Trier le classement
    for(int i = 0; i < *nbParties - 1; i++)
    {
        for(int j = i + 1; j < *nbParties; j++)
        {
            if(classement[i].score < classement[j].score)
            {
                PartieClassement temp = classement[i];
                classement[i]         = classement[j];
                classement[j]         = temp;
            }
        }
    }
}

bool verifierFichierVide()
{
    FILE* fichier = fopen("classement.txt", "w");
    if(!fichier)
    {
        perror("Erreur lors de la sauvegarde du classement");
        return false;
    }

    fseek(fichier, 0, SEEK_END);  // Déplacer le curseur à la fin du fichier
    long taille = ftell(fichier); // Obtenir la position actuelle (taille du fichier en octets)
    fclose(fichier);              // Fermer le fichier

    return (taille == 0); // Retourne true si la taille est 0 (fichier vide)
}