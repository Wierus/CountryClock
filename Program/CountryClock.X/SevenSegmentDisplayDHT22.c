/** SevenSegmentDisplayDHT22.c
 * v.1.0
 */

#include "SevenSegmentDisplayDHT22.h"
#include "SevenSegmentDisplay.h"
#include "DHT22.h"
#include "Math.h"

void FillIndicators5WithDHT22HumidityAndSymbolLowerLetterH(unsigned char* indicatorValues) {
    indicatorValues[4] = SymbolLowerLetterH;
    if (DHT22ResultRead == DHT22ResponseSignalNotDetected) {
        FillIndicators4WithSymbolLine(indicatorValues);
    }
    else {
        if (DHT22ValuesAreCorrect) {
            FillIndicators4WithNumber(indicatorValues, 0, DHT22HumidityValue.integerPart, DHT22HumidityValue.fractionalPart);
        }
        else {
            FillIndicators4WithSymbolLine(indicatorValues);
        }
        if (DHT22ResultRead != DHT22OperationOK) {
            indicatorValues[4] |= SymbolDot;
        }
    }
}

void FillIndicators5WithDHT22TemperatureAndSymbolDegree(unsigned char* indicatorValues) {
    indicatorValues[4] = SymbolDegree;
    if (DHT22ResultRead == DHT22ResponseSignalNotDetected) {
        FillIndicators4WithSymbolLine(indicatorValues);
    }
    else {
        if (DHT22ValuesAreCorrect) {
            FillIndicators4WithNumber(indicatorValues, DHT22TemperatureValue.sign, DHT22TemperatureValue.integerPart, DHT22TemperatureValue.fractionalPart);
        }
        else {
            FillIndicators4WithSymbolLine(indicatorValues);
        }
        if (DHT22ResultRead != DHT22OperationOK) {
            indicatorValues[4] |= SymbolDot;
        }
    }
}
