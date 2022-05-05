#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Preferences.h>


typedef struct{
    short int tension;
    short int courant;
    short int puissance;
    short int charge;
    short int field6 = 0;
    unsigned char soc;
    char type;

}mesureBatterie;


class Battery: public Adafruit_INA219
{
public:
    Battery();
    float getChargeLoop(float temperature);
    float getChargeSetup(float temperature);
    float getCharge(float temperature);
    float getTauxDeCharge();
    float getTension();
    float getPuissance();
    float getCourant();
    bool  init();
    void memoriserCharge();



private:
   // unsigned long t0; /// Mesure prise a l'insant 0
    unsigned long t1;/// Mesure prise a l'instant t1 apès l'envoie sigfox
   // float i0; //// Valeur du courant a l'instant t0
    float i1; /// Valeur du courant au point t1
    float SOC; /// Valeur du taux de charge de la batterie
    float charge;/// Valeur de la charge de la batterie
    float capaciteMax;///Capacite maximum de la batterie
    Preferences preferences;/// Permet la sauvegarde dans la mémoire flash
    const int pin=13; /// Initialisation de la pin GPIO13
};

#endif // BATTERY_H
