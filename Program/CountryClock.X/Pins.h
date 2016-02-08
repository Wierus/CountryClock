#ifndef PINS_H
#define	PINS_H

#include <xc.h>

#define OutputPinDirection 0
#define InputPinDirection  1

#define LowPinLevel  0
#define HighPinLevel 1

// Выводы индикатора (слева направо)
#define Indicator0Pin          RB0
#define Indicator0PinDirection TRISB0
#define Indicator1Pin          RB1
#define Indicator1PinDirection TRISB1
#define Indicator2Pin          RB2
#define Indicator2PinDirection TRISB2
#define Indicator3Pin          RB3
#define Indicator3PinDirection TRISB3
#define Indicator4Pin          RB4
#define Indicator4PinDirection TRISB4

// Маски сегментов индикатора
#define SevenSegmentDisplaySAMask 0b00000001
#define SevenSegmentDisplaySBMask 0b00000010
#define SevenSegmentDisplaySCMask 0b00000100
#define SevenSegmentDisplaySDMask 0b00001000
#define SevenSegmentDisplaySEMask 0b00010000
#define SevenSegmentDisplaySFMask 0b00100000
#define SevenSegmentDisplaySGMask 0b01000000
#define SevenSegmentDisplaySHMask 0b10000000

// Выводы сдвигового регистра
#define SR74HC164ClockPin          RB6
#define SR74HC164ClockPinDirection TRISB6
#define SR74HC164DataPin           RB7
#define SR74HC164DataPinDirection  TRISB7

// Выводы кнопок
#define ButtonHoursPin            RA0
#define ButtonHoursPinDirection   TRISA0
#define ButtonMinutesPin          RA1
#define ButtonMinutesPinDirection TRISA1
#define ButtonModePin             RA2
#define ButtonModePinDirection    TRISA2

// Значение вывода кнопки при нажатом состоянии
#define ButtonPressed 0

// Вывод шины 1-Wire
#define OneWirePin          RA3
#define OneWirePinDirection TRISA3

// Вывод датчика DHT22
#define DHT22Pin          RB5
#define DHT22PinDirection TRISB5

// Вывод наличия питания
#define PowerStatePin          RA4
#define PowerStatePinDirection TRISA4

// Состояния питания
#define PowerOn  1
#define PowerOff 0

#endif /* PINS_H */
