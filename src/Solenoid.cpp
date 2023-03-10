#include "Arduino.h"
#include "Solenoid.h"
#include <math.h>

Solenoid::Solenoid() {
    turn_on = 0;
}

void Solenoid::SetPin(uint8_t set_pin){

    // DEBUG
    // Serial.print("Pin: ");
    // Serial.print(set_pin);
    // Serial.println(" is set to OUTPUT");
    pin = set_pin;
    pinMode(pin, OUTPUT);
}

void Solenoid::SetTimer(int16_t set_time){
    turn_on = set_time;
}

// Updates actual solenoid state
// Updates Turn On timer
void Solenoid::UpdateSolenoidState(bool new_state){
    if (new_state){
        digitalWrite(pin, HIGH);
        turn_on += DISCRETISATION_PERIOD;
        // turn_on = min(0, turn_on);
    }else{
        digitalWrite(pin, LOW);
        turn_on -= DISCRETISATION_PERIOD;
        turn_on = max(0, turn_on);
    }
}

bool Solenoid::SolenoidIsReady(){
    
    // DEBUG
    // Serial.print("Timer On: ");
    // Serial.print(turn_on);
    return turn_on == 0;
}