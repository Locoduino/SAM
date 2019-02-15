
/*
 * Locoduinodrome SAM
 */

/*
 * Les satellites
 */
#include "SAM.h"
#include "SignalFr.h"


/*
 *  Les aiguillages
 */
PointWrapper pointWrapper0(0, 2); /* aiguillage 0 de SAM sur satellite 2 */
PointWrapper pointWrapper1(1, 6); /* aiguillage 1 de SAM sur satellite 6 */

/*
 * Les signaux
 */
SemaphoreSignalWrapper                  S1wrapper(0, 4, SIGNAL_0); /* signal 0 de SAM sur satellite 4, slot 0 */
SemaphoreSignalWrapper                  S2wrapper(1, 3, SIGNAL_0); /* signal 1 de SAM sur satellite 3, slot 0 */
CarreSignalWrapper                      C3wrapper(4, 0, SIGNAL_0); /* signal 4 de SAM sur satellite 0, slot 0 */
CarreSignalWrapper                      C4wrapper(5, 1, SIGNAL_0); /* signal 5 de SAM sur satellite 1, slot 0 */
CarreSignalWrapper                      C5wrapper(6, 6, SIGNAL_0); /* signal 6 de SAM sur satellite 6, slot 0 */
CarreSignalWrapper                      C6wrapper(7, 2, SIGNAL_0); /* signal 7 de SAM sur satellite 2, slot 0 */
CarreRappelRalentissementSignalWrapper  C1wrapper(2, 7, SIGNAL_0); /* signal 2 de SAM sur satellite 7, slot 0 */
CarreRappelRalentissementSignalWrapper  C2wrapper(3, 5, SIGNAL_0); /* signal 3 de SAM sur satellite 5, slot 0 */
SemaphoreRalentissementSignalWrapper    S3wrapper(8, 3, SIGNAL_1); /* signal 8 de SAM sur satellite 3, slot 1 */
SemaphoreRalentissementSignalWrapper    S4wrapper(9, 4, SIGNAL_1); /* signal 9 de SAM sur satellite 4, slot 1 */

/*
 * Pour l'animation des signaux dans Loop
 */

unsigned long tempo;
int sig = 0;
unsigned int feu = 1;

///////////////////////////////////////////

void setup()
{
  Serial.begin(115200);

  SAM::begin();

  PointWrapper::begin();
  SignalWrapper::begin();

  tempo = millis();
}

///////////////////////////////////////////

void loop()
{

  SAM::loop();

  // une animation des signaux
  
  if (millis() - tempo > 500)
  {
    tempo = millis();
    Serial.print("signal ");Serial.print(sig);Serial.print(" feu ");Serial.println(feu);
    SignalWrapper::setSignalState(sig, feu);
    sig++;
    if (sig > 9) {
      sig = 0;
      feu = feu << 1;
      if (feu == 0) feu = 1;
    }
  }
}

// utilitaire de commande d'une aiguille a en position i

void Aiguille(int a, bool i)
{
  Serial.print("Aiguille ");Serial.println(a);
  PointWrapper::setPointPosition(a,i);
  printOutBuffers();
}

// utilitaire de commande d'un signal nsig avec un type de feux f

void Signal(int nsig, unsigned int f)
{
  switch (nsig)
  {
    case 0:
    case 1:
    Serial.print("Semaphore ");Serial.println(nsig);
    break;
    case 4:
    case 5:
    case 6:
    case 7:
    Serial.print("Carre ");Serial.println();
    break;
    case 2:
    case 3:
    Serial.print("CarreRappelRalentissement ");Serial.println(nsig);
    break;    
    case 8:
    case 9:
    Serial.print("SemaphoreRalentissement ");Serial.println(nsig);
    break;    
  }
  SignalWrapper::setSignalState(nsig, f);
  printOutBuffers();
}

///////////////////////////////////////////
