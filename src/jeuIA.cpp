#include "jeuIA.h"
#include "ihm.h"
#include "donnees.h"
#include <ctime>   // pour time
#include <cstdlib> // pour srand

#ifdef DEBUG_JEUIA
#include <iostream>
#endif

void initialiserJeuIA(Jeu& jeu)
{
    srand(time(NULL));
    jeu.nbJoueursReels  = 0;
    jeu.nbJoueursTotaux = 0;
    saisirNombreDeJoueursIA(jeu.nbJoueursReels, jeu.nbJoueursTotaux, jeu.nbJoueursIA);

#ifdef DEBUG_JEUIA
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "Nombre de joueurs humains : " << jeu.nbJoueursReels << std::endl;
    std::cout << "Nombre total de joueurs : " << jeu.nbJoueursTotaux << std::endl;
#endif

    for(int i = 0; i < jeu.nbJoueursTotaux; ++i)
    {
        jeu.joueurs[i].estIA = (i >= jeu.nbJoueursReels);
        jeu.joueurs[i].nom =
          jeu.joueurs[i].estIA ? "IA " + std::to_string(i + 1) : std::to_string(i + 1);
        jeu.joueurs[i].scoreFinal = 0;
        jeu.joueurs[i].sommet     = 0;
    }

    creerLesPilesDesJoueurs(jeu.joueurs, jeu.nbJoueursTotaux);
    initialiserBrochette(jeu.plateau);
}

bool garderDesIA(Plateau& plateau, Joueur& joueur)
{
#ifdef DEBUG_JEUIA
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] "
              << std::endl;
#endif
    int  valeurGardee;
    bool dejaGardee = false;

    do
    {
        valeurGardee = choisirValeurDeIA(plateau, joueur);
#ifdef DEBUG_JEUIA
        std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
        std::cout << "valeurGardee : " << valeurGardee << std::endl;
#endif
        if(estPasDansLesDesLances(plateau, valeurGardee))
        {
            continue;
        }

        dejaGardee = estDejaGarde(valeurGardee, plateau.desGardes, NB_DES);
        if(dejaGardee)
        {
            continue;
        }

    } while(dejaGardee || estPasDansLesDesLances(plateau, valeurGardee));

    bool gardeEffectuee = false;
    int  nbDesGardes    = 0;

    for(int i = 0; i < plateau.desEnJeu; i++)
    {
        if(plateau.desObtenus[i] == valeurGardee)
        {
            for(size_t j = 0; j < NB_DES; j++)
            {
                if(plateau.desGardes[j] == 0)
                {
                    plateau.desGardes[j] = valeurGardee;
                    ++nbDesGardes;
                    gardeEffectuee = true;
                    break;
                }
            }
        }
    }

    plateau.desEnJeu -= nbDesGardes;

#ifdef DEBUG_JEUIA
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    std::cout << "desEnJeu = " << plateau.desEnJeu << std::endl;
#endif

    return gardeEffectuee;
}

int choisirValeurDeIA(Plateau& plateau, Joueur& joueur)
{
    int priorites[] = { ID_VERS,
                        VALEUR_PRIORITEES_IA::CINQ_IA,
                        VALEUR_PRIORITEES_IA::QUATRE_IA,
                        VALEUR_PRIORITEES_IA::TROIS_IA,
                        VALEUR_PRIORITEES_IA::DEUX_IA,
                        VALEUR_PRIORITEES_IA::UN_IA };

    bool versDejaChoisi = false;

    for(size_t i = 0; i < sizeof(priorites) / sizeof(priorites[0]); ++i)
    {
#ifdef DEBUG_JEUIA
        std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
        std::cout << "Je suis dans la boucle pour la valeur : " << priorites[i] << std::endl;
#endif
        int valeurChoisie = priorites[i];

        bool dejaGardee = estDejaGarde(valeurChoisie, plateau.desGardes, NB_DES);
        if(dejaGardee)
        {
            continue;
        }

        for(int j = 0; j < plateau.desEnJeu; ++j)
        {
            if(valeurChoisie == ID_VERS)
            {
                if(plateau.desObtenus[j] == ID_VERS && !versDejaChoisi)
                {
                    versDejaChoisi = true;
                    return valeurChoisie;
                }
            }
            else if(plateau.desObtenus[j] == valeurChoisie)
            {
                return valeurChoisie;
            }
        }
    }

    return -1;
}

