/** SR74HC164.c
 * v.1.1
 */

#include "SR74HC164.h"

void SR74HC164Initialize() {
    SR74HC164ClockPinDirection = OutputPinDirection;
    SR74HC164DataPinDirection  = OutputPinDirection;
}

void SR74HC164SendByte(unsigned char value) {
    unsigned char index = 8;
    while (1) {
        index--;
        SR74HC164ClockPin = LowPinLevel;
        SR74HC164DataPin = (value & (1 << index)) ? LowPinLevel : HighPinLevel;
        SR74HC164ClockPin = HighPinLevel;
        if (!index) {
            break;
        }
    }
}
