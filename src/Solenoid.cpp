#include "Arduino.h"
#include "Solenoid.h"
#include <algorithm>

Solenoid::Solenoid(uint8_t set_pin) {
    pin = set_pin;
    turn_on = 0;
    pinMode(pin, OUTPUT);
}

// Updates actual solenoid state
// Updates Turn On timer
void Solenoid::UpdateSolenoidState(bool new_state){
    if (new_state){
        digitalWrite(pin, HIGH);
        turn_on += DISCRETISATION_PERIOD;
        turn_on = min(0, turn_on);
    }else{
        digitalWrite(pin, LOW);
        turn_on -= DISCRETISATION_PERIOD;
        turn_on = max(0, turn_on);
    }
}

uint32_t Solenoid::TimeOnLeft(){
    return MAX_TURN_ON_TIME - turn_on;
}
