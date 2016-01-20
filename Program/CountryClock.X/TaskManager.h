#ifndef TASKMANAGER_H
#define	TASKMANAGER_H

#include <xc.h>

#define	TasksQueueSize 10

typedef void (*TPtr)(void);

typedef unsigned char TTimer;

TPtr TasksQueue[TasksQueueSize];

TTimer TimersQueue[TasksQueueSize];

void Idle();

void TaskManager();

void TimerService();

void AddTask(TPtr pTask, TTimer time);

void InitRTOS();

void RunRTOS();

#endif /* TASKMANAGER_H */
