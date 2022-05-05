/**
 * File:   main.cpp
 * Author: Matt berthelot
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


/**
 * @brief setup
 */
void setup()
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);

    laBattery = new Battery();
    if (! laBattery->init()) {
        Serial.println("Impossible de trouver la carte batterie");//mise en pause si pas de batterie
        while (1) { delay(1000); }
    }

    //leSigfox.begin();//demarrage sigfox

    Serial.println("Setup done");


    laTrameBatterie.tension =laBattery->getTension()*100;
    laTrameBatterie.courant =laBattery->getCourant();
    laTrameBatterie.puissance =laBattery->getPuissance();
    laTrameBatterie.charge = laBattery->getCharge(5.2)*10;
    laTrameBatterie.soc =laBattery->getTauxDeCharge()*2;
    laTrameBatterie.type = 2;

    Serial.println(laTrameBatterie.tension);
    Serial.println(laTrameBatterie.courant);
    Serial.println(laTrameBatterie.puissance);
    Serial.println(laTrameBatterie.charge);
    Serial.println(laTrameBatterie.soc);
    Serial.println(laTrameBatterie.type);


   // leSigfox.envoyer((void*)&laTrameBatterie,sizeof (laTrameBatterie));//envoie de la trame
delay(10000);
   laBattery->getChargeSetup(5.2);
    //memorisation de la charge
    laBattery->memoriserCharge();

}


void loop()
{
    digitalWrite(LED, digitalRead(LED) ^1);   // turn the LED
    delay(200);                       // wait for 0.2 second
    digitalWrite(LED, digitalRead(LED) ^1);    // turn the LED
    delay(5000);



}


