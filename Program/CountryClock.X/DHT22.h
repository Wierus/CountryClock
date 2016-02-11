/** DHT22.h
 * v.1.1
 */

#ifndef DHT22_H
#define	DHT22_H

#include "Pins.h"

#ifndef DHT22Pin
    #error "DHT22Pin symbol is not defined, you should define it in file Pins.h before using this library"
#endif

#ifndef DHT22PinDirection
    #error "DHT22PinDirection symbol is not defined, you should define it in file Pins.h before using this library"
#endif

/** Количество байт данных, читаемых из датчика.
 * Последовательность байт:
 * Byte 0: Humidity high
 * Byte 1: Humidity low
 * Byte 2: Temperature high
 * Byte 3: Temperature low
 * Byte 4: Parity bits
 */
#define DHT22DataLength 5

/** Host the start signal down time (ms).
 */
#define DHT22_T_be  1

/** Bus master has released time (us).
 */
#define DHT22_T_go 30

/** Signal "0" high time (us).
 */
#define DHT22_T_H0 26

/** Signal "1" high time (us).
 */
#define DHT22_T_H1 70

/** Максимальное время ожидания изменения уровня сигнала на шине (мкс).
 */
#define DHT22Timeout 85

/** Битовая маска знака температуры (бит "1" - знак).
 */
#define DHT22TemperatureSignMask 0b1000000000000000

/** Значение влажности, возвращаемое из памяти датчика, представленное в виде структуры.
 */
typedef struct DHT22Humidity {

    /** Целая часть значения влажности.
     */
    unsigned char integerPart;

    /** Дробная часть значения влажности (от 0 до 9).
     */
    unsigned char fractionalPart;

} DHT22Humidity;

/** Значение температуры, возвращаемое из памяти датчика, представленное в виде структуры.
 */
typedef struct DHT22Temperature {

    /** Отрицательный знак температуры. 0 - положительное значение или ноль, 1 - отрицательное значение.
     */
    unsigned char sign;

    /** Целая часть значения температуры.
     */
    unsigned char integerPart;

    /** Дробная часть значения температуры (от 0 до 9).
     */
    unsigned char fractionalPart;

} DHT22Temperature;

/** Коды ошибок при выполнении операций.
 */
typedef enum DHT22ErrorCodes {

    /** Операция выполнена успешно.
     */
    DHT22OperationOK,

    /** Сигнал присутствия (Response signal) не обнаружен, устройство отсутствует на шине.
     */
    DHT22ResponseSignalNotDetected,

    /** Ошибка при чтении данных из датчика, датчик не ответил вовремя.
     */
    DHT22TimeoutReadError,

    /** Ошибка при чтении данных из датчика, один или несколько битов четности не совпадают.
     */
    DHT22ParityReadError,

} DHT22ErrorCodes;

/** Значение влажности с датчика DHT22.
 */
DHT22Humidity DHT22HumidityValue;

/** Значение температуры с датчика DHT22.
 */
DHT22Temperature DHT22TemperatureValue;

/** Результат выполнения операции чтения данных из датчика DHT22.
 */
DHT22ErrorCodes DHT22ResultRead = DHT22ResponseSignalNotDetected;

/** Флаг, показывающий, что корректные значения влажности и температуры уже были получены и сохранены в переменных DHT22HumidityValue и DHT22TemperatureValue, которые можно использовать.
 */
bit DHT22ValuesAreCorrect = 0;

/** Читает данные из датчика и сохраняет полученные значения в переменных: DHT22HumidityValue (влажность) и DHT22TemperatureValue (температура).
 * Результат выполнения функции сохраняется в переменную DHT22ResultRead.
 */
void ReadDHT22();

/** Отправляет сигнал датчику для его включения и ждет ответ.
 * @return DHT22OperationOK, если ответ получен успешно.
 * DHT22TimeoutReadError, если датчик не ответил вовремя.
 */
DHT22ErrorCodes SendStartSignal();

/** Ожидает на шине сначала низкий уровень, затем высокий.
 * @return DHT22OperationOK, если на шине был прочитан сначала низкий уровень, затем высокий уровень.
 * DHT22TimeoutReadError, если какой-либо уровень не был прочитан вовремя.
 */
DHT22ErrorCodes WaitLowHigh();

/** Читает из датчика 5 байт данных.
 * @param data Массив для записи данных.
 * @return DHT22OperationOK, если данные прочитаны успешно (без проверки контрольной суммы).
 * DHT22TimeoutReadError, если при чтении данных датчик не ответил вовремя.
 */
DHT22ErrorCodes ReadData(unsigned char data[]);

/** Читает из датчика 1 байт данных.
 * @param byte Указатель на переменную для записи байта.
 * @return DHT22OperationOK, если байт прочитан успешно.
 * DHT22TimeoutReadError, если при чтении данных датчик не ответил вовремя.
 */
DHT22ErrorCodes ReadByte(unsigned char* byte);

#endif	/* DHT22_H */
