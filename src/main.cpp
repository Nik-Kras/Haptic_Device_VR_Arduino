#include <Arduino.h>
#include "SolenoidMatrix.h"
#include "CommunicationDriver.h"

#define TICK_TIME 50  // Update solenoids each 50ms

uint64_t time_stamp_1 = millis();
uint64_t time_stamp_2 = millis();
uint8_t solenoid_pins[] = {12,11,10,9,8,7,6,5,3};
bool* solenoid_states;                 
SolenoidMatrix mySolenoidMatrix(solenoid_pins);
CommunicationDriver myCommunication;

void setup() {
  Serial.begin(9600);
}

void loop() {

  // Read the message
  if (myCommunication.MessageWaits()){
    static uint16_t message = myCommunication.ReadMessage();
    static uint16_t solenoid_time = myCommunication.ExtractTime(message);
    myCommunication.fillArrayFrom16BitMessage(message, solenoid_states);
    if (mySolenoidMatrix.CheckSolenoidsAreReady(solenoid_states)){
      mySolenoidMatrix.SetSolenoidPattern(solenoid_states, solenoid_time);  // Put the message data into Solenoid Matrix
    }
  }
    
  // Update Solenoids each 50ms
  static uint64_t time_stamp_1 = millis();
  if (time_stamp_1 - time_stamp_2 > TICK_TIME){
    mySolenoidMatrix.UpdateSolenoidMatrix();
  }
  
}