#ifndef SIGFOX_H
#define SIGFOX_H


#include "Arduino.h"
#include <HardwareSerial.h>

class Sigfox
{
  public:

    Sigfox(uint8_t rxPin=26, uint8_t txPin=27, bool debugEn=true);

    String tester(void);
    void begin(void);

    String   obtenirID(void);
    String   obtenirPAC(void);
    uint16_t obtenirTemp(void);

    bool envoyer(const void* data, uint8_t size);

  private:
    uint8_t rx, tx;
    HardwareSerial *serialSig;
    bool debug;
    String obtenirData(void);

};

#endif // SIGFOX_H
