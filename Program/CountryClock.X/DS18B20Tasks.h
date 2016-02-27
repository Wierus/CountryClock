/** DS18B20Tasks.h
 * v.1.3
 */

#ifndef DS18B20TASKS_H
#define	DS18B20TASKS_H

#include "DS18B20.h"
#include "TaskManager.h"

/* Период опроса шины в случае отсутствия датчика (в единицах T_INT, параметр - в секундах).
 */
#define DS18B20PresencePulseNotDetectedDelay   GetTaskManagerTimerTime(1.0)

/** Ожидание до повторного опроса шины в случае ошибки чтения (в единицах T_INT, параметр - в секундах).
 */
#define DS18B20ReadScratchpadErrorDelay        GetTaskManagerTimerTime(1.0)

/* Ожидание до чтения памяти после запуска процесса измерения и преобразования температуры (в единицах T_INT, параметр - в секундах).
 */
#define DS18B20ConvertTemperatureDelay         GetTaskManagerTimerTime(1.0)

/* Период обновления температуры датчика при штатной работе и при отсутствии ошибок на шине (в единицах T_INT, параметр - в секундах).
 */
#define DS18B20ReadScratchpadSuccessfullyDelay GetTaskManagerTimerTime(5.0)

void DS18B20WriteScratchpadTask();

void DS18B20ConvertTemperatureTask();

void DS18B20ReadScratchpadTask();

/** Удаляет все задачи, связанные с библиотекой, из очереди диспетчера задач.
 * Хотя в один момент времени в очереди находится только одна связанная задача, для гарантированного удаления из очереди любой связанной задачи следует использовать эту функцию.
 */
void DS18B20RemoveAllTasks();

#endif /* DS18B20TASKS_H */
