#include <Arduino.h>
#include "SolenoidMatrix.h"
#include "CommunicationDriver.h"

#define TICK_TIME 50  // Update solenoids each 50ms

uint64_t time_stamp_1 = millis();
uint64_t time_stamp_2 = millis();
uint8_t solenoid_pins[] = {12,11,10,9,8,7,6,5,3};
bool* solenoid_states;                 


void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);

  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);

  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);

  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);

  Serial.println("Start!");

}

void loop() {

  Serial.println("New Loop");

  // Serial.println(1);

  static SolenoidMatrix mySolenoidMatrix(solenoid_pins);
  static CommunicationDriver myCommunication;

  // Serial.println(2);

  // Read the message
  if (myCommunication.MessageWaits()){
    static uint16_t message = myCommunication.ReadMessage();
    static uint16_t solenoid_time = myCommunication.ExtractTime(message);
    myCommunication.fillArrayFrom16BitMessage(message, solenoid_states);
    if (mySolenoidMatrix.CheckSolenoidsAreReady(solenoid_states)){
      mySolenoidMatrix.SetSolenoidPattern(solenoid_states, solenoid_time);  // Put the message data into Solenoid Matrix
    }
  }

  // Serial.println(3);

  // Update Solenoids each 50ms
  time_stamp_1 = millis();
  if (time_stamp_1 - time_stamp_2 > TICK_TIME){
    mySolenoidMatrix.UpdateSolenoidMatrix();
    time_stamp_2 = millis();
    Serial.println("Timer");
  }

  // Serial.println(4);

  delay(2000);
  
}