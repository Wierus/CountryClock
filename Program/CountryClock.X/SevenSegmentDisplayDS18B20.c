/** SevenSegmentDisplayDS18B20.c
 * v.1.4
 */

#include "SevenSegmentDisplayDS18B20.h"
#include "SevenSegmentDisplay.h"
#include "DS18B20.h"
#include "Math.h"

void FillIndicators3WithDS18B20Temperature(unsigned char* indicatorValues) {
    if (DS18B20ResultGetTemperature == DS18B20PrecencePulseNotDetected) {
        FillIndicators3WithSymbolLine(indicatorValues);
    }
    else {
        if (DS18B20TemperatureValueIsCorrect) {
            FillIndicators3WithNumber(indicatorValues, DS18B20TemperatureValue.sign, DS18B20TemperatureValue.integerPart);
        }
        else {
            FillIndicators3WithSymbolLine(indicatorValues);
        }
        if (DS18B20ResultGetTemperature != DS18B20OperationOK) {
            indicatorValues[2] |= SymbolDot;
        }
    }
}

void FillIndicators3AndSignWithDS18B20Temperature(unsigned char* indicatorValues, unsigned char* indicatorSign) {
    if (DS18B20ResultGetTemperature == DS18B20PrecencePulseNotDetected) {
        *indicatorSign = 0;
        FillIndicators3WithSymbolLine(indicatorValues);
    }
    else {
        if (DS18B20TemperatureValueIsCorrect) {
            FillIndicators3AndSignWithNumber(indicatorValues, indicatorSign, DS18B20TemperatureValue.sign, DS18B20TemperatureValue.integerPart, GetD3OfU16(DS18B20TemperatureValue.fractionalPart));
        }
        else {
            *indicatorSign = 0;
            FillIndicators3WithSymbolLine(indicatorValues);
        }
        if (DS18B20ResultGetTemperature != DS18B20OperationOK) {
            indicatorValues[2] |= SymbolDot;
        }
    }
}

void FillIndicators5WithDS18B20TemperatureAndSymbolDegree(unsigned char* indicatorValues) {
    indicatorValues[4] = SymbolDegree;
    if (DS18B20ResultGetTemperature == DS18B20PrecencePulseNotDetected) {
        FillIndicators4WithSymbolLine(indicatorValues);
    }
    else {
        if (DS18B20TemperatureValueIsCorrect) {
            FillIndicators4WithNumber(indicatorValues, DS18B20TemperatureValue.sign, DS18B20TemperatureValue.integerPart, GetD3OfU16(DS18B20TemperatureValue.fractionalPart));
        }
        else {
            FillIndicators4WithSymbolLine(indicatorValues);
        }
        if (DS18B20ResultGetTemperature != DS18B20OperationOK) {
            indicatorValues[4] |= SymbolDot;
        }
    }
}
