#include "ihm.h"
#include <iostream>

int afficherDes(int desObtenue[NB_DES], int& desEnjeu)
{
    std::cout << "Des obtenue au lancer : ";
    for(size_t i = 0; i < desEnjeu; i++)
    {
        if(desObtenue[i] == 6)
            std::cout << "V ";
        else
            std::cout << desObtenue[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}