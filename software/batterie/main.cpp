#include <Arduino.h>
#include <battery.h>


int LED = 2;
Battery *laBattery;

void setup()
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.println("Setup done");
    laBattery = new Battery();

    if (! laBattery->begin()) {
        Serial.println("Impossible de trouver la carte batterie");
        while (1) { delay(10); }
    }

}

void loop()
{
    digitalWrite(LED, digitalRead(LED) ^1);   // turn the LED
    delay(500);                       // wait for 0.5 second
    digitalWrite(LED, digitalRead(LED) ^1);    // turn the LED
    delay(2000);    // wait for 2 seconds

    laBattery->getCourant();
    laBattery->getTension();
    laBattery->getPuissance();
    laBattery->getCharge();
    laBattery->getTauxDeCharge();



}
