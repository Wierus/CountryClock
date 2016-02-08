/** TaskManager.c
 * v.1.4
 */

#include "TaskManager.h"

void Idle() {
}

TPtr pIdle = Idle;

void TaskManager() {
    di();
    TPtr pTask = pIdle;
    for (unsigned char i = 0; i != TaskManagerQueueSize; i++) {
        pTask = TasksQueue[i];
        // если найдена реальная задача
        if (pTask != pIdle) {
            // если таймер для нее равен нулю
            if (TimersQueue[i] == 0) {
                // сдвинуть все задачи до найденной
                for (unsigned char j = i; j != TaskManagerQueueSize - 1; j++) {
                    TasksQueue[j] = TasksQueue[j + 1];
                    TimersQueue[j] = TimersQueue[j + 1];
                }
                // в конец очереди установить задачу-заглушку
                TasksQueue[TaskManagerQueueSize - 1] = pIdle;
                TimersQueue[TaskManagerQueueSize - 1] = 0;
                // задача найдена, завершить поиск
                break;
            }
            // таймер для задачи не равен нулю
            else {
                // не исполнять задачу, продолжить поиск
                pTask = pIdle;
            }
        }
        // найдена задача-заглушка
        else {
            // завершить поиск
            break;
        }
    }
    pTask();
    ei();
}

void TimerService() {
    di();
    for (unsigned char i = 0; i != TaskManagerQueueSize; i++) {
        // если найдена реальная задача
        if (TasksQueue[i] != pIdle) {
            // если таймер для нее не равен нулю
            if (TimersQueue[i] != 0) {
                TimersQueue[i]--;
            }
        }
        // найдена задача-заглушка
        else {
            // завершить поиск
            break;
        }
    }
    ei();
}

void AddTask(TPtr pTask, TTimer time) {
    di();
    if (TasksQueue[TaskManagerQueueSize - 1] != pIdle) {
        // ошибка, нет свободного места в очереди задач
        NOP();
    }
    for (unsigned char i = 0; i != TaskManagerQueueSize; i++) {
        // если задача уже есть в очереди
        if (TasksQueue[i] == pTask) {
            // не добавлять ее
            break;
        }
        // если найдена задача-заглушка
        if (TasksQueue[i] == pIdle) {
            // добавить вместо нее новую
            TasksQueue[i] = pTask;
            TimersQueue[i] = time;
            break;
        }
    }
    ei();
}

void RemoveTask(TPtr pTask) {
    di();
    for (unsigned char i = 0; i != TaskManagerQueueSize; i++) {
        // если задача найдена
        if (TasksQueue[i] == pTask) {
            // сдвинуть все задачи до найденной
            for (unsigned char j = i; j != TaskManagerQueueSize - 1; j++) {
                TasksQueue[j] = TasksQueue[j + 1];
                TimersQueue[j] = TimersQueue[j + 1];
            }
            // в конец очереди установить задачу-заглушку
            TasksQueue[TaskManagerQueueSize - 1] = pIdle;
            TimersQueue[TaskManagerQueueSize - 1] = 0;
            break;
        }
    }
    ei();
}

void InitRTOS() {
    for (unsigned char i = 0; i != TaskManagerQueueSize; i++) {
        TasksQueue[i] = pIdle;
        TimersQueue[i] = 0;
    }
}

void RunRTOS () {
    TMR0 = 0;
    ei();
}
