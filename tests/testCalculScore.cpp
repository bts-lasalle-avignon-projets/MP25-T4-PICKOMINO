#include "doctest.h"
#include "plateau.h"

TEST_CASE("Calcul Simple : ")
{
    int desGarder[8] = { 1, 2, 3, 4, 5, 5, 5, 4 };
    CHECK(calculerScore(desGarder) == 29);
}

TEST_CASE("Valeur Vers : ")
{
    int desGarder[8] = { ID_VERS };
    CHECK(calculerScore(desGarder) == 5);
}

TEST_CASE("Calcul aux limites n°1 : ")
{
    int desGarder[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    CHECK(calculerScore(desGarder) == 8);
}

TEST_CASE("Calcul aux limites n°2 : ")
{
    int desGarder[8] = { ID_VERS, ID_VERS, ID_VERS, ID_VERS, ID_VERS, ID_VERS, ID_VERS, ID_VERS };
    CHECK(calculerScore(desGarder) == 40);
}