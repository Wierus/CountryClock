/** DS18B20Tasks.c
 * v.1.2
 */

#include "DS18B20Tasks.h"
#include "DS18B20.h"
#include "TaskManager.h"
#include "Delay.h"

void DS18B20InitializeSensorTask() {
    DS18B20InitializeSensorAction();
    if (DS18B20ResultInitializeSensor == DS18B20OperationOK) {
        AddTask(DS18B20ConvertTemperatureTask, DS18B20ConvertTemperatureTaskDelay);
    }
    else {
        AddTask(DS18B20InitializeSensorTask, DS18B20RepeatInitializeSensorTaskDelay);
    }
}

void DS18B20ConvertTemperatureTask() {
    DS18B20ConvertTemperatureAction();
    if (DS18B20ResultConvertTemperature == DS18B20OperationOK) {
        AddTask(DS18B20GetTemperatureTask, DS18B20GetTemperatureTaskDelay);
    }
    else {
        AddTask(DS18B20InitializeSensorTask, DS18B20RepeatInitializeSensorTaskDelay);
    }
}

void DS18B20GetTemperatureTask() {
    DS18B20GetTemperatureAction();
    switch (DS18B20ResultGetTemperature) {
        case DS18B20OperationOK: {
            AddTask(DS18B20ConvertTemperatureTask, DS18B20RepeatConvertTemperatureTaskDelay - DS18B20GetTemperatureTaskDelay);
            break;
        }
        case DS18B20PrecencePulseNotDetected:
        case DS18B20ConvertTemperatureError: {
            AddTask(DS18B20InitializeSensorTask, DS18B20RepeatInitializeSensorTaskDelay);
            break;
        }
        default: {
            AddTask(DS18B20GetTemperatureTask, DS18B20RepeatGetTemperatureTaskDelay);
            break;
        }
    }
}

void DS18B20InitializeSensorAction() {
    DS18B20InitializeSensor();
}

void DS18B20ConvertTemperatureAction() {
    DS18B20ConvertTemperature();
}

void DS18B20GetTemperatureAction() {
    DS18B20GetTemperature();
}

void DS18B20RemoveAllTasks() {
    RemoveTask(DS18B20InitializeSensorTask);
    RemoveTask(DS18B20ConvertTemperatureTask);
    RemoveTask(DS18B20GetTemperatureTask);
}
