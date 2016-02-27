/** DS18B20Async.h
 * v.1.5
 */

#ifndef DS18B20ASYNC_H
#define	DS18B20ASYNC_H

#include "DS18B20Tasks.h"
#include "OneWireAsync.h"

/** Содержимое памяти датчика.
 * Используется как при чтении данных из датчика, так и при записи пользовательских данных в датчик.
 */
unsigned char DS18B20ScratchpadMemory[DS18B20ScratchpadLength];

/** Текущий индекс читаемого или записываемого байта.
 */
unsigned char DS18B20ScratchpadIndex;

/** CRC содержимого памяти для проверки правильности чтения.
 */
unsigned char DS18B20ScratchpadCRC;

/** Этапы работы с датчиком.
 */
typedef enum DS18B20CommandStages {

    DS18B20WriteScratchpadCommandStage,
    DS18B20ConvertTCommandStage,
    DS18B20ReadScratchpadCommandStage,

} DS18B20CommandStages;

/** Текущий этап работы с датчиком.
 */
DS18B20CommandStages DS18B20CommandStage;

/** Задача, которая должна быть добавлена в очередь для начала работы с датчиком.
 * Перед добавлением в очередь задач необходимо установить значение переменной DS18B20CommandStage равное DS18B20WriteScratchpadCommandStage.
 * Другие задачи не требуется вызывать для работы с датчиком.
 */
void DS18B20ResetPulseStageTask();

void DS18B20SendCommandStageTask();

void DS18B20SendWriteScratchpadCommandTask();
void DS18B20WriteScratchpadByteTask();

void DS18B20SendConvertTCommandTask();
void DS18B20WaitConvertTemperatureTask();

void DS18B20SendReadScratchpadCommandTask();
void DS18B20ReadScratchpadByteTask();
void DS18B20ReadScratchpadByteCRCTask();
void DS18B20CheckReadErrorsTask();
void DS18B20CalculateTemperatureValueTask();

/** Удаляет все задачи, связанные с библиотекой, из очереди диспетчера задач.
 * Хотя в один момент времени в очереди находится только одна связанная задача, для гарантированного удаления из очереди любой связанной задачи следует использовать эту функцию.
 */
void DS18B20RemoveAllAsyncTasks();

#endif /* DS18B20ASYNC_H */
