#include "Arduino.h"
#include "Solenoid.h"
#include <math.h>

Solenoid::Solenoid(uint8_t set_pin) {
    pin = set_pin;
    turn_on = 0;
    pinMode(pin, OUTPUT);
}

void Solenoid::SetTimer(uint16_t set_time){
    turn_on = set_time;
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

bool Solenoid::SolenoidIsReady(){
    return turn_on == 0;
}