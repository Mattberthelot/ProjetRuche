/*
 * File:   main.cpp
 * Author: Matt berthelot
 *
 * Created on 5 novembre 2021, 17:42
 */

#include <Arduino.h>
#include "sigfox.h"
#include "scan.h"


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
int choix;
float tension;
float courant;
float puissance;
float charge;
float soc;

void afficherMenu(){
    Scan::effacer();
    Serial.println("Menu batterie, que souhaitez vous faire?");
    Serial.println("\n 1- Configurer les données de la trame\n");
    Scan::afficherPrompt("batterie");

}

void setup()
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.println("Setup done");

    do{
        afficherMenu();
        while(!Serial.available());
        choix = Serial.read();

        switch(choix){

        case'1':
            Scan::effacer();
            Serial.println("\n Donner la valeur de la tension \n");
            tension = Scan::lireFloat();

            Serial.println("\n Donner la valeur de la courant \n");
            courant = Scan::lireFloat();

            Serial.println("\n Donner la valeur de la puissance \n");
            puissance = Scan::lireFloat();

            Serial.println("\n Donner la valeur de la charge \n");
            charge = Scan::lireFloat();

            Serial.println("\n Donner la valeur de la soc \n");
            soc = Scan::lireFloat();

        }


    }while(choix!= '5');
    Scan::effacer();
    Serial.printf("Ctrl-C pour quitter\r\n");


    laTrameBatterie.tension = tension*100;
    laTrameBatterie.courant = courant/10;
    laTrameBatterie.puissance = puissance/10;
    laTrameBatterie.charge = charge;
    laTrameBatterie.soc = soc*2;
    laTrameBatterie.type = 2;
    delay(4000);

    Serial.println(laTrameBatterie.tension);
    Serial.println(laTrameBatterie.courant);
    Serial.println(laTrameBatterie.puissance);
    Serial.println(laTrameBatterie.charge);
    Serial.println(laTrameBatterie.soc);
    Serial.println(laTrameBatterie.type);





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
