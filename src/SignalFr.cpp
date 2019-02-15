/*
 * LOCODUINO
 *
 * Locoduinodrome SAM
 *
 * Classe de wrapping des satellites dans SAM.
 *
 * Ces classes permettent a SAM de s'interfacer à la messagerie
 * CAN lui permettant de dialoguer avec les satellites.
 */

#include "SAM.h"
#include "SignalFr.h"

/*-----------------------------------------------------------------------------
 * Wrapper pour les sémaphores : 3 feux, jaune, rouge, vert
 *
 * L'ordre des LED sur le satellite est :
 * - jaune
 * - rouge
 * - vert
 */
void SemaphoreSignalWrapper::setState(const uint16_t inState)
{
  if (mSatelliteIndex != NO_MESSAGE_INDEX) {
    AbstractCANOutSatelliteMessage &message = AbstractCANOutSatelliteMessage::outSatellitesMessages[mSatelliteIndex];
    message.setLED(mSlot, inState & A ? LED_ON : LED_OFF);      /* jaune */
    message.setLED(mSlot + 1, inState & S ? LED_ON : LED_OFF);  /* rouge */
    message.setLED(mSlot + 2, inState & Vl ? LED_ON : LED_OFF); /* vert  */
  }
}

/*-----------------------------------------------------------------------------
 * Wrapper pour les carrés
 *
 * L'ordre des LED sur le satellite est :
 * - jaune
 * - rouge
 * - vert
 * - rouge2
 * - oeilleton (blanc)
 */
void CarreSignalWrapper::setState(const uint16_t inState)
{
  if (mSatelliteIndex != NO_MESSAGE_INDEX) {
    AbstractCANOutSatelliteMessage &message = AbstractCANOutSatelliteMessage::outSatellitesMessages[mSatelliteIndex];
    message.setLED(mSlot, inState & A ? LED_ON : LED_OFF);        /* jaune */
    message.setLED(mSlot + 1, inState & S ? LED_ON : inState & C ? LED_ON : LED_OFF);    /* rouge */
    message.setLED(mSlot + 2, inState & Vl ? LED_ON : LED_OFF);   /* vert  */
    message.setLED(mSlot + 3, inState & C ? LED_ON : LED_OFF);    /* rouge2 */
    message.setLED(mSlot + 4, inState & C ? LED_OFF : inState ? LED_ON : LED_OFF); /* oeilleton */
  }
}

/*-----------------------------------------------------------------------------
 * Wrapper pour les s&maphores avec ralentissement
 *
 * L'ordre des LED sur le satellite est :
 * - jaune
 * - rouge
 * - vert
 * - jaune2
 * - jaune3
 */
void SemaphoreRalentissementSignalWrapper::setState(const uint16_t inState)
{
  if (mSatelliteIndex != NO_MESSAGE_INDEX) {
    AbstractCANOutSatelliteMessage &message = AbstractCANOutSatelliteMessage::outSatellitesMessages[mSatelliteIndex];
    message.setLED(mSlot, inState & A ? LED_ON : LED_OFF);      /* jaune */
    message.setLED(mSlot + 1, inState & S ? LED_ON : LED_OFF);  /* rouge */
    message.setLED(mSlot + 2, inState & Vl ? LED_ON : LED_OFF); /* vert  */
    message.setLED(mSlot + 3, inState & R ? LED_ON : inState & Rc ? LED_BLINK : LED_OFF);  /* jaune2 */
    message.setLED(mSlot + 4, inState & R ? LED_ON : inState & Rc ? LED_BLINK : LED_OFF);  /* jaune3 */
  }
}

/*-----------------------------------------------------------------------------
 * Wrapper pour les carrés avec rappel ralentissement
 *
 * L'ordre des LED sur le satellite est :
 * - jaune
 * - rouge
 * - vert
 * - rouge2
 * - jaune2
 * - jaune3
 * - oeilleton
 */
void CarreRappelRalentissementSignalWrapper::setState(const uint16_t inState)
{
  if (mSatelliteIndex != NO_MESSAGE_INDEX) {
    AbstractCANOutSatelliteMessage &message = AbstractCANOutSatelliteMessage::outSatellitesMessages[mSatelliteIndex];
    message.setLED(mSlot, inState & A ? LED_ON : LED_OFF);      /* jaune */
    message.setLED(mSlot + 1, inState & C ? LED_ON : LED_OFF);  /* rouge */
    message.setLED(mSlot + 2, inState & Vl ? LED_ON : LED_OFF); /* vert  */
    message.setLED(mSlot + 3, inState & C ? LED_ON : LED_OFF);  /* rouge2 */
    message.setLED(mSlot + 4, inState & RR ? LED_ON : inState & RRc ? LED_BLINK : LED_OFF);  /* jaune2 */
    message.setLED(mSlot + 5, inState & RR ? LED_ON : inState & RRc ? LED_BLINK : LED_OFF);  /* jaune3 */
    message.setLED(mSlot + 6, inState & C ? LED_OFF : inState ? LED_ON : LED_OFF); /* oeilleton */
  }
}
