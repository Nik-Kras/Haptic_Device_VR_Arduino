#ifndef LibTimeTrackerArray
#define LibTimeTrackerArray

#include "Arduino.h" 

class TimeTrackerArray {

private:
    int64_t _mask_14_last_bytes;

public:
    
    int64_t number_1;
    int64_t number_2;

    // https://en.cppreference.com/w/cpp/utility/bitset/count 
    // bitset<100> time_array; 

    TimeTrackerArray();
    void UpdateSolenoidTimer(bool new_state);
    bool CheckReadyToRun(int threshold);
};

#endif