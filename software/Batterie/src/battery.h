#ifndef BATTERY_H
#define BATTERY_H
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Preferences.h>

typedef struct{
    short int tension;
    short int courant;
    short int puissance;
    short int charge;
    unsigned char soc;
    char type;

}mesureBatterie;


class Battery: public Adafruit_INA219
{
public:
    Battery();
    float getCharge(float temperature);
    float getTauxDeCharge();
    float getTension();
    float getPuissance();
    float getCourant();
    void memoriserCharge();
    mesureBatterie CompositionTrame();

private:
    unsigned long t0;
    unsigned long t1;
    float i0;
    float i1;
    float SOC;
    float charge;
    float capaciteMax;
    Preferences preferences;
};

#endif // BATTERY_H
