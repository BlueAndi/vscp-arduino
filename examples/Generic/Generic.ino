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

#include <VSCP.h>

// Create an instance of the VSCP framework
VSCP  vscp;

// Node is in active state or not
static bool isActive = false;

// Read a message from the transport layer, e.g. the CAN bus
// If no message is received return false, otherwise true.
bool transportRead(vscp_RxMessage * const rxMsg) {
  
  // Implement your code here ...
  /*
    
    unsigned char index = 0;
    
    rxMsg->priority     = ...
    rxMsg->vscpClass    = ...
    rxMsg->vscpType     = ...
    rxMsg->oAddr        = ...
    rxMsg->hardCoded    = ...
    rxMsg->dataNum      = ...
    
    // Protect against data buffer out of bounce access
    if (VSCP_L1_DATA_SIZE < rxMsg->dataNum)
    {
        rxMsg->dataNum = VSCP_L1_DATA_SIZE;
    }
    
    // Copy the payload
    for(index = 0; index < rxMsg->dataNum; ++index)
    {
        rxMsg->data[index] = ...
    }
    
  */
  
  return false;
}

// Write a message to the transport layer, e.g. the CAN bus
// If it fails to send the message return false, otherwise true.
bool transportWrite(vscp_TxMessage const * const txMsg) {
  
  // Implement your code here ...
  /*
    
    unsigned char index = 0;
    
    ... = rxMsg->priority;
    ... = rxMsg->vscpClass;
    ... = rxMsg->vscpType;
    ... = rxMsg->oAddr;
    ... = rxMsg->hardCoded;
    ... = rxMsg->dataNum;
        
    // Copy the payload
    for(index = 0; index < rxMsg->dataNum; ++index)
    {
        ... = rxMsg->data[index];
    }
    
    // Implement a retry mechanism here as well
    ...
    
  */
  
  return false;
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

  // Set the baudrate of the serial connection to the PC
  Serial.begin(115200);
  Serial.println("VSCP node starts up ...");
  
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
    
    // Send a VSCP message here ... e.g. a CLASS1.INFORMATION ON event
    vscp.prepareTxMessage(txMsg, VSCP_CLASS_L1_INFORMATION, VSCP_TYPE_INFORMATION_ON, VSCP_PRIORITY_3_NORMAL);
    txMsg.data[0] = 1;  // Index
    txMsg.data[1] = 0;  // Zone
    txMsg.data[2] = 0;  // Sub zone
    txMsg.dataNum = 3;
    vscp.write(txMsg);
  
  } else {
  
    // If the node leaves active state, it will be shown to the user
    if (true == isActive) {
      Serial.println("Active state left.");
      isActive = false;
    }
  
  }
  
}
