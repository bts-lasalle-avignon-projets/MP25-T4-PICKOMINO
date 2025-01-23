#include "ihm.h"
#include "donnees.h"

#include <iostream>
#include <string>

int saisirNombreDeJoueurs()
{
    int nombreDeJoueurs;

    do
    {
        std::cout << "Veuillez indiquer le nombre de joueurs (entre " << NB_JOUEURS_MIN << " et "
                  << NB_JOUEURS_MAX << ") : ";
        std::cin >> nombreDeJoueurs;
        std::cout << std::endl;
    } while(nombreDeJoueurs < NB_JOUEURS_MIN || nombreDeJoueurs > NB_JOUEURS_MAX);

    return nombreDeJoueurs;
}

void afficherPlateau(Plateau& plateau, Joueur& joueur)
{
    afficherJoueur(joueur);
    afficherBrochette(plateau.pickominos);
    afficherDes(plateau.desObtenus, plateau.desEnJeu);
    afficherDesGardes(plateau.desGardes, NB_DES - plateau.desEnJeu);
}

void afficherPile(Joueur joueurs[], int nbJoueurs)
{
    for(int numeroJoueur = 0; numeroJoueur < nbJoueurs; numeroJoueur++) // Iterer sur chaque joueur
    {
        if(joueurs[numeroJoueur].sommet <= 0) // Si le joueur n'a pas de pile
        {
            std::cout << "La pile du joueur " << joueurs[numeroJoueur].nom << " est vide."
                      << std::endl;
        }
        else // Si le joueur a des éléments dans sa pile
        {
            std::cout << "Pile du joueur " << joueurs[numeroJoueur].nom << ": ";
            for(int i = 0; i < joueurs[numeroJoueur].sommet;
                i++) // Affiche chaque élément de la pile
            {
                std::cout << joueurs[numeroJoueur].pilePickominos[i] << " ";
            }
            std::cout << std::endl;
        }
    }
}

void afficherJoueur(Joueur& joueur)
{
    std::cout << "Joueur " << joueur.nom << std::endl;
}

void afficherBrochette(EtatPickomino pickominos[NB_PICKOMINOS])
{
    std::cout << "Brochette :";
    for(int i = 0; i < NB_PICKOMINOS; i++)
    {
        if(pickominos[i] == EtatPickomino::DISPONIBLE)
        {
            std::cout << " " << (i + VALEUR_PICKOMINO_MIN);
        }
        else if(pickominos[i] == EtatPickomino::RETOURNE)
        {
            std::cout << " X";
        }
    }
    std::cout << std::endl;
}

void afficherDes(int desObtenus[NB_DES], int nbDes)
{
    std::cout << "Lancer des dés : ";
    for(int i = 0; i < nbDes; i++)
    {
        std::cout << (desObtenus[i] == ID_VERS ? "V" : std::to_string(desObtenus[i])) << " ";
    }
    std::cout << std::endl << std::endl;
}

void afficherDesGardes(int desGardes[NB_DES], int nbDes)
{
    std::cout << "Dés gardés : ";
    if(nbDes == 0)
    {
        std::cout << "aucun";
    }
    else
    {
        for(int i = 0; i < nbDes; i++)
        {
            if(desGardes[i] != 0)
            {
                std::cout << (desGardes[i] == ID_VERS ? "V" : std::to_string(desGardes[i])) << " ";
            }
        }
    }

    std::cout << std::endl;
}

void afficherScore(int score)
{
    std::cout << "Votre score : " << score << std::endl;
}

void afficherPioche(int pickomino)
{
    std::cout << "Vous piochez : " << pickomino << std::endl << std::endl;
}

void afficherPicorer(int pickomino)
{
    std::cout << "Vous picorez : " << pickomino << std::endl << std::endl;
}

void afficherErreurEntree()
{
    std::cout << "Entrée invalide !" << std::endl;
}

void afficherErreurDeveloppement()
{
    std::cout << "En cours de développement !" << std::endl;
}

void afficherBienvenue()
{
    std::cout << "Pickomino version " << VERSION << std::endl << std::endl;
}

void afficherValeurDejaGardee()
{
    std::cout << "Vous avez déjà gardé cette valeur !" << std::endl;
}

void afficherTousDesGardes()
{
    std::cout << "Tous les dés sont gardés ! Aucune relance." << std::endl;
}

void afficherLancerArrete()
{
    std::cout << "Vous ne pouvez plus relancer !" << std::endl;
}

void afficherLancerNul()
{
    std::cout << "Le lancer est nul !" << std::endl << std::endl;
}

void afficherScoreFinal(Joueur joueurs[], int nbjoueurs)
{
    for(int i = 0; i < nbjoueurs; i++)
    {
        std::cout << "Score final du joueur" << i + 1 << " : " << joueurs[i].score << std::endl;
    }
}

