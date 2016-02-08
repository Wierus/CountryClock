/** DS18B20.c
 * v.1.2
 */

#include "DS18B20.h"
#include "OneWire.h"

DS18B20ErrorCodes DS18B20SendConvertTCommand() {
    if (OneWireResetPulse() != OneWirePrecencePulse) {
        return DS18B20PrecencePulseNotDetected;
    }
    OneWireWriteByte(DS18B20SkipROMCommand);
    OneWireWriteByte(DS18B20ConvertTCommand);
    return DS18B20OperationOK;
}

DS18B20ErrorCodes DS18B20SendReadScratchpadCommand() {
    if (OneWireResetPulse() != OneWirePrecencePulse) {
        return DS18B20PrecencePulseNotDetected;
    }
    OneWireWriteByte(DS18B20SkipROMCommand);
    OneWireWriteByte(DS18B20ReadScratchpadCommand);
    unsigned char DS18B20ScratchpadMemory[DS18B20ScratchpadLength];
    unsigned char crc = OneWireCRC8Init;
    for (unsigned char i = 0; i < DS18B20ScratchpadLength; i++) {
        DS18B20ScratchpadMemory[i] = OneWireReadByte();
        crc = OneWireCRC8(DS18B20ScratchpadMemory[i], crc);
    }
    if (crc != 0) {
        return DS18B20CRCReadError;
    }
    if (DS18B20ScratchpadMemory[5] != DS18B20ScratchpadByte5) {
        return DS18B20Byte5ReadError;
    }
    if (DS18B20ScratchpadMemory[7] != DS18B20ScratchpadByte7) {
        return DS18B20Byte7ReadError;
    }
    if (DS18B20ScratchpadMemory[4] != DS18B20DesiredResolution) {
        DS18B20WriteScratchpad();
        return DS18B20Byte4ReadError;
    }
    if (DS18B20ScratchpadMemory[2] != DS18B20ScratchpadByte2) {
        DS18B20WriteScratchpad();
        return DS18B20Byte2ReadError;
    }
    if (DS18B20ScratchpadMemory[3] != DS18B20ScratchpadByte3) {
        DS18B20WriteScratchpad();
        return DS18B20Byte3ReadError;
    }
    unsigned short temperatureRegister = (DS18B20ScratchpadMemory[1] << 8) | DS18B20ScratchpadMemory[0];
    DS18B20TemperatureValue.sign = (DS18B20ScratchpadMemory[1] & DS18B20TemperatureSignMask) ? 1 : 0;
    if (DS18B20TemperatureValue.sign) {
        temperatureRegister = (~temperatureRegister) + 1;
    }
    DS18B20TemperatureValue.integerPart = temperatureRegister >> DS18B20TemperatureFractionalPartMaskBitsCount;
    DS18B20TemperatureValue.fractionalPart = (temperatureRegister & DS18B20TemperatureFractionalPartMask) * (10000 / 16);
    return DS18B20OperationOK;
}

DS18B20ErrorCodes DS18B20WriteScratchpad() {
    if (OneWireResetPulse() != OneWirePrecencePulse) {
        return DS18B20PrecencePulseNotDetected;
    }
    OneWireWriteByte(DS18B20SkipROMCommand);
    OneWireWriteByte(DS18B20WriteScratchpadCommand);
    OneWireWriteByte(DS18B20ScratchpadByte2);
    OneWireWriteByte(DS18B20ScratchpadByte3);
    OneWireWriteByte(DS18B20DesiredResolution);
    return DS18B20OperationOK;
}

void DS18B20SetResolution(DS18B20ThermometerResolutions resolution) {
    DS18B20DesiredResolution = resolution;
}

void DS18B20InitializeSensor() {
    DS18B20ResultGetTemperature = DS18B20SendReadScratchpadCommand();
    switch (DS18B20ResultGetTemperature) {
        case DS18B20OperationOK:
        case DS18B20Byte2ReadError:
        case DS18B20Byte3ReadError:
        case DS18B20Byte4ReadError: {
            DS18B20ResultInitializeSensor = DS18B20OperationOK;
            break;
        }
        default: {
            DS18B20ResultInitializeSensor = DS18B20ResultGetTemperature;
            break;
        }
    }
    DS18B20TemperatureValueIsCorrect = 0;
}

void DS18B20ConvertTemperature() {
    DS18B20ResultConvertTemperature = DS18B20SendConvertTCommand();
    if (DS18B20ResultConvertTemperature == DS18B20PrecencePulseNotDetected) {
        DS18B20TemperatureValueIsCorrect = 0;
    }
}

void DS18B20GetTemperature() {
    if (DS18B20ResultConvertTemperature == DS18B20OperationOK) {
        DS18B20ResultGetTemperature = DS18B20SendReadScratchpadCommand();
        if (DS18B20ResultGetTemperature == DS18B20OperationOK) {
            DS18B20TemperatureValueIsCorrect = 1;
        }
        else {
            DS18B20TemperatureValueIsCorrect = 0;
        }
    }
    else {
        DS18B20ResultGetTemperature = DS18B20ConvertTemperatureError;
        DS18B20TemperatureValueIsCorrect = 0;
    }
}