bool reglesIA(Plateau& plateau, Joueur& joueur)
{
    int  score = calculerScore(plateau.desGardes);
    bool aUnV  = false;

    for(int i = 0; i < NB_DES; i++)
    {
        if(plateau.desGardes[i] == ID_VERS)
        {
            aUnV = true;
            if(score >= VALEUR_PICKOMINO_MIN)
            {
                return true;
            }
        }
    }

    if(aUnV && score >= VALEUR_PICKOMINO_MIN)
    {
        return true;
    }

    return false;
}

int jouerTourIA(Plateau& plateau, Joueur joueurs[], int nbJoueurs, Joueur& joueur)
{
    bool jeuActif = true;
    int  etatTour = LANCER_TERMINE;
    int  score    = 0;

    while(jeuActif)
    {
        lancerDes(plateau);
        afficherPlateau(plateau, joueur);
        afficherPile(joueurs, nbJoueurs);
        afficherScore(score);

        if(verifierLancerNul(plateau.desObtenus, plateau.desGardes, plateau.desEnJeu))
        {
            rendreDernierPickomino(joueur, plateau);
            afficherLancerNul();
            etatTour = LANCER_NUL;
            jeuActif = false;
        }
        else
        {
            garderDesIA(plateau, joueur);
            score = calculerScore(plateau.desGardes);
            afficherScore(score);
#ifdef DEBUG_JEUIA
            std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
            std::cout << "Le score est de : " << score << std::endl;
#endif
            if(reglesIA(plateau, joueur))
            {
                int pickomino = piocherPickomino(plateau, score, joueurs, nbJoueurs);
                if(pickomino != AUCUN_PICKOMINO)
                {
                    afficherPioche(pickomino);
                }
                jeuActif = false;
#ifdef DEBUG_JEUIA
                std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__
                          << "] ";
                std::cout << "Je respecte la règle et termine le tour." << std::endl;
#endif
            }
        }
    }

    return etatTour;
}

void jouerJeuIA()
{
    PartieClassement classement[MAX_PARTIES];
    int              nbParties = chargerClassement(classement, MAX_PARTIES);
    Jeu              jeu;
    initialiserJeuIA(jeu);

    creerLesPilesDesJoueurs(jeu.joueurs, jeu.nbJoueursTotaux);
    jeu.plateau.numeroJoueur = JOUEUR_DEBUT;
#ifdef DEBUG_JEUIA
    std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
    for(int i = 0; i < jeu.nbJoueursTotaux; i++)
    {
        std::cout << "joueur.nom" << i << ": " << jeu.joueurs[i].nom << std::endl;
    }
#endif
    do
    {
        initialiserPlateau(jeu.plateau, jeu.nbJoueursTotaux);
        Joueur& joueurActuel = jeu.joueurs[jeu.plateau.numeroJoueur];
        if(estJoueurIA(joueurActuel))
        {
#ifdef DEBUG_JEUIA
            std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
            std::cout << "Le joueur est une IA donc 'JouerTourIA'" << std::endl;
#endif
            jouerTourIA(jeu.plateau, jeu.joueurs, jeu.nbJoueursTotaux, joueurActuel);
        }
        else
        {
            jouerTour(jeu.plateau, jeu.joueurs, jeu.nbJoueursTotaux, joueurActuel);
        }
#ifdef DEBUG_JEUIA
        for(int i = 0; i < jeu.nbJoueursTotaux; ++i)
        {
            std::cout << "[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] ";
            std::cout << "Pile du joueur " << i << " : Sommet = " << jeu.joueurs[i].sommet
                      << std::endl;
        }
#endif
    } while(!estPartieFinie(jeu.plateau));
    calculerScoreFinal(jeu.joueurs, jeu.nbJoueursTotaux);
    afficherScoreFinal(jeu.joueurs, jeu.nbJoueursTotaux);
    int indexGagnant = trouverGagnant(jeu.joueurs, jeu.nbJoueursTotaux);
    afficherGagnant(jeu.joueurs[indexGagnant]);

    // Appel de la fonction
    ajouterPartieClassement(classement,
                            nbParties,
                            jeu.joueurs[indexGagnant].nom,
                            jeu.joueurs[indexGagnant].score);

    sauvegarderClassement(classement, nbParties);
}