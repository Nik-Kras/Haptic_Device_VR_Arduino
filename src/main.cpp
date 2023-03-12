#include <Arduino.h>
#include "SolenoidMatrix.h"
#include "CommunicationDriver.h"

#define TICK_TIME 50  // Update solenoids each 50ms

/*
NOTE ON SOLENOIDS:
- Solenoids are very fast, You can use them up to 20Hz with no issues (Higher frequencies were not tested, so MAX could be higher)
- However you should be careful on ON TIME as it is a source of harm. Test with 7V Power Supply and 1Hz signal on solenoid showed around 40C degrees in 1 minute
- It heats up very fast on low frequencies, so 1Hz is assumed a minimum frequency and it is desired to avoid it and work in range 5-20Hz
- It doesn't heat as all on 20Hz frequency
*/

/* Pins = [
  12  11  10 
  9   8   7
  6   5   3 
]
*/

uint64_t time_stamp_1 = millis();
uint64_t time_stamp_2 = millis();
uint8_t solenoid_pins[] = {12,11,10,9,8,7,6,5,3};
bool solenoid_states[] = {false,false,false,false,false,false,false,false,false};                 

void printNewSolenoidStates(bool* array_to_print){
  for (int i = 0; i<9; i++){
    Serial.print("Solenoid #");
    Serial.print(i);
    Serial.print(" State: ");
    if (array_to_print[i]){
      Serial.println("ON");
    }else{
      Serial.println("OFF");
    }
    delay(20);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);

  for (int i = 0; i < 3; i ++){
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }

  delay(100);
  Serial.println("Start!");
  Serial.println("Version v1");
  delay(100);

}

void loop() {

  static SolenoidMatrix mySolenoidMatrix(solenoid_pins);
  static CommunicationDriver myCommunication;

  // Read the message
  if (myCommunication.MessageWaits()){
    // Serial.print("Available bytes: ");
    // Serial.println(Serial.available());

    static uint16_t message = myCommunication.ReadMessage();
    static uint16_t solenoid_time = myCommunication.ExtractTime(message);
    myCommunication.fillArrayFrom16BitMessage(message, solenoid_states);
    if (mySolenoidMatrix.CheckSolenoidsAreReady(solenoid_states)){
      mySolenoidMatrix.SetSolenoidPattern(solenoid_states, solenoid_time); 
    }
    // Serial.println("Final Pattern:");
    // printNewSolenoidStates(mySolenoidMatrix.solenoid_states);
  }

  // DEBUG - Single Message
  // static bool b = true;
  // if (b){
  //   b = false;
  //   Serial.println("Available: ");
  //   Serial.println(Serial.available());

  //   static uint16_t message = 5393;
  //   static uint16_t solenoid_time = myCommunication.ExtractTime(message);
  //   Serial.println("Mesage: ");
  //   Serial.println(message);
  //   Serial.println("Time: ");
  //   Serial.println(solenoid_time);

  //   Serial.println("Before: ");
  //   printNewSolenoidStates(mySolenoidMatrix.solenoid_states);

  //   myCommunication.fillArrayFrom16BitMessage(message, solenoid_states);
  //   if (mySolenoidMatrix.CheckSolenoidsAreReady(solenoid_states)){
  //     mySolenoidMatrix.SetSolenoidPattern(solenoid_states, solenoid_time);  // Put the message data into Solenoid Matrix
  //   }

  //   Serial.println("After: ");
  //   printNewSolenoidStates(mySolenoidMatrix.solenoid_states);
  // }

  // Update Solenoids each 50ms
  // time_stamp_1 = millis();
  // if (time_stamp_1 - time_stamp_2 > TICK_TIME){
  //   mySolenoidMatrix.UpdateSolenoidMatrix();
  //   time_stamp_2 = millis();
  //   Serial.println("Timer");
  // }

  // DEBUG
  // Serial.print("Update #");
  // Serial.println(cnt);
  mySolenoidMatrix.UpdateSolenoidMatrix();
  time_stamp_2 = millis();
  delay(50);
  
}