#include "Arduino.h"
#include "Solenoid.h"
#include "SolenoidMatrix.h"
#include <algorithm>
#include <assert.h>

// Initializes all 9 Solenoids,
// Each of them activates its pin and resets its timer
SolenoidMatrix::SolenoidMatrix(uint8_t* set_pin_array) {
    
    assert(sizeof(set_pin_array) == NUM_OF_SOLENOIDS);
    solenoids = (Solenoid*) malloc(NUM_OF_SOLENOIDS*sizeof(Solenoid));

    for (int i; i < NUM_OF_SOLENOIDS; i++){
        solenoids[i] = Solenoid(set_pin_array[i]);
    }

}

// Returns True if all Solenoids are ready to run 
// Requested pattern
// requested_pattern is 16b digit that holds both Solenodis and Duration:
// b'00tttttsssssssss
// - t..t is 0..32 number showing how much of 50ms pattern is requested for
// 00001 means 50ms, 00010 means 100ms and so on
// - ss..ss are binary states of each solenoid
// 10000.. means to turn on 1st solenoid, 0100.. 2nd solenoid, 11000.. 1st and 2nd
// - 00 is a space
bool SolenoidMatrix::CheckSolenoidsReady(uint16_t requested_pattern){

    assert(sizeof(new_state_array) == NUM_OF_SOLENOIDS);

    int16_t requested_time = (requested_pattern & MASK_EXTRACT_TIME) >> SHIFT_EXTRACT_TIME;

    bool solenoids_are_ready = true;
    for (int i = 0; i < NUM_OF_SOLENOIDS; i++){
        // Find if i-th solenoid is requested to be turned on
        int16_t mask_for_current_solenoid_position = 1 << i;
        bool activate_this_solenoid = mask_for_current_solenoid_position == (requested_pattern & mask_for_current_solenoid_position);

        // Version 1: Risk of overheat
        // For solenoid that is requested to be turned on
        // Check that it's available turn_on window is bigger than requested, 
        // Otherwise solenoids are not ready
        // if (activate_this_solenoid){
        //     int32_t time_left = solenoids[i].TimeOnLeft;
        //     solenoids_are_ready = time_left > requested_time;
        // }

        // Version 2: Less risk
        // If all solenoids timers are zero - it means they 
        // Had rest of minimum the time they were ON,
        // So they will not overheat
        if (activate_this_solenoid){
            int32_t time_left = solenoids[i].TimeOnLeft;
            solenoids_are_ready = time_left == 0;
        }

        if (solenoids_are_ready == false){
            break;
        }
    }

    return solenoids_are_ready;
}

bool SolenoidMatrix::UpdateSolenoidMatrix(uint16_t requested_pattern){

    // Check that all solenoids are ready
    bool solenoids_are_ready = CheckSolenoidsReady(requested_pattern);
    if (solenoids_are_ready == false){
        return solenoids_are_ready;
    }

    // Update all Solenoids
    for (int i = 0; i < NUM_OF_SOLENOIDS; i++){
        int16_t mask_for_current_solenoid_position = 1 << i;
        bool activate_this_solenoid = mask_for_current_solenoid_position == (requested_pattern & mask_for_current_solenoid_position);

        if (activate_this_solenoid){
            solenoids[i].UpdateSolenoidState()
        }

    }
}
