/** SevenSegmentDisplayDS18B20.c
 * v.1.5
 */

#include "SevenSegmentDisplayDS18B20.h"

void FillIndicators3WithDS18B20Temperature(unsigned char* indicatorValues) {
    if (DS18B20TemperatureValueIsCorrect) {
        FillIndicators3WithNumber(indicatorValues, DS18B20TemperatureValue.sign, DS18B20TemperatureValue.integerPart);
    }
    else {
        FillIndicators3WithSymbolLine(indicatorValues);
    }
    if (DS18B20LastError == DS18B20ScratchpadReadError) {
        indicatorValues[2] |= SymbolDot;
    }
}

void FillIndicators3AndSignWithDS18B20Temperature(unsigned char* indicatorValues, unsigned char* indicatorSign) {
    if (DS18B20TemperatureValueIsCorrect) {
        FillIndicators3AndSignWithNumber(indicatorValues, indicatorSign, DS18B20TemperatureValue.sign, DS18B20TemperatureValue.integerPart, GetD3OfU16(DS18B20TemperatureValue.fractionalPart));
    }
    else {
        *indicatorSign = 0;
        FillIndicators3WithSymbolLine(indicatorValues);
    }
    if (DS18B20LastError == DS18B20ScratchpadReadError) {
        indicatorValues[2] |= SymbolDot;
    }
}

void FillIndicators5WithDS18B20TemperatureAndSymbolDegree(unsigned char* indicatorValues) {
    indicatorValues[4] = SymbolDegree;
    if (DS18B20TemperatureValueIsCorrect) {
        FillIndicators4WithNumber(indicatorValues, DS18B20TemperatureValue.sign, DS18B20TemperatureValue.integerPart, GetD3OfU16(DS18B20TemperatureValue.fractionalPart));
    }
    else {
        FillIndicators4WithSymbolLine(indicatorValues);
    }
    if (DS18B20LastError == DS18B20ScratchpadReadError) {
        indicatorValues[4] |= SymbolDot;
    }
}
