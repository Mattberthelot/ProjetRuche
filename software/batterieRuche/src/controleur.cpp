#include "controleur.h"
#include <Arduino.h>
#include <iostream>
Controleur::Controleur()
{

}

trameBatterie Controleur::CompositionDeLaTrame(int type)
{
    trameBatterie laTrameBatterie;
    if(type==1){



        laTrameBatterie.tension = mesures.getTension()*100;
        laTrameBatterie.courant = mesures.getCourant()*100;
        laTrameBatterie.puissance = mesures.getPuissance()*100;
        laTrameBatterie.charge = mesures.getCharge()*100;
        laTrameBatterie.tauxDeCharge = mesures.getTauxDeCharge()*2;
        laTrameBatterie.type = '1';

    }
    return laTrameBatterie;
}

battery Controleur::getMesures() const
{
    return mesures;
}
