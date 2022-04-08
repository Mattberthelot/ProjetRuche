/*
 * File:   main.cpp
 * Author: philippe
 *
 * Created on 5 novembre 2021, 17:42
 */

#include <Arduino.h>
#include "sigfox.h"


int LED = 2;

typedef struct{
    short int tension= 300;
    short int courant = 2 ;
    short int puissance = 50;
    short int charge = 1000;
    unsigned char soc= 10;
    char type=1;

}mesureBatterie;

Sigfox leSigfox(26,27,true);
mesureBatterie laTrameBatterie;
void setup()
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.println("Setup done");

    leSigfox.envoyer((void*)&laTrameBatterie,sizeof (laTrameBatterie));


}

void loop()
{
    digitalWrite(LED, digitalRead(LED) ^1);   // turn the LED
    delay(200);                       // wait for 0.2 second
    digitalWrite(LED, digitalRead(LED) ^1);    // turn the LED
    delay(2000);  // wait for 2 seconds



}
