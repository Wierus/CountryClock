#ifndef SEVENSEGMENTDISPLAY_H
#define	SEVENSEGMENTDISPLAY_H

/** Значения вывода индикатора с общим анодом для его включения.
 */
#define IndicatorCAOn  1

/** Значение вывода индикатора с общим анодом для его выключения.
 */
#define IndicatorCAOff 0

/** Значение вывода сегмента индикатора с общим анодом для его включения.
 */
#define SegmentCAOn    0

/** Значение вывода сегмента индикатора с общим анодом для его выключения.
 */
#define SegmentCAOff   1

/** Значение вывода индикатора с общим катодом для его включения.
 */
#define IndicatorCCOn  0

/** Значение вывода индикатора с общим катодом для его выключения.
 */
#define IndicatorCCOff 1

/** Значение вывода сегмента индикатора с общим катодом для его включения.
 */
#define SegmentCCOn    1

/** Значение вывода сегмента индикатора с общим катодом для его выключения.
 */
#define SegmentCCOff   0

/** Сегменты на индикаторе.
 */
typedef enum IndicatorSegments {

    SegmentA = 0b00000001,
    SegmentB = 0b00000010,
    SegmentC = 0b00000100,
    SegmentD = 0b00001000,
    SegmentE = 0b00010000,
    SegmentF = 0b00100000,
    SegmentG = 0b01000000,
    SegmentH = 0b10000000,

} IndicatorSegments;

/** Символы на индикаторе.
 */
typedef enum IndicatorSymbols {

    SymbolNull         = 0b00000000,
    SymbolDigit0       = SegmentA | SegmentB | SegmentC | SegmentD | SegmentE | SegmentF,
    SymbolDigit1       = SegmentB | SegmentC,
    SymbolDigit2       = SegmentA | SegmentB | SegmentD | SegmentE | SegmentG,
    SymbolDigit3       = SegmentA | SegmentB | SegmentC | SegmentD | SegmentG,
    SymbolDigit4       = SegmentB | SegmentC | SegmentF | SegmentG,
    SymbolDigit5       = SegmentA | SegmentC | SegmentD | SegmentF | SegmentG,
    SymbolDigit6       = SegmentA | SegmentC | SegmentD | SegmentE | SegmentF | SegmentG,
    SymbolDigit7       = SegmentA | SegmentB | SegmentC,
    SymbolDigit8       = SegmentA | SegmentB | SegmentC | SegmentD | SegmentE | SegmentF | SegmentG,
    SymbolDigit9       = SegmentA | SegmentB | SegmentC | SegmentD | SegmentF | SegmentG,
    SymbolUpperLetterA = SegmentA | SegmentB | SegmentC | SegmentE | SegmentF | SegmentG,
    SymbolLowerLetterB = SegmentC | SegmentD | SegmentE | SegmentF | SegmentG,
    SymbolUpperLetterC = SegmentA | SegmentD | SegmentE | SegmentF,
    SymbolLowerLetterC = SegmentD | SegmentE | SegmentG,
    SymbolLowerLetterD = SegmentB | SegmentC | SegmentD | SegmentE | SegmentG,
    SymbolUpperLetterE = SegmentA | SegmentD | SegmentE | SegmentF | SegmentG,
    SymbolUpperLetterF = SegmentA | SegmentE | SegmentF | SegmentG,
    SymbolUpperLetterH = SegmentB | SegmentC | SegmentE | SegmentF | SegmentG,
    SymbolLowerLetterH = SegmentC | SegmentE | SegmentF | SegmentG,
    SymbolUpperLetterJ = SegmentB | SegmentC | SegmentD | SegmentE,
    SymbolUpperLetterL = SegmentD | SegmentE | SegmentF,
    SymbolLowerLetterO = SegmentC | SegmentD | SegmentE | SegmentG,
    SymbolUpperLetterP = SegmentA | SegmentB | SegmentE | SegmentF | SegmentG,
    SymbolLowerLetterT = SegmentD | SegmentE | SegmentF | SegmentG,
    SymbolUpperLetterU = SegmentB | SegmentC | SegmentD | SegmentE | SegmentF,
    SymbolLowerLetterU = SegmentC | SegmentD | SegmentE,
    SymbolUpperLetterY = SegmentB | SegmentC | SegmentD | SegmentF | SegmentG,
    SymbolDot          = SegmentH,
    SymbolLine         = SegmentG,
    SymbolDegree       = SegmentA | SegmentB | SegmentF | SegmentG,
    SymbolAll          = SegmentA | SegmentB | SegmentC | SegmentD | SegmentE | SegmentF | SegmentG | SegmentH,

} IndicatorSymbols;

unsigned char GetIndicatorDigit(unsigned char digit);

#endif /* SEVENSEGMENTDISPLAY_H */
