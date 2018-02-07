/* The MIT License (MIT)
 * 
 * Copyright (c) 2014 - 2018, Andreas Merkle
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

#include <VSCP.h>           // VSCP framework
#include <SPI.h>            // SPI used for CAN controller communication
#include <mcp_can.h>        // CAN controller driver
#include <mcp_can_dfs.h>    // CAN controller driver defines

// Create an instance of the VSCP framework
VSCP  vscp;

// Create an instance of the CAN controller driver
MCP_CAN canCom(
  9 // Set CS (chip select) pin, note if you use a CAN BUS shield prior to V1.1 use pin 10!
);

// Node is in active state or not
static bool isActive = false;

// Read a message from the transport layer, e.g. the CAN bus
// If no message is received return false, otherwise true.
bool transportRead(vscp_RxMessage * const rxMsg) {
  
  bool status   = false;
  
  if (CAN_MSGAVAIL == canCom.checkReceive())
  {
    unsigned long   canMsgId  = 0;
    
    if (CAN_OK == canCom.readMsgBufID(&canMsgId, &rxMsg->dataNum, rxMsg->data)) {
    
        rxMsg->vscpClass  = (uint16_t)((canMsgId >> 16) & 0x01ff);
        rxMsg->vscpType   = (uint8_t)((canMsgId >> 8) & 0x00ff);
        rxMsg->oAddr      = (uint8_t)((canMsgId >> 0) & 0x00ff);
        rxMsg->hardCoded  = (uint8_t)((canMsgId >> 25) & 0x0001);
        rxMsg->priority   = (VSCP_PRIORITY)((canMsgId >> 26) & 0x0007);
            
        status = true;
    }
  }
  
  return status;
}

// Write a message to the transport layer, e.g. the CAN bus
// If it fails to send the message return false, otherwise true.
bool transportWrite(vscp_TxMessage const * const txMsg) {
  
  bool          status    = false;
  unsigned long canMsgId  = 0;
  unsigned char retryCnt  = 0;
  
  canMsgId = (((uint32_t)txMsg->priority)  << 26) |
             (((uint32_t)txMsg->hardCoded) << 25) |
             (((uint32_t)txMsg->vscpClass) << 16) |
             (((uint32_t)txMsg->vscpType)  <<  8) |
             txMsg->oAddr;
  
  do {
    
    // Before any retry, wait some time
    if (0 < retryCnt)
    {
      delay(100);
    }
    
    // Send CAN message
    if (CAN_OK != canCom.sendMsgBuf(canMsgId, 1, 0, txMsg->dataNum, (unsigned char*)txMsg->data)) {
      
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
    // Implement your cod here ...
    
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
    if (CAN_OK != canCom.begin(CAN_125KBPS)) {
    
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
  
  } else {
  
    Serial.println("CAN controller initialized successful.");
  
    // Only CAN frames with 29-bit identifier shall be received
    canCom.init_Mask(0, 1, 0x1fffffff);
    canCom.init_Mask(1, 1, 0x1fffffff);
    canCom.init_Filt(0, 0, 0x00);
    canCom.init_Filt(1, 0, 0x00);
    canCom.init_Filt(2, 0, 0x00);
    canCom.init_Filt(3, 0, 0x00);
    canCom.init_Filt(4, 0, 0x00);
    canCom.init_Filt(5, 0, 0x00);
     
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
