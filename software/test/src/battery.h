#ifndef BATTERY_H
#define BATTERY_H
#include <Wire.h>
#include <Adafruit_INA219.h>



class Battery : public Adafruit_INA219
{
public:
    Battery();
    float getCharge();
    float getTauxDeCharge();
    float getTension();
    float getPuissance();
    float getCourant();

private:
     float i0;
     float i1;
     float charge;
     float capaciteMax;

};

#endif // BATTERY_H
