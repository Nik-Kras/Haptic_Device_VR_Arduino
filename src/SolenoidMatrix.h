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
    
    SolenoidMatrix(uint8_t* set_pin_array);
    bool CheckSolenoidsReady(uint16_t requested_pattern);
    void UpdateSolenoidMatrix(uint16_t requested_pattern);

};

#endif