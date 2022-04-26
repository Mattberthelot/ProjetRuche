/*
 * File:   main.cpp
 * Author: Matt
 *
 * Created on 5 novembre 2021, 17:42
 */

#include <Arduino.h>
#include <battery.h>
#include <sigfox.h>
#include <modemsigfox.h>



int LED = 2;
Battery *laBattery;
mesureBatterie laTrameBatterie;
Sigfox leSigfox(16,17,true);
ModemSigfox leModem;
bool booleen =true;

void setup()
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);

    laBattery = new Battery();
    if (! laBattery->begin()) {
        Serial.println("Impossible de trouver la carte batterie");//mise en pause si pas de batterie
        while (1) { delay(10); }
    }

    Serial.println("Setup done");

    laTrameBatterie=laBattery->CompositionTrame();

    leSigfox.begin();//demarrage sigfox

    leSigfox.envoyer((void*)&laTrameBatterie,sizeof (laTrameBatterie));//envoie de la trame
}

void loop()
{
    digitalWrite(LED, digitalRead(LED) ^1);   // turn the LED
    delay(200);                       // wait for 0.2 second
    digitalWrite(LED, digitalRead(LED) ^1);    // turn the LED
    delay(5000); // wait for 2 seconds

//affichage de la trame
//    Serial.println(laTrameBatterie.tension);
//    Serial.println(laTrameBatterie.courant);
//    Serial.println(laTrameBatterie.puissance);
//    Serial.println(laTrameBatterie.charge);
//    Serial.println(laTrameBatterie.soc);
//    Serial.println(laTrameBatterie.type);



}