void afficherErreurValeurIndisponible()
{
    std::cout << "La valeur choisie n'est pas disponible parmi les dés lancés. Essayez encore."
              << std::endl;
}

void afficherGagnant(Joueur joueur)
{
    std::cout << "Le gagnant est : " << joueur.nom << std::endl;
}

void demanderNomJoueur(Joueur joueurs[], int nbJoueurs)
{
    for(int i = 0; i < nbJoueurs; i++)
    {
        std::cout << "Saisir le pseudo du joueur " << (i + 1) << " : ";
        std::cin >> joueurs[i].nom;
    }
}

char demanderValeurDe()
{
    char valeur;

    do
    {
        std::cout << "Choisir une valeur à garder : ";
        std::cin >> valeur;
    } while((valeur < '1' || valeur > '5') && valeur != 'V' && valeur != 'v');

    return valeur;
}

bool demander(const std::string& message)
{
    char              reponse;
    const std::string choixValides = "on";

    do
    {
        std::cout << "Voulez-vous " << message << " ? (oO/nN) ";
        std::cin >> reponse;
        std::cout << std::endl;
        reponse = tolower(reponse);
    } while(choixValides.find(reponse) == std::string::npos);

    return (reponse == 'o' || reponse == 'O');
}

void afficherMenu()
{
    afficherBienvenue();
    afficherLogo();

    std::cout << " ------------ Choisir un mode de jeu ------------ " << std::endl;
    std::cout << "1. Jouer en LAN" << std::endl;
    std::cout << "2. Jouer contre IA" << std::endl;
    std::cout << "3. Afficher classement" << std::endl;
    std::cout << "4. Afficher les règles" << std::endl;
    std::cout << "5. Quitter Pickomino" << std::endl << std::endl;

    int choixUtilisateur;

    do
    {
        std::cout << "Votre Choix : ";
        std::cin >> choixUtilisateur;
        choisirModeDeJeu(choixUtilisateur);
    } while(choixUtilisateur >= 2 && choixUtilisateur <= 4);
}

void choisirModeDeJeu(int choixUtilisateur)
{
    PartieClassement classement[MAX_PARTIES];
    int              nbParties = chargerClassement(classement, MAX_PARTIES);

    switch(choixUtilisateur)
    {
        case 1:
            jouerJeu();
            break;
        case 2:
            afficherErreurDeveloppement();
            break;
        case 3:
            afficherClassement(classement, nbParties);
            break;
        case 4:
            afficherErreurDeveloppement();
            break;
        case 5:
            break;
        default:
            std::cout << "Choix invalide. Veuillez réessayer.\n";
            break;
    }
}

void afficherLogo()
{
    // Définir la couleur jaune avec les séquences d'échappement ANSI
    const std::string yellow = "\033[33m"; // Code ANSI pour jaune
    const std::string reset  = "\033[0m";  // Réinitialise la couleur

    // Texte à afficher
    const std::string text = R"(
   
                                              
▗▄▄▖▗▄▄▄▖ ▗▄▄▖▗▖ ▗▖ ▗▄▖ ▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖ ▗▄▖ 
▐▌ ▐▌ █  ▐▌   ▐▌▗▞▘▐▌ ▐▌▐▛▚▞▜▌  █  ▐▛▚▖▐▌▐▌ ▐▌
▐▛▀▘  █  ▐▌   ▐▛▚▖ ▐▌ ▐▌▐▌  ▐▌  █  ▐▌ ▝▜▌▐▌ ▐▌
▐▌  ▗▄█▄▖▝▚▄▄▖▐▌ ▐▌▝▚▄▞▘▐▌  ▐▌▗▄█▄▖▐▌  ▐▌▝▚▄▞▘

                                                                                     
)";

    // Afficher le texte en jaune
    std::cout << yellow << text << reset << std::endl;
}

void afficherClassement(PartieClassement classement[], int nbParties)
{
    if(verifierFichierVide())
    {
        system("clear");
        std::cout << "Il n'y a aucune partie de sauvegarder !" << std::endl;
    }
    else
    {
        system("clear");
        std::cout << "Classement des meilleures parties :\n";
        for(int i = 0; i < nbParties; i++)
        {
            std::cout << i + 1 << ". " << classement[i].nomJoueur << " - " << classement[i].score
                      << " points\n";
        }
    }
    retournerAuMenu();
}

void retournerAuMenu()
{
    char choixUtilisateur;
    std::cout << "Retourner au Menu (oO)";
    std::cin >> choixUtilisateur;
    switch(choixUtilisateur)
    {
        case 'o':
        case 'O':
            afficherMenu();
        default:
            break;
    }
}
