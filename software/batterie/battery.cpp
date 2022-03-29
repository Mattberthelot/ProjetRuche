#include "battery.h"

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

}

float Battery::getCharge(){

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
