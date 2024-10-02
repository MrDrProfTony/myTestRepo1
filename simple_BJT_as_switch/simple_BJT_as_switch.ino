/*
 * Dr. Anthony Barsic
 * University of Vermont
 * Department of Electrical Engineering
 * CMPE 3815
 * 2024 September 29
 * The purpose of this script is to use a BJT as a simple switch.
 * In this case, the BJT is simply switching on an LED.
 *
 * I later added a 2nd BJT+LED circuit. Then I made them blink in a 4th/3rds rhythm.
 *
 * The hardware set-up for a single BJT/LED circuit is:
 * "switched" line sequence:
 *      [5V] - [R ~220ohm] - [LED] - [BJT-collector] [BJT-emitter] - GND
 * Then, the [BJT-base] is connected to a digital pin (GPIO) via a 1k resistor.
 * Operating principle:
 * Pulling the base high (or rather, injecting current via the R=1k) will
 * "open the tap" on the BJT, thus allowing current to flow through the LED circuit.
 * 
 * I repeated the circuit a 2nd time for a 2nd cricuit.
 * Then, I run through the blinking scheme.
 */

// INIT ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+===
// Explicitly include Arduino.h
#include "Arduino.h"

// This pin is connected to the BJT's base.
// Any digital IO pin will do.
// The circuit is wired such that a HIGH will turn on the BJT collector-emitter path.
const byte pinBJTbase_green = 7; 

// Repeat a 2nd time for the red LED
const byte pinBJTbase_red = 8;  


// SETUP ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+===                      
void setup()
{
  // prepare the pins for output, and start them off LOW
  pinMode(pinBJTbase_green, OUTPUT);
  digitalWrite(pinBJTbase_green, LOW);
  // again for 2nd output/circuit
  pinMode(pinBJTbase_red, OUTPUT);
  digitalWrite(pinBJTbase_red, LOW);
}


// LOOP ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+=== ===+===
void loop()
{
  // I want one to turn on 3 times per "measure",
  // And the other to turn on 4 times in the same period

  // Define the delay time (this is half of 1/12th of a measure)
  const byte delayOneTwelfthHalved = 80; // 60 ms - good value for 3/4
  // const byte delayOneTwelfthHalved = 15; // 15 ms - good value for 12/13
  // I initially coded this for 3s/4s polyrhythm, but I can do any polyrhythm now
  static byte polyRhythm_green = 3;
  static byte polyRhythm_red   = 4;
  // static byte polyRhythm_green = 12;
  // static byte polyRhythm_red   = 13;

  // now we need a counter for each LED
  static byte counter_green = 0;
  static byte counter_red = 0;

  // Switch them on (if it's their time)
  if ( !(counter_green%polyRhythm_green) ) digitalWrite(pinBJTbase_green, HIGH);
  if ( !(counter_red%polyRhythm_red)     ) digitalWrite(pinBJTbase_red,   HIGH);
  delay(delayOneTwelfthHalved);

  // Switch them off (if it's their time)
  if ( !(counter_green%polyRhythm_green) ) digitalWrite(pinBJTbase_green, LOW);
  if ( !(counter_red%polyRhythm_red)     ) digitalWrite(pinBJTbase_red,   LOW);
  delay(delayOneTwelfthHalved);

  // update the counters
  counter_green = (counter_green+1) % (polyRhythm_green*polyRhythm_red);
  counter_red   = (counter_red+1)   % (polyRhythm_green*polyRhythm_red);
}


// ===+=== ===+=== ===+=== ===+=== ===+=== END OF SKETCH ===+=== ===+=== ===+=== ===+=== ===+===
// ===+=== ===+=== ===+=== ===+=== ===+=== END OF SKETCH ===+=== ===+=== ===+=== ===+=== ===+===
// ===+=== ===+=== ===+=== ===+=== ===+=== END OF SKETCH ===+=== ===+=== ===+=== ===+=== ===+===