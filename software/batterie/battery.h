#ifndef BATTERY_H
#define BATTERY_H
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <cmath>

class Battery: public Adafruit_INA219
{
public:
    Battery();
    float getCharge();
    float getTauxDeCharge();
    float getTension();
    float getPuissance();
    float getCourant();

private:
     unsigned long t0;
     unsigned long t1;
     float i0;
     float i1;
     float SOC;
     float charge;
     float capaciteMax;
};

#endif // BATTERY_H
