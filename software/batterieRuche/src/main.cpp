#include <Arduino.h>
#include <battery.h>
#include <controleur.h>

using namespace std;
int LED = 2;
Controleur leControleur;

void setup()
{
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    Serial.println("Setup done");

    if (! leControleur.getMesures().begin()) {
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

trameBatterie t = leControleur.CompositionDeLaTrame(1);
Serial.println(t.tension);
Serial.println(t.courant);
Serial.println(t.puissance);
Serial.println(t.charge);
Serial.println(t.tauxDeCharge);
Serial.println(t.type);



}
