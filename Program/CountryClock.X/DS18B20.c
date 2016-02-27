/** DS18B20.c
 * v.1.6
 */

#include "DS18B20.h"

void DS18B20WriteScratchpad() {
    if (OneWireResetPulse() != OneWirePrecencePulse) {
        DS18B20LastError = DS18B20PrecencePulseNotDetected;
        DS18B20TemperatureValueIsCorrect = 0;
        return;
    }
    OneWireWriteByte(DS18B20SkipROMCommand);
    OneWireWriteByte(DS18B20WriteScratchpadCommand);
    OneWireWriteByte(DS18B20ScratchpadByte2);
    OneWireWriteByte(DS18B20ScratchpadByte3);
    OneWireWriteByte(DS18B20DesiredResolution);
    DS18B20LastError = DS18B20OperationOK;
}

void DS18B20ConvertT() {
    if (OneWireResetPulse() != OneWirePrecencePulse) {
        DS18B20LastError = DS18B20PrecencePulseNotDetected;
        DS18B20TemperatureValueIsCorrect = 0;
        return;
    }
    OneWireWriteByte(DS18B20SkipROMCommand);
    OneWireWriteByte(DS18B20ConvertTCommand);
    DS18B20LastError = DS18B20OperationOK;
}

void DS18B20ReadScratchpad() {
    if (OneWireResetPulse() != OneWirePrecencePulse) {
        DS18B20LastError = DS18B20PrecencePulseNotDetected;
        DS18B20TemperatureValueIsCorrect = 0;
        return;
    }
    OneWireWriteByte(DS18B20SkipROMCommand);
    OneWireWriteByte(DS18B20ReadScratchpadCommand);
    unsigned char DS18B20ScratchpadMemory[DS18B20ScratchpadLength];
    unsigned char crc = OneWireCRC8Init;
    for (unsigned char i = 0; i < DS18B20ScratchpadLength; i++) {
        DS18B20ScratchpadMemory[i] = OneWireReadByte();
        crc = OneWireCRC8(DS18B20ScratchpadMemory[i], crc);
    }
    if (
        (crc                        != 0)                        ||
        (DS18B20ScratchpadMemory[2] != DS18B20ScratchpadByte2)   ||
        (DS18B20ScratchpadMemory[3] != DS18B20ScratchpadByte3)   ||
        (DS18B20ScratchpadMemory[4] != DS18B20DesiredResolution) ||
        (DS18B20ScratchpadMemory[5] != DS18B20ScratchpadByte5)   ||
        (DS18B20ScratchpadMemory[7] != DS18B20ScratchpadByte7)
    ) {
        DS18B20LastError = DS18B20ScratchpadReadError;
        DS18B20ReadErrorsCount++;
        if (DS18B20ReadErrorsCount > DS18B20MaxReadErrorsCount) {
            DS18B20TemperatureValueIsCorrect = 0;
        }
        return;
    }
    unsigned short temperatureRegister = (DS18B20ScratchpadMemory[1] << 8) | DS18B20ScratchpadMemory[0];
    DS18B20TemperatureValue.sign = (DS18B20ScratchpadMemory[1] & DS18B20TemperatureSignMask) ? 1 : 0;
    if (DS18B20TemperatureValue.sign) {
        temperatureRegister = (~temperatureRegister) + 1;
    }
    DS18B20TemperatureValue.integerPart = temperatureRegister >> DS18B20TemperatureFractionalPartMaskBitsCount;
    DS18B20TemperatureValue.fractionalPart = (temperatureRegister & DS18B20TemperatureFractionalPartMask) * (10000 / 16);
    DS18B20LastError = DS18B20OperationOK;
    DS18B20ReadErrorsCount = 0;
    DS18B20TemperatureValueIsCorrect = 1;
}

void DS18B20SetResolution(DS18B20ThermometerResolutions resolution) {
    DS18B20DesiredResolution = resolution;
}
