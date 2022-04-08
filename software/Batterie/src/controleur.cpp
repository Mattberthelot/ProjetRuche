#include "controleur.h"

Controleur::Controleur()
{
  laBatterie = new Battery();
  leModemSigfox = new ModemSigfox();
  leModemSigfox->begin();

    choixTrame = true;

}

void Controleur::RecupererDonneesBatterie()
{
    //lesMesuresBatterie = laBatterie->
}
