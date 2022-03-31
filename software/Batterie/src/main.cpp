/*
 * File:   main.cpp
 * Author: Matt
 *
 * Created on 5 novembre 2021, 17:42
 */

#include <Arduino.h>
#include <battery.h>


typedef struct{
    short int tension;
    short int courant;
    short int puissance;
    short int charge;
    unsigned char soc;
    char type;

}mesureBatterie;

int LED = 2;
Battery *laBattery;
mesureBatterie laTrameBatterie;

void setup()
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);

    laBattery = new Battery();
    if (! laBattery->begin()) {
        Serial.println("Impossible de trouver la carte batterie");
        while (1) { delay(10); }
    }

    Serial.println("Setup done");

}

void loop()
{
    digitalWrite(LED, digitalRead(LED) ^1);   // turn the LED
    delay(200);                       // wait for 0.2 second
    digitalWrite(LED, digitalRead(LED) ^1);    // turn the LED
    delay(5000); // wait for 2 seconds




    laTrameBatterie.tension = laBattery->getTension()*100;
    laTrameBatterie.courant = laBattery->getCourant()/10;
    laTrameBatterie.puissance = laBattery->getPuissance()/10;
    laTrameBatterie.charge = laBattery->getCharge()*1;
    laTrameBatterie.soc = laBattery->getTauxDeCharge()*2;
    laTrameBatterie.type = '1';

    laBattery->memoriserCharge();

    Serial.println(laTrameBatterie.tension);
    Serial.println(laTrameBatterie.courant);
    Serial.println(laTrameBatterie.puissance);
    Serial.println(laTrameBatterie.charge);
    Serial.println(laTrameBatterie.soc);
    Serial.println(laTrameBatterie.type);


}
