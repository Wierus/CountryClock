/** OneWire.h
 * v.1.0
 */

#ifndef ONEWIRE_H
#define	ONEWIRE_H

#include "Pins.h"

#ifndef OneWirePin
    #error "OneWirePin symbol is not defined, you should define it in file Pins.h before using this library"
#endif

#ifndef OneWirePinDirection
    #error "OneWirePinDirection symbol is not defined, you should define it in file Pins.h before using this library"
#endif

// Timings by AN126 Maxim Integrated Products
#define OneWireTimeA   1
#define OneWireTimeB  64
#define OneWireTimeC  60
#define OneWireTimeD  10
#define OneWireTimeE   1
#define OneWireTimeF  55
#define OneWireTimeG   0
#define OneWireTimeH 480
#define OneWireTimeI  70
#define OneWireTimeJ 410

/** Значение логического уровня, которым устройство обозначает свое присутствует на шине после сигнала сброса (Reset pulse).
 */
#define OneWirePrecencePulse 0

/** Начальное значение CRC для вычисления CRC-8 (Dallas/Maxim).
 */
#define OneWireCRC8Init 0x00

/** Представление полинома для вычисления CRC-8 (Dallas/Maxim): x^8 + x^5 + x^4 + x^0 (0b00110001) (старший бит опущен).
 */
#define OneWireCRC8Poly 0x8C

/** Притягивает шину к низкому логическому уровню.
 */
void OneWireDriveBusLow();

/** Отпускает шину, возвращая ее в высокий логический уровень (за счет подтягивающего резистора).
 */
void OneWireReleaseBus();

/** Возвращает значение логического уровня на шине в текущий момент.
 * @return Значение логического уровня на шине в текущий момент.
 */
bit OneWireSampleBus();

/** Отправляет в шину сигнал сброса (Reset pulse).
 * @return Сигнал присутствия (Precence pulse) устройства на шине.
 */
bit OneWireResetPulse();

/** Записывает в шину бит "0".
 */
void OneWireWriteBit0();

/** Записывает в шину бит "1".
 */
void OneWireWriteBit1();

/** Читает из шины один бит.
 */
bit OneWireReadBit();

/** Записывает в шину один байт, начиная с младшего бита.
 * @param value Байт, записываемый в шину.
 */
void OneWireWriteByte(unsigned char value);

/** Читает из шины один байт, начиная с младшего бита.
 * @return Байт, прочитанный из шины.
 */
unsigned char OneWireReadByte();

/** Вычисляет CRC-8 (Dallas/Maxim) для следующего байта и текущего значения CRC.
 * Количество вызовов функции должно быть равно количеству прочитанных байт (с учетом байта CRC).
 * @param data Следующий байт.
 * @param crc Текущее значение CRC.
 * @return Значение CRC после вычисления. Если после необходимого количества вызовов функции значение CRC равно 0, то чтение успешно.
 */
unsigned char OneWireCRC8(unsigned char data, unsigned char crc);

#endif /* ONEWIRE_H */
