#ifndef BATTERY_H
#define BATTERY_H
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Preferences.h>


class Battery: public Adafruit_INA219
{
public:
    Battery();
    float getCharge();
    float getTauxDeCharge();
    float getTension();
    float getPuissance();
    float getCourant();
    void memoriserCharge();

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
