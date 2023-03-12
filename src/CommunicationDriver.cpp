#include "Arduino.h"
#include "CommunicationDriver.h"
#include "SolenoidMatrix.h"

CommunicationDriver::CommunicationDriver(HardwareSerial& my_Serial): serial_port(my_Serial){}

void CommunicationDriver::begin(){
    serial_port.begin(9600);
    serial_port.setTimeout(10); // Set timeout to 10 ms for functions like Serial.readString()
}

bool CommunicationDriver::MessageWaits(){
    // API to check if 3x16b message is ready to read
    return serial_port.available() >= 6;
}

void CommunicationDriver::clearSerialBuffer() {
  serial_port.println("Clearing buffer...");
  while (serial_port.available() > 0) {
    // serial_port.read();
    serial_port.println(serial_port.read());
    // serial_port.println(serial_port.available());
  }
}

uint16_t CommunicationDriver::ReadMessage(){
    // API to read a message as two 8bit parts to get 16bit number 
    // uint16_t message = serial_port.read() | (serial_port.read() << 8); // read the number as 2 bytes and combine them into a 16-bit integer
    // message = atoi(message);
    // serial_port.print("Received number: ");
    // serial_port.println(message);
    // return message;

    String teststr = serial_port.readString();  //read until timeout
    teststr.trim();
    uint16_t message = (uint16_t)atoi(teststr.c_str());
    return message;
}

uint16_t CommunicationDriver::ExtractTime(uint16_t message){
    // API to get time in ms from the message 
    uint16_t time = message & EXTRACT_TIME_MASK;
    time = time >> EXTRACT_TIME_SHIFT;
    time = time * EXTRACT_TIME_DISCRETE;
    return time;
}

void CommunicationDriver::fillArrayFrom16BitMessage(uint16_t message, bool (&array)[NUM_OF_SOLENOIDS]) {
    // API to fill solenoid states array from the message 
    for (int i = 0; i < NUM_OF_SOLENOIDS; i++) {
        array[i] = message & (1 << i); // extract the i-th bit of the message and store it in the array
        
        // DEBUG
        // serial_port.print("Array ");
        // serial_port.print(i);
        // serial_port.print(" = ");
        // serial_port.println(array[i]);
    }
}
