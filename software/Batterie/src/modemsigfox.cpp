#include "modemsigfox.h"

ModemSigfox::ModemSigfox():Sigfox(33, 32, false)
{

}

void ModemSigfox::envoyerTrame(int type, Battery bat)

{
    if(type == 0){

    }
    if(type == 1)
    {
        mesureBatterie trameBatterie;
        //trameBatterie = bat.CompositionTrame();

        if (envoyer((void*)&trameBatterie,sizeof(trameBatterie)))
        {
            Serial.println("Trame envoyée avec succès");
        }
        else{
            Serial.println("Problème envoi Sigfox");
        }
    }

}

ModemSigfox::~ModemSigfox()
{

}
