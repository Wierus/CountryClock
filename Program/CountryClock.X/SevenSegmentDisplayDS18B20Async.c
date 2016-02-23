/** SevenSegmentDisplayDS18B20Async.c
 * v.1.0
 */

#include "SevenSegmentDisplayDS18B20Async.h"

void FillIndicators3WithDS18B20Temperature(unsigned char* indicatorValues) {
    if (!OneWireHasPresencePulseDetected) {
        FillIndicators3WithSymbolLine(indicatorValues);
    }
    else {
        if (DS18B20TemperatureValueIsCorrect) {
            FillIndicators3WithNumber(indicatorValues, DS18B20TemperatureValue.sign, DS18B20TemperatureValue.integerPart);
        }
        else {
            FillIndicators3WithSymbolLine(indicatorValues);
        }
    }
}

void FillIndicators3AndSignWithDS18B20Temperature(unsigned char* indicatorValues, unsigned char* indicatorSign) {
    if (!OneWireHasPresencePulseDetected) {
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
    }
}

void FillIndicators5WithDS18B20TemperatureAndSymbolDegree(unsigned char* indicatorValues) {
    indicatorValues[4] = SymbolDegree;
    if (!OneWireHasPresencePulseDetected) {
        FillIndicators4WithSymbolLine(indicatorValues);
    }
    else {
        if (DS18B20TemperatureValueIsCorrect) {
            FillIndicators4WithNumber(indicatorValues, DS18B20TemperatureValue.sign, DS18B20TemperatureValue.integerPart, GetD3OfU16(DS18B20TemperatureValue.fractionalPart));
        }
        else {
            FillIndicators4WithSymbolLine(indicatorValues);
        }
    }
}
