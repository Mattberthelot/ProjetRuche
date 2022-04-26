#include "battery.h"
#include <Arduino.h>


Battery::Battery():
    Adafruit_INA219(),
    t0(millis()),
    t1(0),
    i0(0),
    i1(0),
    SOC(0),
    charge(0),
    capaciteMax(3000)
{
    pinMode(13, OUTPUT);     // GPIO 13 en sortie
      digitalWrite(13, HIGH);  // Fermeture du Mosfet charge de la batterie
    preferences.begin("battery", false); //initialisation mémoire batterie
    charge = preferences.getFloat("charge", 3000);
}


float Battery::getCharge(float temperature){

    t1= millis();
    i1 = getCurrent_mA();

    charge += (i0+i1)*(t1-t0)/7200000;   //calcul de la charge

    i0 = i1;
    t0 = t1;

    if(charge>capaciteMax){  //la charge ne peut pas dépasser la capacité Max de la batterie
        charge= capaciteMax;
    }

    if(charge<0.0){    // la charge de ne peut pas etre negatif
        charge = 0.0;
    }
// on arrete le charge si la temperature est en dessous de 0 ou la batterie est charger a fond
    if (getBusVoltage_V() > 12.6 || temperature < 0.0){
          digitalWrite(13, LOW);
       }
 // on reprend la charge si la température est positive et la batterie n'est pas charger a fond
       if (getBusVoltage_V() < 12.3 && temperature > 1.0){
          digitalWrite(13, HIGH);
       }

    Serial.print("La charge est de : ");Serial.print(charge);Serial.println(" mAh");
    return charge;
}

float Battery::getTauxDeCharge(){


    SOC = charge/capaciteMax*100;// calcul du taux de charge
    float SOC = this->SOC;
    Serial.print("La Taux de charge est de : ");
    Serial.print(SOC);Serial.println(" %");

    return SOC;
}

float Battery::getTension()
{
    float busvoltage = this->getBusVoltage_V();
    Serial.print("La tension est de : ");Serial.print(busvoltage);Serial.println(" V");
    return busvoltage;
}

float Battery::getPuissance()
{
    float power = this->getPower_mW();
    Serial.print("La puissance est de : ");Serial.print(power);Serial.println(" mW");
    return power;
}

float Battery::getCourant()
{

    float current = this->getCurrent_mA();
    Serial.print("Le courant est de : ");Serial.print(current);Serial.println(" mA");
    return current;
}

void Battery::memoriserCharge()
{
    preferences.putFloat("charge",charge);
}

mesureBatterie Battery::CompositionTrame()
{

    mesureBatterie laTrameBatterie;
    //Trame batterie

    laTrameBatterie.tension = getTension()*100;
    laTrameBatterie.courant = getCourant()/10;
    laTrameBatterie.puissance =getPuissance()/10;
    laTrameBatterie.charge = getCharge(5.2)*1;
    laTrameBatterie.soc = getTauxDeCharge()*2;
    laTrameBatterie.type = '1';

    Serial.println(laTrameBatterie.tension);
    Serial.println(laTrameBatterie.courant);
    Serial.println(laTrameBatterie.puissance);
    Serial.println(laTrameBatterie.charge);
    Serial.println(laTrameBatterie.soc);
    Serial.println(laTrameBatterie.type);

//memorisation de la charge
    memoriserCharge();

    return laTrameBatterie;
}
