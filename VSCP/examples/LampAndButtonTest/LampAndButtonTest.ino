#include <DigInDebounce.h>
#include <SwTimer.h>
#include <VSCP.h>

static int            gStatusLampPin    = 13;
static int            gInitButtonPin    = 12;
static unsigned int   gTimeout          = 250;
static SwTimer        gSwTimer;
static DigInDebounce  gInitButton(gInitButtonPin);
static int            gInitButtonState  = HIGH;

void setup() {
  
  Serial.begin(115200);
  Serial.println("Starts up ...");
  
  pinMode(gStatusLampPin, OUTPUT);
  pinMode(gInitButtonPin, INPUT_PULLUP);
  gSwTimer.start(gTimeout);

}

void loop() {

  gSwTimer.process();

  if (true == gSwTimer.isTimeout()) {

    int statusLampPinState = digitalRead(gStatusLampPin);

    if (LOW == statusLampPinState)
    {
      statusLampPinState = HIGH;
    }
    else
    {
      statusLampPinState = LOW;
    }

    digitalWrite(gStatusLampPin, statusLampPinState);
  }

  if (LOW == gInitButton.read()) {
    if (HIGH == gInitButtonState) {
      gTimeout += 250;
      
      if (1000 <= gTimeout) {
        gTimeout = 250;
      }
      gSwTimer.start(gTimeout);
      
      Serial.println("Init button triggered.");
      
      gInitButtonState = LOW;
    }
  }
  else {
    gInitButtonState = HIGH;
  }

}
