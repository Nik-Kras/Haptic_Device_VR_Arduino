#ifndef LibCommunicationDriver
#define LibCommunicationDriver

#include "Arduino.h" 
#include "SolenoidMatrix.h"

/**
 * The communication protocol is next:
 * - I receive a 16b number
 * - It encodes solenoids selection and time ON for them in next way:
 * 
 *  b'00tttttsssssssss
 * 
 * 9xs - 9 solenoids
 * 5xt - number of time with 50ms discrete time. 0001 = 50ms, 0011 = 150ms, etc
 * 2x0 - space
*/

#define EXTRACT_TIME_MASK 0x3E00        // Multiply with & to bet time-related bits
#define EXTRACT_TIME_SHIFT 9            // Divide by to get exact time number
#define EXTRACT_TIME_DISCRETE 50        // Each time unit means this amount of milliseconds 

#define EXTRACT_SOLENOIDS_MASK 0x01FF   // Multiply with & to bet solenoids-related bits
#define SOLENOIDS_COUNT 9

class CommunicationDriver {

public:
    
    CommunicationDriver();
    bool MessageWaits();
    uint16_t ReadMessage();
    uint16_t ExtractTime(uint16_t message);
    void fillArrayFrom16BitMessage(uint16_t message, bool (&array)[NUM_OF_SOLENOIDS]);

};

#endif