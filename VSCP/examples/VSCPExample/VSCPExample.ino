#include <VSCP.h>

// Create an instance of the VSCP framework
VSCP  vscp;

// Read a message from the transport layer, e.g. the CAN bus
// If no message is received return false, otherwise true.
bool transportRead(vscp_RxMessage * const rxMsg) {
  
  // Implement your code here ...
  
  return false;
}

// Write a message to the transport layer, e.g. the CAN bus
// If it fails to send the message return false, otherwise true.
bool transportWrite(vscp_TxMessage const * const txMsg) {
  
  // Implement your code here ...
  
  return false;
}

// Is called by the VSCP framework to notify the user about a received message
void notify(vscp_RxMessage const * const rxMsg) {
  
  // Implement your code here ...

  return;  
}

void setup() {
  
  // Node GUID - Used to unique identify nodes
  VSCPGuid  nodeGuid = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
  
  // Setup VSCP framework
  vscp.setup(
    13,             // Status lamp pin
    14,             // Init button pin
    nodeGuid,       // Node GUID,
    255,            // Node zone (255 = all zones)
    255,            // Node sub-zone (255 = all sub-zones)
    transportRead,  // VSCP framework calls it to read a message
    transportWrite  // VSCP framework calls it to write a message
  );

}

void loop() {
  // Process the VSCP framework
  vscp.process();

  // Send VSCP messages only in active state
  if (true == vscp.isActive()) {
    
    /* Do something here ... */
    
  }
}
