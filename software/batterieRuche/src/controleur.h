#ifndef CONTROLEUR_H
#define CONTROLEUR_H
#include "battery.h"
#include <iostream>


struct trameBatterie{
    short int tension;
    short int courant;
    short int puissance;
    short int charge;
    unsigned char tauxDeCharge;
    char type;

};
class Controleur
{
public:
    Controleur();
    trameBatterie CompositionDeLaTrame(int type);

    battery getMesures() const;

private:
    battery mesures;

};

#endif // CONTROLEUR_H
