#include "SevenSegmentDisplay.h"

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
