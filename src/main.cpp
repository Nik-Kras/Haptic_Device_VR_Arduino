#include <Arduino.h>
#include "SolenoidMatrix.h"

#define TICK_TIME 50  // Update solenoids each 50ms

uint64_t time_stamp_1 = millis();
uint64_t time_stamp_2 = millis();

void setup() {
  uint8_t solenoid_pins = {12,11,10,9,8,7,6,5,3};
  SolenoidMatrix mySolenoidMatrix(solenoid_pins);
  Serial.begin(9600);
}

// On Serial parsing: https://www.programmingelectronics.com/serial-read/
void loop() {

  // Get latest request
  static int16_t incomming_request;
  while (Serial.available() > 0){
    incomming_request = Serial.read();
  }
  
  // Update Solenoids each 50ms
  uint64_t time_stamp_1 = millis();
  if (time_stamp_1 - time_stamp_2 > TICK_TIME){

    time_stamp_2 = millis();
  }

  
}