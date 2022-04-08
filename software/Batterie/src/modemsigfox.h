#ifndef MODEMSIGFOX_H
#define MODEMSIGFOX_H

#include "battery.h"
#include "sigfox.h"



class ModemSigfox:public Sigfox
{
public:
    ModemSigfox();
    void envoyerTrame(int type,Battery bat);
    virtual ~ModemSigfox();

private:

};

#endif // MODEMSIGFOX_H
