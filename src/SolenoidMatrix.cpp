#include "Arduino.h"
#include "Solenoid.h"
#include "SolenoidMatrix.h"
#include <math.h>
#include <assert.h>

// Initializes all 9 Solenoids,
// Each of them activates its pin and resets its timer
SolenoidMatrix::SolenoidMatrix(uint8_t* set_pin_array) {
    // len(set_pin_array) == 9
    // solenoids = (Solenoid*) malloc(NUM_OF_SOLENOIDS*sizeof(Solenoid));
    // solenoids = new Solenoid[NUM_OF_SOLENOIDS]();
    for (int i; i < NUM_OF_SOLENOIDS; i++){
        solenoids[i].SetPin(set_pin_array[i]);
        solenoid_states[i] = false;
    }
    time_on_left = 0;
}

bool SolenoidMatrix::CheckSolenoidsAreReady(bool* array_solenoid_states){
    /* Call to check if all solenoids are ready for new pattern comming */
    // For each solenoid that will be used we check if it rested enough and ready to be used
    bool all_solenoids_are_aready = true;
    for (int i = 0; i < NUM_OF_SOLENOIDS; i++) {

        // DEBUG
        // Serial.print("Checking Solenoid #");
        // Serial.print(i);
        // Serial.print(" ");
        // bool ready = solenoids[i].SolenoidIsReady();
        // Serial.print(" State: ");
        // Serial.println(ready);

        if (array_solenoid_states[i]){
            all_solenoids_are_aready = solenoids[i].SolenoidIsReady();
        }
        if (all_solenoids_are_aready == false){ break; }
    }
    // Serial.print("Total Ready: ");
    // Serial.println(all_solenoids_are_aready);
    return all_solenoids_are_aready;
}

void SolenoidMatrix::SetSolenoidPattern(bool array_solenoid_states[NUM_OF_SOLENOIDS], int16_t time){
    assert(time <= 1000);
    for (int i = 0; i < NUM_OF_SOLENOIDS; i++){
        solenoid_states[i] = array_solenoid_states[i];

        // // DEBUG
        // Serial.print("SET Solenoid #");
        // Serial.print(i);
        // Serial.print(" to State ");
        // Serial.println(solenoid_states[i]);
    }
    time_on_left = time;
}

void SolenoidMatrix::UpdateSolenoidMatrix(){
    /* API to be called each 50ms. Updates timer and states for all solenoids */
    
    // DEBUG
    // for (int i = 0; i < 9; i++){
    //     Serial.print("Solenoid #");
    //     Serial.print(i);
    //     Serial.print(" State: ");
    //     Serial.println(solenoid_states[i]);
    // }
    
    if (time_on_left > 0){
        for (int i = 0; i < NUM_OF_SOLENOIDS; i++) {
            solenoids[i].UpdateSolenoidState(solenoid_states[i]);
        }
        time_on_left -= DISCRETISATION_PERIOD;
        time_on_left = max(0, time_on_left);
    }else{
        for (int i = 0; i < NUM_OF_SOLENOIDS; i++) {
            solenoids[i].UpdateSolenoidState(false);
            solenoid_states[i] = false;
        }
    }
}
    
