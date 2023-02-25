#include "Arduino.h"
#include "Solenoid.h"
#include "SolenoidMatrix.h"
#include <math.h>
#include <assert.h>

// Initializes all 9 Solenoids,
// Each of them activates its pin and resets its timer
SolenoidMatrix::SolenoidMatrix(uint8_t* set_pin_array) {
    assert(sizeof(set_pin_array) == NUM_OF_SOLENOIDS);
    solenoids = (Solenoid*) malloc(NUM_OF_SOLENOIDS*sizeof(Solenoid));
    for (int i; i < NUM_OF_SOLENOIDS; i++){
        solenoids[i] = Solenoid(set_pin_array[i]);
        solenoid_states[i] = false;
    }
}

bool SolenoidMatrix::CheckSolenoidsAreReady(bool* array_solenoid_states){
    /* Call to check if all solenoids are ready for new pattern comming */
    // For each solenoid that will be used we check if it rested enough and ready to be used
    bool all_solenoids_are_aready = true;
    for (int i = 0; i < NUM_OF_SOLENOIDS; i++) {
        if (array_solenoid_states[i]){
            all_solenoids_are_aready = solenoids[i].SolenoidIsReady();
        }
        if (all_solenoids_are_aready == false){ break; }
    }
    return all_solenoids_are_aready;
}

void SolenoidMatrix::SetSolenoidPattern(bool* array_solenoid_states, uint16_t time){
    assert(time <= 1000);
    solenoid_states = array_solenoid_states;
    time_on_left = time;
}

void SolenoidMatrix::UpdateSolenoidMatrix(){
    /* API to be called each 50ms. Updates timer and states for all solenoids */
    if (time_on_left > 0){
        for (int i = 0; i < NUM_OF_SOLENOIDS; i++) {
            solenoids->UpdateSolenoidState(solenoid_states[i]);
        }
        time_on_left -= DISCRETISATION_PERIOD;
        time_on_left = max(0, time_on_left);
    }else{
        for (int i = 0; i < NUM_OF_SOLENOIDS; i++) {
            solenoids->UpdateSolenoidState(false);
        }
    }
}
    
