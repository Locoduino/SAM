/*
 * LOCODUINO
 *
 * Locoduinodrome SAM
 *
 * Config des satellites
 */

#ifndef __SAM_H__
#define __SAM_H__

#include "Messaging.h"
#include "Feux.h"
#include "CANMessage.h"
#include "SatelliteWrapper.h"

static const uint32_t NUMBER_OF_SATELLITES = 8;
static const uint32_t OUT_MESSAGE_PERIOD = 100;

class SAM
{
public:
	static void begin();
	static void loop();
};

#endif /* __SAM_H__ */
