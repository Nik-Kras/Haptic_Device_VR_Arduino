#ifndef LibSolenoidMatrix
#define LibSolenoidMatrix

#include "Arduino.h" 
#include "Solenoid.h"

#define NUM_OF_SOLENOIDS 9
#define MASK_EXTRACT_TIME 0x3E00    // Apply to requested pattern to get requested time in units=50ms
#define SHIFT_EXTRACT_TIME 9

class SolenoidMatrix {

public:
    Solenoid* solenoids;
    bool* solenoid_states;
    uint16_t time_on_left;
    
    SolenoidMatrix(uint8_t* set_pin_array);
    bool CheckSolenoidsAreReady(bool* array_solenoid_states);
    void SetSolenoidPattern(bool* array_solenoid_states, uint16_t time);
    void UpdateSolenoidMatrix();

};

#endif