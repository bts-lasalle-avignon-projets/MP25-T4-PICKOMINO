#ifndef DONNEES_H
#define DONNEES_H

#define NB_FACES           6
#define NB_DES             8
#define ID_VERS            6
#define VALEUR_VERS        5
#define VALEUR_DE_INCONNUE -1

#define NB_JOUEURS_MAX        7
#define NB_JOUEURS_MIN        2
#define JOUEUR_DEBUT          1
#define NB_JOUEURS_MAX_JEU_IA 6

#define NB_PICKOMINOS        16
#define VALEUR_PICKOMINO_MIN 21
#define VALEUR_PICKOMINO_MAX 36

#define AUCUN_PICKOMINO -1

enum VALEUR_PRIORITEES_IA

{
    UN_IA     = 1,
    DEUX_IA   = 2,
    TROIS_IA  = 3,
    QUATRE_IA = 4,
    CINQ_IA   = 5
};

enum NB_VERS_PICKOMINO

{
    UN_VER      = 1,
    DEUX_VERS   = 2,
    TROIS_VERS  = 3,
    QUATRE_VERS = 4
};

enum LIMITE_PICKOMINO
{
    VALEUR_PICKOMINO_MAX_UN_VER     = 24,
    VALEUR_PICKOMINO_MAX_DEUX_VERS  = 28,
    VALEUR_PICKOMINO_MAX_TROIS_VERS = 32
};

#endif
