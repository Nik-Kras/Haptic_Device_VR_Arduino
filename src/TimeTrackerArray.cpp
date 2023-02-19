#include "Arduino.h"
#include "TimeTrackerArray.h"

TimeTrackerArray::TimeTrackerArray() {
    
}

// When solenoid worked more than 1s in last 2s
// Will return False, showing that it needs to rest
// Otherwise returns True, ready to turn the solenoid on
bool TimeTrackerArray::CheckReadyToRun(int threshould){

    // int sum_of_array = time_array.count()
    // bool result = threshould > sum_of_array
    // return result

    return false;
}

// With new solenoid state comming I add new value to the right
// And clear the oldest one so we have last 2 seconds updated
// PS: Call it each 50ms!!!
void TimeTrackerArray::UpdateSolenoidTimer(bool new_state){
    // time_array = time_array << 1
    // if new_state{
    //     time_array.set(99)
    // }
}