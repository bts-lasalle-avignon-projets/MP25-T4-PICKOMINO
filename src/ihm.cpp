#include "ihm.h"
#include <iostream>
#include <string>

void afficherDemandeValeur() {
    std::cout << "Choisir une valeur à garder : ";
}

void afficherErreurEntree() {
    std::cout << "Entrée invalide. Veuillez réessayer." << std::endl;
}

void afficherValeurDejaGardee() {
    std::cout << "Vous avez déjà gardé cette valeur." << std::endl;
}

int demanderValeur() {
    char valeur;
    std::cout << "Choisir une valeur à garder : ";
    std::cin >> valeur;
    return valeur;
}

void afficherDesGardes(int desGarder[], int taille) {
    std::cout << "Vous avez gardé : ";
    for (int i = 0; i < taille; i++) {
        if (desGarder[i] != 0) {
            std::cout << (desGarder[i] == 6 ? "V" : std::to_string(desGarder[i])) << " ";
        }
    }
    std::cout << std::endl << std::endl;
}

void afficherTousDesGardes() {
    std::cout << "Tous les dés sont gardés. Aucune relance." << std::endl;
}

void afficherDes(int desObtenue[], int taille) {
    std::cout << "Dés obtenus au lancer : ";
    for (int i = 0; i < taille; i++) {
        std::cout << (desObtenue[i] == 6 ? "V" : std::to_string(desObtenue[i])) << " ";
    }
    std::cout << std::endl;
}

void afficherLancerArrete() {
    std::cout << "Vous ne pouvez plus relancer. Le jeu est arrêté." << std::endl;
}

void afficherJeuNul() {
    std::cout << "Le lancer est nul, vous ne pouvez pas gagner." << std::endl;
}

bool demanderContinuer() {
    char reponse;
    do {
        std::cout << "Voulez-vous continuer à jouer ? (o/n) : ";
        std::cin >> reponse;

        // Vérifier si la réponse est valide
        if (reponse == 'o' || reponse == 'O') {
            return true; // Le joueur veut continuer
        } else if (reponse == 'n' || reponse == 'N') {
            return false; // Le joueur veut arrêter
        } else {
            std::cout << "Réponse invalide. Veuillez entrer 'o' pour oui ou 'n' pour non." << std::endl;
        }
    } while (true); // Continuer à demander jusqu'à obtenir une réponse valide
}