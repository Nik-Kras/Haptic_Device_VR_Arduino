#include "Arduino.h"
#include "Solenoid.h"

Solenoid::Solenoid(int8_t set_pin) {
    pin = set_pin;
    pinMode(pin, OUTPUT);
}

// Updates actual solenoid state
void Solenoid::UpdateSolenoidState(bool new_state){
    if (new_state){
        digitalWrite(pin, HIGH);
    }else{
        digitalWrite(pin, LOW);
    }
}
