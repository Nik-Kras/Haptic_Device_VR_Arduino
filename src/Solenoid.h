#ifndef LibSolenoid
#define LibSolenoid

#include "Arduino.h" 

class Solenoid {

public:
    int8_t pin;
    
    Solenoid(int8_t set_pin);
    void UpdateSolenoidState(bool new_state);

};

#endif