#ifndef CONTROLEUR_H
#define CONTROLEUR_H
#include <Arduino.h>
#include "modemsigfox.h"
#include "battery.h"
#include "HardwareSerial.h"
class Controleur
{
public:
    Controleur();
     void RecupererDonneesBatterie();
     virtual ~Controleur();

private:
      mesureBatterie lesMesuresBatterie;
      float tension;
         float intensite;
         float tauxDeCharge;
         float charge;
         bool choixTrame;
         Battery *laBatterie;
         ModemSigfox *leModemSigfox;

};

#endif // CONTROLEUR_H
