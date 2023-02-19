#ifndef LibSolenoid
#define LibSolenoid

#include "Arduino.h" 

#define DISCRETISATION_PERIOD = 50  // ms
#define MAX_TURN_ON_TIME = 1000     // ms
#define ATTENTION_WINDOW = 2000     // ms

class Solenoid {

public:
    uint8_t pin;
    uint16_t turn_on;
    
    Solenoid(int8_t set_pin);
    void UpdateSolenoidState(bool new_state);
    uint16_t TimeOnLeft()

};

#endif