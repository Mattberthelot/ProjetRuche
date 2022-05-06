
/**
  @file :battery.cpp
  @author : Matt berthelot
  @date : 5 novembre 2021
  @details : La classe batterie devra recuperer les valeurs de la tension, du courant,de la puissance.
             Elle calculera la charge ainsi que le taux de charge de la batterie
             pour visualiser la charge et la décharge de la batterie.

*/

#include "battery.h"

/**
 * @brief Battery::Battery
 * @details: On initialise les varibales de la batterie
 */
Battery::Battery():
    Adafruit_INA219(),
    t0(0),
    t1(0),
    i0(0),
    i1(0),
    SOC(0),
    charge(0),
    capaciteMax(3000)
{
    pinMode(pin, OUTPUT);     // GPIO 13 en sortie
    digitalWrite(pin, HIGH);  // Fermeture du Mosfet charge de la batterie
}

/**
 * @brief Battery::getChargeLoop
 * @details : Calcule la charge de la batterie et arrête la charge
 *          si la température est inférieure à 0 ou si la batterie
 *          a une tension supérieure a 12.6 V à chaque seconde
 * @param temperature : Température ambiante
 * @return Valeur de la charge de la batterie à l'instant t1
 */
float Battery::getChargeLoop(float temperature){

    t1= millis();
    i1 = getCurrent_mA();

    charge += (i0+i1)*(t1-t0)/7200000;   //calcul de la charge trapèze

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

    Serial.print("La chargeLoop est de : ");Serial.print(charge);Serial.println(" mAh");
    return charge;
}
/**
 * @brief Battery::getChargeSetup
 * @details Calcule la charge de la batterie et arrête la charge
 *          si la température est inférieure à 0 ou si la batterie
 *          a une tension supérieure a 12.6 V
 * @param temperature : Température ambiante
 * @return Valeur de la charge de la batterie à l'instant t1
 *
 */

float Battery::getChargeSetup(float temperature)
{
    t1= millis();
    i1 = getCurrent_mA();


    charge += (i1*t1)/3600000;   //calcul de la charge rectangle


    if(charge>capaciteMax){  //la charge ne peut pas dépasser la capacité Max de la batterie
        charge= capaciteMax;
    }

    if(charge<0.0){    // la charge de ne peut pas etre negatif
        charge = 0.0;
    }
    // on arrete le charge si la temperature est en dessous de 0 ou la batterie a une tension superieur a 12.6
    if (getBusVoltage_V() > 12.6 || temperature < 0.0){
        digitalWrite(13, LOW);
    }
    // on reprend la charge si la température est positive et la batterie n'est pas charger a fond
    if (getBusVoltage_V() < 12.3 && temperature > 1.0){
        digitalWrite(13, HIGH);
    }

    Serial.print("La chargeSetup est de : ");Serial.print(charge);Serial.println(" mAh");
    return charge;
}
/**
 * @brief Battery::getCharge
 * @details : Obtiens la charge de la batterie et arrête la charge
 *            si la température est inférieure à 0 degré ou si la batterie
 *            a une tension supérieure à 12.6 V. On peux reprendre la charge si
 *            la tension est inférieur à 12.3 V et la température supérieur a 1 degré.
 * @param temperature : Température ambiante
 * @return Valeur de la charge de la batterie a linstant t0
 */
float Battery::getCharge(float temperature)
{
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
/**
 * @brief Battery::getTauxDeCharge
 * @details Obtenir le taux de charge de la batterie
 *          en prenant la charge divisée par la capacité maximum de la batterie * 100
 * @return Taux de charge en pourcentage
 */
float Battery::getTauxDeCharge(){


    SOC = charge/capaciteMax*100;// calcul du taux de charge

    Serial.print("La Taux de charge est de : ");
    Serial.print(SOC);Serial.println(" %");

    return SOC;
}

/**
 * @brief Battery::getTension
 * @details: Obtenir la tension de la batterie en V
 *           grâce a la fonction obtenir tension de l'INA219
 * @return Valeur de la tension de la batterie
 */
float Battery::getTension()
{
    float busvoltage = this->getBusVoltage_V();//Acquisition de la tension
    Serial.print("La tension est de : ");Serial.print(busvoltage);Serial.println(" V");
    return busvoltage;
}

/**
 * @brief Battery::getPuissance
 * @details: Obtenir la puissance de la batterie en mW
 *           grâce a la fonction obtenir puissance de l'INA219
 * @return Valeur de la puissance de la batterie
 */
float Battery::getPuissance()
{
    float power = this->getPower_mW();//Acquisition de la puissance
    Serial.print("La puissance est de : ");Serial.print(power);Serial.println(" mW");
    return power;
}
/**
 * @brief Battery::getCourant
 * @details: Obtenir le courant de la batterie en mA
 *           grâce a la fonction obtenir courant de l'INA219
 * @return Valeur du courant de la batterie
 */
float Battery::getCourant()
{

    float current = this->getCurrent_mA();//Acquisition du courant
    Serial.print("Le courant est de : ");Serial.print(current);Serial.println(" mA");
    return current;
}
/**
 * @brief Battery::init
 * @details: On calibre l'INA219 a 32V_1A et on initialise la mémoire de la batterie pour pouvoir
 *           aller chercher la charge dans la mémoire flash
 *           et si la charge n'est pas trouvée on lui donne la valeur 3000 par défault et on
 *           ferme la mémoire flash
 * @return  Test de démarrage de l'INA219
 */
bool Battery::init()
{
    setCalibration_32V_1A();
    preferences.begin("battery", false); //initialisation mémoire batterie
    charge = preferences.getFloat("charge", 3000.0);//récuperer la charge dans le mémoire flash et si on ne trouve pas on prend 3000
    preferences.end();
    bool res = begin();
    return res;
}
/**
 * @brief Battery::memoriserCharge
 * @details: Initialisation de la mémoire de la batterie
 *           et mémorise la charge de la batterie dans la mémoire flash
 */
void Battery::memoriserCharge()
{
    preferences.begin("battery", false); //initialisation mémoire batterie
    preferences.putFloat("charge",charge);//mémoriser la charge dans le mémoire flash
    preferences.end();
}
/**
 * @brief Battery::modifierCharge
 * @details : Modifier la valeur de la charge si elle est connu
 * @param charge : Charge de la batterie
 */
void Battery::modifierCharge(float charge)
{
    preferences.begin("battery", false); //initialisation mémoire batterie
        preferences.putFloat("charge",charge);//mémoriser la charge dans le mémoire flash
        preferences.end();
}
/**
 * @brief Battery::LireCharge
 * @details : Lire la charge de la batterie pour effectuer le calcul de perte de charge pendant l'endormissement de l'esp32
 * @return Charge de la batterie
 */
float Battery::LireCharge()
{
    preferences.begin("battery", false); //initialisation mémoire batterie
       float charge = preferences.getFloat("charge",0);//mémoriser la charge dans le mémoire flash
       preferences.end();

       this->charge = charge;

       return charge;
}


