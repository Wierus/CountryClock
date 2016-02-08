/** OneWire.c
 * v.1.0
 */

#include "OneWire.h"
#include "Delay.h"

void OneWireDriveBusLow() {
    OneWirePinDirection = OutputPinDirection;
    OneWirePin = LowPinLevel;
}

void OneWireReleaseBus() {
    OneWirePinDirection = InputPinDirection;
}

bit OneWireSampleBus() {
    return OneWirePin;
}

bit OneWireResetPulse() {
    unsigned char result;
    __delay_us(OneWireTimeG);
    OneWireDriveBusLow();
    __delay_us(OneWireTimeH);
    OneWireReleaseBus();
    __delay_us(OneWireTimeI);
    result = OneWireSampleBus();
    __delay_us(OneWireTimeJ);
    return result;
}

void OneWireWriteBit0() {
    OneWireDriveBusLow();
    __delay_us(OneWireTimeC);
    OneWireReleaseBus();
    __delay_us(OneWireTimeD);
}

void OneWireWriteBit1() {
    OneWireDriveBusLow();
    __delay_us(OneWireTimeA);
    OneWireReleaseBus();
    __delay_us(OneWireTimeB);
}

bit OneWireReadBit() {
    unsigned char result;
    OneWireDriveBusLow();
    __delay_us(OneWireTimeA);
    OneWireReleaseBus();
    __delay_us(OneWireTimeE);
    result = OneWireSampleBus();
    __delay_us(OneWireTimeF);
    return result;
}

void OneWireWriteByte(unsigned char value) {
    unsigned char index = 8;
    while (1) {
        if (value & 1) {
            OneWireWriteBit1();
        }
        else {
            OneWireWriteBit0();
        }
        value >>= 1;
        if (!(--index)) {
            break;
        }
    }
}

unsigned char OneWireReadByte() {
    unsigned char value = 0;
    unsigned char index = 8;
    while (1) {
        value >>= 1;
        if (OneWireReadBit()) {
            value |= 0b10000000;
        }
        if (!(--index)) {
            break;
        }
    }
    return value;
}

unsigned char OneWireCRC8(unsigned char data, unsigned char crc) {
    for (unsigned char i = 0; i < 8; i++) {
        unsigned char mix = (crc ^ data) & 1;
		crc >>= 1;
		if (mix) {
			crc ^= OneWireCRC8Poly;
        }
		data >>= 1;
    }
    return crc;
}
