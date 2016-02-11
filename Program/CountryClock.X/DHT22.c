/** DHT22.c
 * v.1.1
 */

#include "DHT22.h"
#include "Delay.h"

void ReadDHT22() {
    if (SendStartSignal() == DHT22TimeoutReadError) {
        DHT22ValuesAreCorrect = 0;
        DHT22ResultRead = DHT22ResponseSignalNotDetected;
        return;
    }
    unsigned char data[DHT22DataLength];
    if (ReadData(data) == DHT22TimeoutReadError) {
        DHT22ResultRead = DHT22TimeoutReadError;
        return;
    }
    unsigned char parity = 0;
    for (unsigned char i = 0; i < DHT22DataLength - 1; i++) {
        parity += data[i];
    }
    if (parity != data[DHT22DataLength - 1]) {
        DHT22ResultRead = DHT22ParityReadError;
        return;
    }
    unsigned short humidityData    = (data[0] << 8) | data[1];
    unsigned short temperatureData = (data[2] << 8) | data[3];
    DHT22HumidityValue.integerPart = 0;
    while (humidityData >= 10) {
        humidityData -= 10;
        DHT22HumidityValue.integerPart++;
    }
    DHT22HumidityValue.fractionalPart = humidityData;
    DHT22TemperatureValue.sign = (temperatureData & DHT22TemperatureSignMask) ? 1 : 0;
    if (DHT22TemperatureValue.sign) {
        temperatureData &= ~DHT22TemperatureSignMask;
    }
    DHT22TemperatureValue.integerPart = 0;
    while (temperatureData >= 10) {
        temperatureData -= 10;
        DHT22TemperatureValue.integerPart++;
    }
    DHT22TemperatureValue.fractionalPart = (unsigned char)temperatureData;
    DHT22ValuesAreCorrect = 1;
    DHT22ResultRead = DHT22OperationOK;
}

DHT22ErrorCodes SendStartSignal() {
    DHT22PinDirection = OutputPinDirection;
    DHT22Pin = LowPinLevel;
    __delay_ms(DHT22_T_be);
    DHT22PinDirection = InputPinDirection;
    __delay_us(DHT22_T_go);
    if (WaitLowHigh() == DHT22TimeoutReadError) {
        return DHT22TimeoutReadError;
    }
    return DHT22OperationOK;
}

DHT22ErrorCodes WaitLowHigh() {
    unsigned char timeout = 0;
    while (DHT22Pin == HighPinLevel) {
        __delay_us(1);
        if (++timeout > DHT22Timeout) {
            return DHT22TimeoutReadError;
        }
    }
    timeout = 0;
    while (DHT22Pin == LowPinLevel) {
        __delay_us(1);
        if (++timeout > DHT22Timeout) {
            return DHT22TimeoutReadError;
        }
    }
    return DHT22OperationOK;
}

DHT22ErrorCodes ReadData(unsigned char data[]) {
    DHT22PinDirection = InputPinDirection;
    for (unsigned char i = 0; i < DHT22DataLength; i++) {
        if (ReadByte(&data[i]) == DHT22TimeoutReadError) {
            return DHT22TimeoutReadError;
        }
    }
    return DHT22OperationOK;
}

DHT22ErrorCodes ReadByte(unsigned char* byte) {
    for (unsigned char i = 0; i < 8; i++) {
        if (WaitLowHigh() == DHT22TimeoutReadError) {
            return DHT22TimeoutReadError;
        }
        __delay_us(DHT22_T_H0);
        *byte <<= 1;
        if (DHT22Pin == HighPinLevel) {
            *byte |= 1;
        }
    }
    return DHT22OperationOK;
}
