/*
 * LOCODUINO
 *
 * Locoduinodrome SAM
 *
 * Config des satellites
 */

#ifndef __SAM_H__
#define __SAM_H__

#define NO_SATELLITE_ID	255
#define NUMBER_OF_SATELLITES	8
#define OUT_MESSAGE_PERIOD	100
#define NO_MESSAGE_INDEX	255
#define NO_SATELLITE_INDEX	255

#include "Messaging.h"
#include "CANMessage.h"
#include "SatelliteWrapper.h"

class SAM
{
public:
	static void begin();
	static void loop();
};

#endif /* __SAM_H__ */
