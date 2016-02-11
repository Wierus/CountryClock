/** SevenSegmentDisplay.c
 * v.1.3
 */

#include "SevenSegmentDisplay.h"
#include "Math.h"

unsigned char GetIndicatorDigit(unsigned char digit) {
    switch (digit) {
        case 0: {
            return SymbolDigit0;
        }
        case 1: {
            return SymbolDigit1;
        }
        case 2: {
            return SymbolDigit2;
        }
        case 3: {
            return SymbolDigit3;
        }
        case 4: {
            return SymbolDigit4;
        }
        case 5: {
            return SymbolDigit5;
        }
        case 6: {
            return SymbolDigit6;
        }
        case 7: {
            return SymbolDigit7;
        }
        case 8: {
            return SymbolDigit8;
        }
        case 9: {
            return SymbolDigit9;
        }
        default: {
            return SymbolNull;
        }
    }
}

void FillIndicators1WithSymbolNull(unsigned char* indicatorValues) {
    indicatorValues[0] = SymbolNull;
}

void FillIndicators2WithSymbolNull(unsigned char* indicatorValues) {
    indicatorValues[0] = SymbolNull;
    indicatorValues[1] = SymbolNull;
}

void FillIndicators3WithSymbolNull(unsigned char* indicatorValues) {
    indicatorValues[0] = SymbolNull;
    indicatorValues[1] = SymbolNull;
    indicatorValues[2] = SymbolNull;
}

void FillIndicators4WithSymbolNull(unsigned char* indicatorValues) {
    indicatorValues[0] = SymbolNull;
    indicatorValues[1] = SymbolNull;
    indicatorValues[2] = SymbolNull;
    indicatorValues[3] = SymbolNull;
}

void FillIndicators5WithSymbolNull(unsigned char* indicatorValues) {
    indicatorValues[0] = SymbolNull;
    indicatorValues[1] = SymbolNull;
    indicatorValues[2] = SymbolNull;
    indicatorValues[3] = SymbolNull;
    indicatorValues[4] = SymbolNull;
}

void FillIndicators1WithSymbolLine(unsigned char* indicatorValues) {
    indicatorValues[0] = SymbolLine;
}

void FillIndicators2WithSymbolLine(unsigned char* indicatorValues) {
    indicatorValues[0] = SymbolLine;
    indicatorValues[1] = SymbolLine;
}

void FillIndicators3WithSymbolLine(unsigned char* indicatorValues) {
    indicatorValues[0] = SymbolLine;
    indicatorValues[1] = SymbolLine;
    indicatorValues[2] = SymbolLine;
}

void FillIndicators4WithSymbolLine(unsigned char* indicatorValues) {
    indicatorValues[0] = SymbolLine;
    indicatorValues[1] = SymbolLine;
    indicatorValues[2] = SymbolLine;
    indicatorValues[3] = SymbolLine;
}

void FillIndicators5WithSymbolLine(unsigned char* indicatorValues) {
    indicatorValues[0] = SymbolLine;
    indicatorValues[1] = SymbolLine;
    indicatorValues[2] = SymbolLine;
    indicatorValues[3] = SymbolLine;
    indicatorValues[4] = SymbolLine;
}

void FillIndicators3WithNumber(unsigned char* indicatorValues, unsigned char sign, unsigned char number) {
    if (number >= 100) {
        // [100; 255]
        // Формат: d2 d1 d0
        indicatorValues[0] = GetIndicatorDigit(GetD2OfU08(number));
        indicatorValues[1] = GetIndicatorDigit(GetD1OfU08(number));
    }
    else if (number >= 10) {
        // [-99; -10] и [10; 100)
        // Формат: s d1 d0
        indicatorValues[0] = sign ? SymbolLine : SymbolNull;
        indicatorValues[1] = GetIndicatorDigit(GetD1OfU08(number));
    }
    else {
        // (-10; 0) и [0; 10)
        // Формат: _ s d0
        indicatorValues[0] = SymbolNull;
        indicatorValues[1] = sign ? SymbolLine : SymbolNull;
    }
    indicatorValues[2] = GetIndicatorDigit(GetD0OfU08(number));
}

void FillIndicators3AndSignWithNumber(unsigned char* indicatorValues, unsigned char* indicatorSign, unsigned char sign, unsigned char number, unsigned char fractionalPart) {
    if (number >= 100) {
        // [100; 255]
        // Формат: s d2 d1 d0
        *indicatorSign = 0;
        indicatorValues[0] = GetIndicatorDigit(GetD2OfU08(number));
        indicatorValues[1] = GetIndicatorDigit(GetD1OfU08(number));
        indicatorValues[2] = GetIndicatorDigit(GetD0OfU08(number));
    }
    else if (number >= 10) {
        // [-99.9; -10] и [10; 99.9]
        // Формат: s d1 d0. f0
        *indicatorSign = sign;
        indicatorValues[0] = GetIndicatorDigit(GetD1OfU08(number));
        indicatorValues[1] = GetIndicatorDigit(GetD0OfU08(number)) | SymbolDot;
        indicatorValues[2] = GetIndicatorDigit(GetD0OfU08(fractionalPart));
    }
    else {
        // (-10; 0) и [0; 10)
        // Формат: _ s d0. f0
        *indicatorSign = 0;
        indicatorValues[0] = sign ? SymbolLine : SymbolNull;
        indicatorValues[1] = GetIndicatorDigit(GetD0OfU08(number)) | SymbolDot;
        indicatorValues[2] = GetIndicatorDigit(GetD0OfU08(fractionalPart));
    }
}

void FillIndicators4WithNumber(unsigned char* indicatorValues, unsigned char sign, unsigned char number, unsigned char fractionalPart) {
    if (number >= 100) {
        // [100; 255]
        // Формат: d2 d1 d0. f0
        indicatorValues[0] = GetIndicatorDigit(GetD2OfU08(number));
        indicatorValues[1] = GetIndicatorDigit(GetD1OfU08(number));
    }
    else if (number >= 10) {
        // [-99.9; -10] или [10; 99.9]
        // Формат: s d1 d0. f0
        indicatorValues[0] = sign ? SymbolLine : SymbolNull;
        indicatorValues[1] = GetIndicatorDigit(GetD1OfU08(number));
    }
    else {
        // (-10; 0) или [0; 10)
        // Формат: _ s d0. f0
        indicatorValues[0] = SymbolNull;
        indicatorValues[1] = sign ? SymbolLine : SymbolNull;
    }
    indicatorValues[2] = GetIndicatorDigit(GetD0OfU08(number)) | SymbolDot;
    indicatorValues[3] = GetIndicatorDigit(GetD0OfU08(fractionalPart));
}
