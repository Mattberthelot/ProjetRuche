/*
 * File:   main.cpp
 * Author: Matt berthelot
 *
 * Created on 5 novembre 2021, 17:42
 */

#include <Arduino.h>
#include "sigfox.h"


int LED = 2;

typedef struct{
    short int tension;
    short int courant;
    short int puissance;
    short int charge;
    short int field6 = 0;
    unsigned char soc;
    char type;

}mesureBatterie;

Sigfox leSigfox;

mesureBatterie laTrameBatterie;



void setup()
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.println("Setup done");
    laTrameBatterie.tension = 15;
    laTrameBatterie.courant = 100;
    laTrameBatterie.puissance = 200;
    laTrameBatterie.charge = 3000;
    laTrameBatterie.soc = 100;
    laTrameBatterie.type = 2;
    delay(4000);


    leSigfox.begin();

    leSigfox.envoyer((void*)&laTrameBatterie,sizeof (laTrameBatterie));


}

void loop()
{
    digitalWrite(LED, digitalRead(LED) ^1);   // turn the LED
    delay(200);                       // wait for 0.2 second
    digitalWrite(LED, digitalRead(LED) ^1);    // turn the LED
    delay(2000);  // wait for 2 seconds



}
