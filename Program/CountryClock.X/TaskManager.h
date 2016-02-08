/** TaskManager.h
 * v.1.4
 */

#ifndef TASKMANAGER_H
#define	TASKMANAGER_H

#include <xc.h>
#include "Config.h"

#ifndef TaskManagerQueueSize
    #error "TaskManagerQueueSize symbol is not defined, you should define it in file Config.h before using this library"
#endif

#ifndef TaskManagerTimerType
    #error "TaskManagerTimerType symbol is not defined, you should define it in file Config.h before using this library"
#endif

typedef void (*TPtr)(void);

typedef TaskManagerTimerType TTimer;

/** Преобразовывает время в секундах во время в единицах T_INT для установки таймера на задачу.
 * @param timeS Время в секундах (поддерживаются дробные значения секунд).
 * @return Время в единицах T_INT для установки таймера на задачу.
 */
#define GetTaskManagerTimerTime(timeS) ((TTimer)((timeS) / T_INT))

TPtr TasksQueue[TaskManagerQueueSize];

TTimer TimersQueue[TaskManagerQueueSize];

void Idle();

void TaskManager();

void TimerService();

void AddTask(TPtr pTask, TTimer time);

void RemoveTask(TPtr pTask);

void InitRTOS();

void RunRTOS();

#endif /* TASKMANAGER_H */
