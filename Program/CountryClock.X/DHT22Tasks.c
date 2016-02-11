/** DHT22Tasks.c
 * v.1.0
 */

#include "DHT22Tasks.h"
#include "DHT22.h"
#include "TaskManager.h"
#include "Delay.h"

void DHT22InitializeSensorTask() {
    DHT22InitializeSensorAction();
    AddTask(DHT22ReadTask, DHT22ReadTaskDelay);
}

void DHT22ReadTask() {
    DHT22ReadAction();
    if (DHT22ResultRead == DHT22OperationOK) {
        AddTask(DHT22ReadTask, DHT22RepeatOKReadTaskDelay);
    }
    else {
        AddTask(DHT22ReadTask, DHT22RepeatFailReadTaskDelay);
    }
}

void DHT22InitializeSensorAction() {
}

void DHT22ReadAction() {
    ReadDHT22();
}

void DHT22RemoveAllTasks() {
    RemoveTask(DHT22InitializeSensorTask);
    RemoveTask(DHT22ReadTask);
}
