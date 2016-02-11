/** SevenSegmentDisplay.h
 * v.1.3
 */

#ifndef SEVENSEGMENTDISPLAY_H
#define	SEVENSEGMENTDISPLAY_H

#include "Pins.h"

#ifndef SevenSegmentDisplaySAMask
    #error "SevenSegmentDisplaySAMask symbol is not defined, you should define it in file Pins.h before using this library"
#endif

#ifndef SevenSegmentDisplaySBMask
    #error "SevenSegmentDisplaySBMask symbol is not defined, you should define it in file Pins.h before using this library"
#endif

#ifndef SevenSegmentDisplaySCMask
    #error "SevenSegmentDisplaySCMask symbol is not defined, you should define it in file Pins.h before using this library"
#endif

#ifndef SevenSegmentDisplaySDMask
    #error "SevenSegmentDisplaySDMask symbol is not defined, you should define it in file Pins.h before using this library"
#endif

#ifndef SevenSegmentDisplaySEMask
    #error "SevenSegmentDisplaySEMask symbol is not defined, you should define it in file Pins.h before using this library"
#endif

#ifndef SevenSegmentDisplaySFMask
    #error "SevenSegmentDisplaySFMask symbol is not defined, you should define it in file Pins.h before using this library"
#endif

#ifndef SevenSegmentDisplaySGMask
    #error "SevenSegmentDisplaySGMask symbol is not defined, you should define it in file Pins.h before using this library"
#endif

#ifndef SevenSegmentDisplaySHMask
    #error "SevenSegmentDisplaySHMask symbol is not defined, you should define it in file Pins.h before using this library"
#endif

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

    SegmentA = SevenSegmentDisplaySAMask,
    SegmentB = SevenSegmentDisplaySBMask,
    SegmentC = SevenSegmentDisplaySCMask,
    SegmentD = SevenSegmentDisplaySDMask,
    SegmentE = SevenSegmentDisplaySEMask,
    SegmentF = SevenSegmentDisplaySFMask,
    SegmentG = SevenSegmentDisplaySGMask,
    SegmentH = SevenSegmentDisplaySHMask,
    
} IndicatorSegments;

/** Символы на индикаторе.
 */
typedef enum IndicatorSymbols {

    SymbolNull         = 0,
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

void FillIndicators1WithSymbolNull(unsigned char* indicatorValues);

void FillIndicators2WithSymbolNull(unsigned char* indicatorValues);

void FillIndicators3WithSymbolNull(unsigned char* indicatorValues);

void FillIndicators4WithSymbolNull(unsigned char* indicatorValues);

void FillIndicators5WithSymbolNull(unsigned char* indicatorValues);

/* Выводит символ "Минус" на 1 семисегментный индикатор.
 * @param indicatorValues Массив, в который будут выведены символы. Массив должен иметь длину равную одному.
 */
void FillIndicators1WithSymbolLine(unsigned char* indicatorValues);

/* Выводит символ "Минус" на 2 семисегментных индикатора.
 * @param indicatorValues Массив, в который будут выведены символы. Массив должен иметь длину равную двум.
 */
void FillIndicators2WithSymbolLine(unsigned char* indicatorValues);

/* Выводит символ "Минус" на 3 семисегментных индикатора.
 * @param indicatorValues Массив, в который будут выведены символы. Массив должен иметь длину равную трем.
 */
void FillIndicators3WithSymbolLine(unsigned char* indicatorValues);

/* Выводит символ "Минус" на 4 семисегментных индикатора.
 * @param indicatorValues Массив, в который будут выведены символы. Массив должен иметь длину равную четырем.
 */
void FillIndicators4WithSymbolLine(unsigned char* indicatorValues);

/* Выводит символ "Минус" на 5 семисегментных индикатора.
 * @param indicatorValues Массив, в который будут выведены символы. Массив должен иметь длину равную пяти.
 */
void FillIndicators5WithSymbolLine(unsigned char* indicatorValues);

/** Выводит число в диапазоне от -99 до 255 с шагом 1 на 3 семисегментных индикатора.
 * @param indicatorValues Массив, в который будут выведены символы. Массив должен иметь длину равную трем.
 * @param sign Отрицательный знак числа. 0 - положительное значение или ноль, 1 - отрицательное значение.
 * @param number Модуль выводимого числа в диапазоне от 0 до 255.
 */
void FillIndicators3WithNumber(unsigned char* indicatorValues, unsigned char sign, unsigned char number);

/** Выводит число в диапазоне от -99.9 до 99.9 с шагом 0.1 или в диапазоне от 100 до 255 с шагом 1 на индикатор символа "минус" и 3 семисегментных индикатора.
 * @param indicatorValues Массив, в который будут выведены символы. Массив должен иметь длину равную трем.
 * @param indicatorSign Указатель на переменную, в которую будет записано состояние индикатора символа "минус" (включен или выключен).
 * @param sign Отрицательный знак числа. 0 - положительное значение или ноль, 1 - отрицательное значение.
 * @param number Модуль выводимого числа в диапазоне от 0 до 255 (целая часть).
 * @param fractionalPart Дробная часть выводимого числа от 0 до 9.
 */
void FillIndicators3AndSignWithNumber(unsigned char* indicatorValues, unsigned char* indicatorSign, unsigned char sign, unsigned char number, unsigned char fractionalPart);

/** Выводит число в диапазоне от -99.9 до 255.0 с шагом 0.1 на 4 семисегментных индикатора.
 * @param indicatorValues Массив, в который будут выведены символы. Массив должен иметь длину равную четырем.
 * @param sign Отрицательный знак числа. 0 - положительное значение или ноль, 1 - отрицательное значение.
 * @param number Модуль выводимого числа в диапазоне от 0 до 255 (целая часть).
 * @param fractionalPart Дробная часть выводимого числа от 0 до 9.
 */
void FillIndicators4WithNumber(unsigned char* indicatorValues, unsigned char sign, unsigned char number, unsigned char fractionalPart);

#endif /* SEVENSEGMENTDISPLAY_H */
