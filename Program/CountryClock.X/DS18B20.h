/** DS18B20.h
 * v.1.6
 */

#ifndef DS18B20_H
#define	DS18B20_H

#include "OneWire.h"

/** Количество байт в уникальном идентификаторе датчика.
 */
#define DS18B20ROMCodeLength 8

/** Количество байт, читаемых из памяти датчика.
 * Структура памяти датчика:
 * Byte 0: Temperature LSB
 * Byte 1: Temperature MSB
 * Byte 2: TH Register or User Byte 1
 * Byte 3: TL Register or User Byte 2
 * Byte 4: Configuration Register
 * Byte 5: Reserved (FFh)
 * Byte 6: Reserved
 * Byte 7: Reserved (10h)
 * Byte 8: CRC
 */
#define DS18B20ScratchpadLength 9

/** Количество байт, записываемых в память датчика (Byte 2, Byte 3, Byte 4).
 */
#define DS18B20ScratchpadUserBytesCount 3

/** Смещение в памяти датчика, с которого начинается запись.
 */
#define DS18B20ScratchpadOffsetUserBytes 2

/** Значение 2-го байта памяти датчика (TH Register or User Byte 1).
 */
#define DS18B20ScratchpadByte2 0x00

/** Значение 3-го байта памяти датчика (TL Register or User Byte 2).
 */
#define DS18B20ScratchpadByte3 0x00

/** Значение 5-го байта памяти датчика.
 */
#define DS18B20ScratchpadByte5 0xFF

/** Значение 7-го байта памяти датчика.
 */
#define DS18B20ScratchpadByte7 0x10

/** Битовая маска знака температуры в старшем байте (бит "1" - знак).
 */
#define DS18B20TemperatureSignMask 0b11111000

/** Битовая маска дробной части температуры в младшем байте (бит "1" - дробная часть).
 */
#define DS18B20TemperatureFractionalPartMask 0b00001111

/** Количество бит равных "1" в маске дробной части температуры (используются для сдвига).
 */
#define DS18B20TemperatureFractionalPartMaskBitsCount 4

/** Команды для работы с ROM-кодом.
 */
typedef enum DS18B20ROMCommands {

    DS18B20SearchROMCommand   = 0xF0,
    DS18B20ReadROMCommand     = 0x33,
    DS18B20MatchROMCommand    = 0x55,
    DS18B20SkipROMCommand     = 0xCC,
    DS18B20AlarmSearchCommand = 0xEC,

} DS18B20ROMCommands;

/** Функциональные команды.
 */
typedef enum DS18B20FunctionCommands {

    DS18B20ConvertTCommand        = 0x44,
    DS18B20WriteScratchpadCommand = 0x4E,
    DS18B20ReadScratchpadCommand  = 0xBE,
    DS18B20CopyScratchpadCommand  = 0x48,
    DS18B20RecallE2Command        = 0xB8,
    DS18B20ReadPowerSupplyCommand = 0xB4,

} DS18B20FunctionCommands;

/** Разрешающая способность датчика.
 */
typedef enum DS18B20ThermometerResolutions {

    /** Разрешение 9 бит (0.5 градуса). Максимально время процесса измерения и преобразования температуры равно 93.75 мс.
     */
    DS18B20Resolution9Bit  = 0b00011111,

    /** Разрешение 10 бит (0.25 градуса). Максимально время процесса измерения и преобразования температуры равно 187.5 мс.
     */
    DS18B20Resolution10Bit = 0b00111111,

    /** Разрешение 11 бит (0.125 градуса). Максимально время процесса измерения и преобразования температуры равно 375 мс.
     */
    DS18B20Resolution11Bit = 0b01011111,

    /** Разрешение 12 бит (0.0625 градуса). Максимально время процесса измерения и преобразования температуры равно 750 мс.
     * Это значение установлено по умолчанию при включении питания датчика.
     */
    DS18B20Resolution12Bit = 0b01111111,

} DS18B20ThermometerResolutions;

/** Значение температуры, возвращаемое из памяти датчика, представленное в виде структуры.
 */
typedef struct DS18B20Temperature {

    /** Отрицательный знак температуры. 0 - положительное значение или ноль, 1 - отрицательное значение.
     */
    unsigned char sign;

    /** Целая часть значения температуры.
     */
    unsigned char integerPart;

    /** Дробная часть значения температуры.
     */
    unsigned short fractionalPart;

} DS18B20Temperature;

/** Коды ошибок при выполнении операций.
 */
typedef enum DS18B20ErrorCodes {
    
    /** Операция выполнена успешно.
     */
    DS18B20OperationOK,
    
    /** Сигнал присутствия (Precence pulse) не обнаружен, устройство отсутствует на шине.
     */
    DS18B20PrecencePulseNotDetected,
    
    /** Ошибка при чтении памяти датчика.
     */
    DS18B20ScratchpadReadError,

} DS18B20ErrorCodes;

/** Разрешающая способность датчика.
 */
DS18B20ThermometerResolutions DS18B20DesiredResolution = DS18B20Resolution12Bit;

/** Значение температуры с датчика DS18B20.
 */
DS18B20Temperature DS18B20TemperatureValue;

/** Результат выполнения предыдущей функции.
 */
DS18B20ErrorCodes DS18B20LastError = DS18B20PrecencePulseNotDetected;

/** Флаг, показывающий, что корректное значение температуры уже было получено и сохранено в переменной DS18B20TemperatureValue, которую можно использовать.
 */
bit DS18B20TemperatureValueIsCorrect = 0;

/** Максимальное количество последовательных ошибок чтения, после которого значение температуры DS18B20TemperatureValue становится недействительным.
 */
#define DS18B20MaxReadErrorsCount 5

/** Количество последовательных ошибок чтения.
 */
unsigned char DS18B20ReadErrorsCount = 0;

/** Отправляет датчику команду "Write Scratchpad", затем записывает данные в память датчика (2, 3 и 4 байты памяти датчика).
 * При этом устанавливается разрешающая способность датчика.
 */
void DS18B20WriteScratchpad();

/** Отправляет датчику команду "Convert T" для запуска процесса измерения и преобразования температуры.
 */
void DS18B20ConvertT();

/** Отправляет датчику команду "Read Scratchpad", затем получает значение температуры из памяти датчика.
 * При успешном выполнении значение температуры сохраняется в переменную DS18B20TemperatureValue.
 */
void DS18B20ReadScratchpad();

/** Задает разрешающую способность датчика.
 * @param resolution Разрешающая способность датчика.
 */
void DS18B20SetResolution(DS18B20ThermometerResolutions resolution);

#endif /* DS18B20_H */
