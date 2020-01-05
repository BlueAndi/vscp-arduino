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
