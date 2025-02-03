#include "classement.h"
#include "donnees.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;
int chargerClassement(PartieClassement classement[], int maxParties)
{
    ifstream fichier("classement.txt");
    if(!fichier)
    {
        cerr << "Erreur lors de l'ouverture du fichier" << endl;
        return 0;
    }

    int    nbParties = 0;
    string ligne;

    while(nbParties < maxParties && getline(fichier, ligne))
    {
        stringstream ligneLu(ligne);
        getline(ligneLu, classement[nbParties].nomJoueur, ','); // Lire le nom jusqu'à la virgule
        ligneLu >> classement[nbParties].score;
        nbParties++;
    }

    fichier.close();
    return nbParties;
}

void sauvegarderClassement(PartieClassement classement[], int nbParties)
{
    ofstream fichier("classement.txt");
    if(!fichier)
    {
        cerr << "Erreur lors de la sauvegarde du classement";
        return;
    }

    for(int i = 0; i < nbParties; i++)
    {
        fichier << classement[i].nomJoueur << "," << classement[i].score << "\n";
    }

    fichier.close();
}

void ajouterPartieClassement(PartieClassement   classement[],
                             int&               nbParties,
                             const std::string& nomJoueur,
                             int                score)
{
    // Ajouter la nouvelle partie
    if(nbParties < MAX_PARTIES)
    {
        classement[nbParties].nomJoueur = nomJoueur;
        classement[nbParties].score     = score;
        (nbParties)++;
    }
    else if(score > classement[nbParties - 1].score)
    {
        classement[nbParties - 1].nomJoueur = nomJoueur;
        classement[nbParties - 1].score     = score;
    }
    trierClassement(classement, nbParties);
}

void trierClassement(PartieClassement classement[], int& nbParties)
{
    // Trier le classement
    for(int i = 0; i < nbParties - 1; i++)
    {
        for(int j = i + 1; j < nbParties; j++)
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
    ifstream fichier("classement.txt");
    if(!fichier)
    {
        cerr << "Erreur lors de l'ouverture du fichier";
        return true;
    }
    return fichier.peek() == EOF;
}