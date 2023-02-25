#ifndef LibSolenoid
#define LibSolenoid

#include "Arduino.h" 

#define DISCRETISATION_PERIOD 50  // ms
#define MAX_TURN_ON_TIME 1000     // ms
#define ATTENTION_WINDOW 2000     // ms

class Solenoid {

public:
    uint8_t pin;
    uint16_t turn_on;
    
    Solenoid(uint8_t set_pin);
    void SetTimer(uint16_t set_time);
    void UpdateSolenoidState(bool new_state);
    bool SolenoidIsReady();

};

#endif