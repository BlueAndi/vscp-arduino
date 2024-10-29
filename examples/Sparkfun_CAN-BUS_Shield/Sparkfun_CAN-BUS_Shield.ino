/* The MIT License (MIT)
 * 
 * Copyright (c) 2014 - 2020, Andreas Merkle
 * http://www.blue-andi.de
 * vscp@blue-andi.de
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

#include <VSCP.h>       // VSCP framework
#include <SPI.h>        // SPI used for CAN controller communication
#include <MCP2515.h>    // CAN controller driver

// Create an instance of the VSCP framework
VSCP  vscp;

// Node is in active state or not
static bool isActive = false;

// Read a message from the transport layer, e.g. the CAN bus
// If no message is received return false, otherwise true.
bool transportRead(vscp_RxMessage * const rxMsg) {
  
  bool    status   = false;
  CANMSG  canMsg;
  
  // Any CAN frame received?
  if (true == MCP2515::receiveCANMessage(&canMsg, 10)) {
    
    // Is it a extended CAN frame?
    if (true == canMsg.isExtendedAdrs) {
    
      unsigned char index = 0;
    
      rxMsg->vscpClass  = (uint16_t)((canMsg.adrsValue >> 16) & 0x01ff);
      rxMsg->vscpType   = (uint8_t)((canMsg.adrsValue >> 8) & 0x00ff);
      rxMsg->oAddr      = (uint8_t)((canMsg.adrsValue >> 0) & 0x00ff);
      rxMsg->hardCoded  = (uint8_t)((canMsg.adrsValue >> 25) & 0x0001);
      rxMsg->priority   = (VSCP_PRIORITY)((canMsg.adrsValue >> 26) & 0x0007);
      rxMsg->dataSize   = canMsg.dataLength;
      
      // Protect against a buffer out of bounce access
      if (VSCP_L1_DATA_SIZE < rxMsg->dataSize) {
      
        rxMsg->dataSize = VSCP_L1_DATA_SIZE;
      }
      
      // Copy payload
      for(index = 0; index < rxMsg->dataSize; ++index) {
      
        rxMsg->data[index] = canMsg.data[index];
      }
            
      status = true;
    }
  }
  
  return status;
}

// Write a message to the transport layer, e.g. the CAN bus
// If it fails to send the message return false, otherwise true.
bool transportWrite(vscp_TxMessage const * const txMsg) {
  
  bool          status    = false;
  CANMSG        canMsg;
  unsigned char index     = 0;
  unsigned char retryCnt  = 0;
  
  canMsg.isExtendedAdrs = true;
  
  canMsg.adrsValue = (((uint32_t)txMsg->priority)  << 26) |
                     (((uint32_t)txMsg->hardCoded) << 25) |
                     (((uint32_t)txMsg->vscpClass) << 16) |
                     (((uint32_t)txMsg->vscpType)  <<  8) |
                     txMsg->oAddr;
                     
  canMsg.rtr = 0;
  
  canMsg.dataLength = txMsg->dataSize;
  
  for(index = 0; index < canMsg.dataLength; ++index) {
  
    canMsg.data[index] = txMsg->data[index];
  }
  
  do {
    
    // Before any retry, wait some time
    if (0 < retryCnt)
    {
      delay(100);
    }
    
    // Send CAN message
    if (false == MCP2515::transmitCANMessage(canMsg, 10)) {
      
      // CAN message couldn't be sent, try again.
      ++retryCnt;
    }
    // Successl sent
    else {
      status = true;
    }
  
  } while((false == status) && (0 < retryCnt));
    
  return status;
}

// Execute a action which was triggered by the decision matrix
void actionExecute(unsigned char action, unsigned char par, vscp_RxMessage const * const msg) {

    if (NULL == msg) {
        return;
    }

    switch(action)
    {
    // Implement your code here ...
    
    default:
        break;
    }

    return;
}

void setup() {

  unsigned char retry   = 3;      // Max. number of retries for CAN controller initialization
  bool          isError = false;  // Error flag

  // Set the baudrate of the serial connection to the PC
  Serial.begin(115200);
  Serial.println("VSCP node starts up ...");
  
  do {
    // Initialize CAN controller with 125 kbit/s (VSCP default bitrate)
    if (false == MCP2515::initCAN(CAN_BAUD_125K)) {

        // Try again
        delay(100);
        --retry;
        
        if (0 == retry) {
          isError = true;
        }

    } else {
    
        // Successful initialized
        retry = 0;
    }
    
  } while(0 < retry);
  
  if (true == isError) {
  
    Serial.println("Failed to initialize CAN controller!");
  
  }
  // Set to normal mode non single shot
  else if (false == MCP2515::setCANNormalMode(LOW)) {
  
    Serial.println("Failed to set CAN controller to normal mode!");
  
  } else {
  
    Serial.println("CAN controller initialized successful.");
  
    // Node GUID - Used to unique identify nodes
    VSCPGuid  nodeGuid = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
      
    // Setup VSCP framework
    vscp.setup(
      8,              // Status lamp pin
      7,              // Init button pin
      nodeGuid,       // Node GUID,
      255,            // Node zone (255 = all zones)
      255,            // Node sub-zone (255 = all sub-zones)
      transportRead,  // VSCP framework calls it to read a message
      transportWrite, // VSCP framework calls it to write a message
      actionExecute   // VSCP framework calls it to execute action
    );
    
  }
  
}

void loop() {

  // Process the VSCP framework
  vscp.process();

  // Send and receive VSCP messages only in active state
  if (true == vscp.isActive()) {
  
    vscp_RxMessage  rxMsg;  // Receive message
    vscp_TxMessage  txMsg;  // Transmit message
    
    // If the node enters active state, it will be shown to the user
    if (false == isActive) {
    
      Serial.println("Active state entered.");
      isActive = true;
    }
    
    // Any VSCP message received?
    if (true == vscp.read(rxMsg)) {
    
        // Implement your code here ...
        
    }
    
    // Send a VSCP message here ...
    
  } else {
  
    // If the node leaves active state, it will be shown to the user
    if (true == isActive) {
      Serial.println("Active state left.");
      isActive = false;
    }
  
  }
  
}
