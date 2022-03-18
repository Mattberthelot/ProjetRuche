#include "battery.h"

battery::battery() :
    Adafruit_INA219(),
    t0(0),
    t1(0),
    i0(0),
    i1(0),
      SOC(0),
    charge(0),
    capaciteMax(3000)
{

}


float battery::getCharge(){
i1 = getCurrent_mA();
charge += (i0+i1)/2 *0.5;   //calcul de la charge
        i0 = i1;






        if(charge>capaciteMax){
            charge= capaciteMax;
        }

        if(charge<0.0){
            charge = 0.0;
        }

   float charge = this->charge;
  Serial.print("La charge est de : ");Serial.print(charge);Serial.println(" Ah");
        return charge;

}

float battery::getTauxDeCharge(){


SOC = charge/capaciteMax*100;// calcul du taux de charge
float SOC = this->SOC;
Serial.print("La Taux de charge est de : ");Serial.print(SOC);Serial.println(" %");

    return SOC;
}

float battery::getTension()
{
    float busvoltage = this->getBusVoltage_V();
    Serial.print("La tension est de : ");Serial.print(busvoltage);Serial.println(" V");
    return busvoltage;
}

float battery::getPuissance()
{
    float power = this->getPower_mW();
    Serial.print("La puissance est de : ");Serial.print(power);Serial.println(" mW");
    return power;
}

float battery::getCourant()
{

    float current = this->getCurrent_mA();
     Serial.print("Le courant est de : ");Serial.print(current);Serial.println(" mA");
     return current;
}



