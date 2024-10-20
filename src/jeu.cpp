#include "jeu.h"
#include "plateau.h"
#include "ihm.h"
#include <ctime>   // pour time
#include <cstdlib> // pour srand

#ifdef DEBUG_JEU
#include <iostream>
#endif

void initialiserJeu()
{
    srand(time(NULL));
    // @todo initialiser les données du jeu
}

void jouerJeu()
{
    Plateau plateau;

    initialiserJeu();

#ifdef SIMULATION
    initialiserPlateau(plateau);

    jouerTour(plateau);
#endif
}

void jouerTour(Plateau& plateau)
{
    bool continuer = true;

    while(continuer)
    {
        lancerDes(plateau);
        afficherPlateau(plateau);

        if(verifierLancerNul(plateau.desObtenus, plateau.desGardes, plateau.desEnJeu))
        {
            afficherLancerNul();
            break;
        }

        bool gardeReussi = garderDes(plateau);

        if(!gardeReussi)
        {
            afficherValeurDejaGardee();
        }

        afficherScore(calculerScore(plateau.desGardes));

        continuer = demander("continuer à lancer des dés");
    }
    /*
    if(!contientV(plateau.desGardes))
    {

    }
    */

    afficherLancerArrete();
}
