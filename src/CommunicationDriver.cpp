#include "Arduino.h"
#include "CommunicationDriver.h"
#include "SolenoidMatrix.h"

CommunicationDriver::CommunicationDriver(){}

bool CommunicationDriver::MessageWaits(){
    /* API to check if 16b message is ready to read*/
    return Serial.available() >= 2;
}

uint16_t CommunicationDriver::ReadMessage(){
    /* API to read a message as two 8bit parts to get 16bit number */
    // uint16_t message = Serial.read() | (Serial.read() << 8); // read the number as 2 bytes and combine them into a 16-bit integer
    // message = atoi(message);
    // Serial.print("Received number: ");
    // Serial.println(message);
    // return message;

    String teststr = Serial.readString();  //read until timeout
    teststr.trim();
    uint16_t message = (uint16_t)atoi(teststr.c_str());
    Serial.print("Received number: ");
    Serial.println(message);
    return message;
}

uint16_t CommunicationDriver::ExtractTime(uint16_t message){
    /* API to get time in ms from the message */
    uint16_t time = message & EXTRACT_TIME_MASK;
    time = time >> EXTRACT_TIME_SHIFT;
    time = time * EXTRACT_TIME_DISCRETE;
    return time;
}

void CommunicationDriver::fillArrayFrom16BitMessage(uint16_t message, bool (&array)[NUM_OF_SOLENOIDS]) {
    /* API to fill solenoid states array from the message */
    for (int i = 0; i < NUM_OF_SOLENOIDS; i++) {
        array[i] = message & (1 << i); // extract the i-th bit of the message and store it in the array
    }
}
