#include "jeu.h"
#include <iostream>


int lancerDES(int desObtenue[NB_DES])
{
    srand(time(NULL));
    for (size_t i = 0; i < NB_DES; i++)
    {
        int valeur = rand() % 6;
        desObtenue[i] = (valeur == 5) ? 6 : valeur + 1;

    }
    return 0;    
}

int afficherDES(int desObtenue[NB_DES])
{
    std::cout << "Des obtenue au lancer : ";
    for (size_t i = 0; i < NB_DES; i++)
    {
        if (desObtenue[i] == 6) std::cout << "V " ;
        else std::cout << desObtenue[i] << " ";        
    }
    std::cout << std::endl;
    return 0;
}

int demanderValeur()
{
    char valeur;
    std::cout << "Choisir une valeur a garder : ";
    std::cin >> valeur; 
    return valeur;
}

int convertirValeur(char valeur) {
    if (valeur == 'V' || valeur == 'v') return 6;  
    else if (valeur >= '1' && valeur <= '5') return valeur - '0'; 
    return -1; 
}

bool rechercherEtGarder(int desGarder[NB_DES], int desObtenue[NB_DES], int valeurGardee) {
    for (size_t i = 0; i < NB_DES; i++) {
        if (desGarder[i] == valeurGardee) {
            return false;
        }
    }
    bool valeurTrouvee = false;
    for (size_t i = 0; i < NB_DES; i++)
    {
        if (desObtenue[i] == valeurGardee)
        {
            desGarder[i] = desObtenue[i];
            valeurTrouvee = true;
        }
    }
    return valeurTrouvee;
}


void garderDES(int desGarder[NB_DES], int desObtenue[NB_DES]) {
    int valeurGardee = convertirValeur(demanderValeur());
    if (valeurGardee == -1) {
        std::cout << "Entree invalide." << std::endl;
        return;
    }
    if (rechercherEtGarder(desGarder, desObtenue, valeurGardee)) {
        std::cout << "Vous avez garde : ";
        for (size_t i = 0; i < NB_DES; i++)
            if (desGarder[i] != 0) std::cout << (desGarder[i] == 6 ? "V" : std::to_string(desGarder[i])) << " ";
        std::cout << std::endl;
    } else std::cout << "Vous ne pouvez pas garder cette valeur." << std::endl;
}

bool verifierNombreDesGarder(int desGarder[NB_DES])
{
    int countGardes = 0;
    for (size_t i = 0; i < NB_DES; i++) {
        if (desGarder[i] != 0) {
            countGardes++;
        }
    }
    if (countGardes == NB_DES) {
        std::cout << "Tous les dés sont gardés. Aucune relance." << std::endl;
        return false;
    }
}
/*
bool verifierLancer(int desGarder[NB_DES])
{
    if (!verifierNombreDesGarder(desGarder) || arreterParJoueur || les valeurs de des obtenus sont déjà dans desGarder donc impossible de relancer)
    {
        for (size_t i = 0; i < NB_DES; i++)
        {
            if(desGarder[i] == 6) return true;
        }
        std::cout << "Vous n'avez pas garder de V" << std::endl;
    }
    
}
*/


int jouerJeu()
{
    int desObtenue[NB_DES];
    int desGarder[NB_DES] = {0};
    lancerDES(desObtenue);
    afficherDES(desObtenue);
    garderDES(desGarder, desObtenue);
    verifierNombreDesGarder(desGarder);
   // score();

}// FAIT QU'UN LANCER
