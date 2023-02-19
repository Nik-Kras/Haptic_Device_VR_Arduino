#include <Arduino.h>
#include "SolenoidMatrix.h"

/* Each solenoid must not be turned on
   for longer than `000 ms per 2000 ms
   The state of solenoids will be updated
   with 50 ms time period or 20Hz.
   That gives one possible solution to
   keep track of time on per period: 
   circular buffer

   We can create an array of 100 elements (or 100-byte number)
   and each 50ms we shift all its elements to the left 
   and add current state to the right element (1 or 0).
   When the sum of array is 50 or more we ignore turning on.
   That will prevent 
     */
#define DISCRETISATION_PERIOD = 50  // ms
#define MAX_TURN_ON_TIME = 1000     // ms
#define ATTENTION_WINDOW = 2000     // ms



void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}