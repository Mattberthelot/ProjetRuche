#include <battery.h>

Battery::Battery() :
   Adafruit_INA219(),
   i0(0),
   i1(0),
   charge(0),
   capaciteMax(3000)
{

}

float Battery::getCharge(){
i1 = getCurrent_mA();
charge= (i0+i1)/2 *0.5;   //calcul de la charge
        i0 = i1; 

        if(charge>capaciteMax){
            charge= capaciteMax;
        }

        if(charge<0.0){
            charge = 0.0;
        }


        return charge;

}

float Battery::getTauxDeCharge(){

    return charge/capaciteMax*100; // calcul du taux de charge
}

float Battery::getTension()
{
    float busvoltage = laBattery->getBusVoltage_V();
    Serial.println("la tension est de : ");Serial.print(busvoltage);Serial.println(" V");
    return busvoltage;
}

float Battery::getPuissance()
{
    float power = laBattery->getPower_mW();
    Serial.println("la puissance est de : ");Serial.print(power);Serial.println(" mW");
    return power;
}

float Battery::getCourant()
{

    float current = laBattery->getCurrent_mA();
     Serial.println("le courant est de : ");Serial.print(current);Serial.println(" mA");
     return current;
}
