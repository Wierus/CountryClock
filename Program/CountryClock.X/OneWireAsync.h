/** OneWireAsync.h
 * v.1.0
 */

#ifndef ONEWIREASYNC_H
#define	ONEWIREASYNC_H

#include "OneWire.h"
#include "TaskManager.h"

/** Флаг, показывающий, что был получен сигнал присутствия устройства на шине.
 */
bit OneWireHasPresencePulseDetected = 0;

/** Указатель на задачу, которая должна быть добавлена в очередь после выполнения текущей асинхронной функции.
 */
TPtr OneWireAsyncCallbackPTask;

/** Байт, асинхронно записываемый в шину.
 */
unsigned char OneWireAsyncWriteByte;

/** Указатель на байт, асинхронно читаемый из шины.
 */
unsigned char* OneWireAsyncReadByte;

/** Текущий индекс читаемого или записываемого бита в байте.
 */
unsigned char OneWireAsyncBitIndex;

/** Асинхронно отправляет в шину сигнал сброса и проверяет сигнал присутствия устройства на шине.
 * После получения сигнала присутствия устройства на шине (или по истечении таймаута при отсутствии сигнала) устанавливает соответствующее значение флага OneWireHasPresencePulseDetected (0 или 1) и добавляет указанную callback-задачу в очередь задач.
 * @param pCallbackTask Указатель на callback-задачу, которая должна быть добавлена в очередь после выполнения функции.
 */
void OneWireResetPulseAsync(TPtr pCallbackTask);

void OneWireDriveBusLowTask();
void OneWireCheckPresencePulseTask();
void OneWireCheckForReleasedBusTask();

void OneWireWriteBit0Async();
void OneWireWriteBit1Async();
bit OneWireReadBitAsync();

/** Асинхронно записывает в шину один байт, начиная с младшего бита.
 * После завершения записи добавляет указанную callback-задачу в очередь задач.
 * @param value Байт, записываемый в шину.
 * @param pCallbackTask Указатель на callback-задачу, которая должна быть добавлена в очередь после выполнения функции.
 */
void OneWireWriteByteAsync(unsigned char value, TPtr pCallbackTask);

void OneWireWriteBitAsyncTask();

/** Асинхронно читает из шины один байт, начиная с младшего бита.
 * После завершения чтения добавляет указанную callback-задачу в очередь задач.
 * @param value Указатель на байт, читаемый из шины.
 * @param pCallbackTask Указатель на callback-задачу, которая должна быть добавлена в очередь после выполнения функции.
 */
void OneWireReadByteAsync(unsigned char* value, TPtr pCallbackTask);

void OneWireReadBitAsyncTask();

#endif /* ONEWIREASYNC_H */
