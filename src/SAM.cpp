/*
 * LOCODUINO
 *
 * Locoduinodrome SAM
 *
 * Config des satellites
 */

#include "SAM.h"
#include "mcp_can.h"
#include "mcp_can_dfs.h"

extern MCP_CAN canController;

// CAN interrupt routine
volatile bool FlagReceive = false;      // can interrupt flag
void MCP2515_ISR() {FlagReceive = true;}

void SAM::begin()
{
 // init CAN

  canController.start();
  
 /*
  * set mask & filters
  */
  
  canController.init_Mask(0, 0, 0x3F0);               // there are 2 mask in mcp2515, you need to set both of them
  canController.init_Mask(1, 0, 0x3F0);               // precisement : Id 0x10 à 0x4F
  // filtres du buffer 0
  canController.init_Filt(0, 0, 0x10);                // Reception possible : Id 10 & 1F (hex)  : Satellites
  canController.init_Filt(1, 0, 0x40);                // Reception possible : Id 4x (hex) 
  // filtres du buffer 1
  canController.init_Filt(2, 0, 0x10);                // Reception possible : Id 1x (hex) 
  canController.init_Filt(3, 0, 0x40);                // Reception possible : Id 4x (hex) 40 conduite via centrale DCC
  canController.init_Filt(4, 0, 0x43);                // Reception possible : Id 4x (hex) 43 keepalive
  canController.init_Filt(5, 0, 0x48);                // Reception possible : Id 4x (hex) 48 etat DCC
  
  while (CAN_OK != canController.begin(CAN_500KBPS))              // init can bus : baudrate = 500k (carte NiRem a 16 Mhz)
  {
    Serial.println("CAN BUS Shield init fail");
    delay(100);
  }
  Serial.println("CAN BUS Shield init ok!");
  attachInterrupt(0, MCP2515_ISR, FALLING); // start interrupt

  Serial.println("Initial");
  printOutBuffers();
}
	
void SAM::loop()
{
  // réception d'un message Can

  if(FlagReceive)                      // test si message
  {
    FlagReceive=0;
    if (CAN_MSGAVAIL == canController.checkReceive())            // check if data coming
    {
  		unsigned char len = 0;
		  unsigned char buf[8];

      canController.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf
      unsigned int canId = canController.getCanId();
      Serial.print(" ID: 0x");
      Serial.print(canId, HEX);
      Serial.print(" data:");
      for(int i = 0; i<len; i++)    // print the data
      {
        Serial.print(" 0x");
        Serial.print(buf[i], HEX);
      }
      Serial.println();
    }
  }

  sendSatelliteMessage();
}
