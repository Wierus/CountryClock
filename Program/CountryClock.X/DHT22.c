/** DHT22.c
 * v.1.0
 */

#include "DHT22.h"
#include "Delay.h"

DHT22ErrorCodes ReadDHT22(DHT22Humidity* humidityValue, DHT22Temperature* temperatureValue) {
    if (SendStartSignal() == DHT22TimeoutReadError) {
        return DHT22ResponseSignalNotDetected;
    }
    unsigned char data[DHT22DataLength];
    if (ReadData(data) == DHT22TimeoutReadError) {
        return DHT22TimeoutReadError;
    }
    unsigned char parity = 0;
    for (unsigned char i = 0; i < DHT22DataLength - 1; i++) {
        parity += data[i];
    }
    if (parity != data[DHT22DataLength - 1]) {
        return DHT22ParityReadError;
    }
    unsigned short humidityData    = (data[0] << 8) | data[1];
    unsigned short temperatureData = (data[2] << 8) | data[3];
    humidityValue -> integerPart = 0;
    while (humidityData >= 10) {
        humidityData -= 10;
        humidityValue -> integerPart++;
    }
    humidityValue -> fractionalPart = humidityData;
    temperatureValue -> sign = (temperatureData & DHT22TemperatureSignMask) ? 1 : 0;
    if (temperatureValue -> sign) {
        temperatureData &= ~DHT22TemperatureSignMask;
    }
    temperatureValue -> integerPart = 0;
    while (temperatureData >= 10) {
        temperatureData -= 10;
        temperatureValue -> integerPart++;
    }
    temperatureValue -> fractionalPart = (unsigned char)temperatureData;
    return DHT22OperationOK;
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
