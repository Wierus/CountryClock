/** OneWireAsync.c
 * v.1.0
 */

#include "OneWireAsync.h"

void OneWireResetPulseAsync(TPtr pCallbackTask) {
    OneWireAsyncCallbackPTask = pCallbackTask;
    OneWireDriveBusLow();
    //__delay_us(OneWireTimeH); // удалено из функции, так как цикл задач выполняется дольше этого ожидания
    AddTask(OneWireCheckPresencePulseTask, 0);
}

void OneWireCheckPresencePulseTask() {
    OneWireReleaseBus();
    __delay_us(60);
    unsigned char timeout = 0;
    while (OneWirePin != OneWirePrecencePulse) {
        __delay_us(1);
        if (++timeout > 60) {
            OneWireHasPresencePulseDetected = 0;
            AddTask(OneWireAsyncCallbackPTask, 0);
            return;
        }
    }
    //__delay_us(OneWireTimeJ); // удалено из функции, так как цикл задач выполняется дольше этого ожидания
    AddTask(OneWireCheckForReleasedBusTask, 0);
}

void OneWireCheckForReleasedBusTask() {
    if (OneWirePin == OneWirePrecencePulse) {
        OneWireHasPresencePulseDetected = 0;
        AddTask(OneWireAsyncCallbackPTask, 0);
        return;
    }
    OneWireHasPresencePulseDetected = 1;
    AddTask(OneWireAsyncCallbackPTask, 0);
}

void OneWireWriteBit0Async() {
    OneWireDriveBusLow();
    __delay_us(OneWireTimeC);
    OneWireReleaseBus();
    //__delay_us(OneWireTimeD); // удалено из функции, так как цикл задач выполняется дольше этого ожидания
}

void OneWireWriteBit1Async() {
    OneWireDriveBusLow();
    __delay_us(OneWireTimeA);
    OneWireReleaseBus();
    //__delay_us(OneWireTimeB); // удалено из функции, так как цикл задач выполняется дольше этого ожидания
}

bit OneWireReadBitAsync() {
    OneWireDriveBusLow();
    __delay_us(OneWireTimeA);
    OneWireReleaseBus();
    __delay_us(OneWireTimeE);
    //__delay_us(OneWireTimeF); // удалено из функции, так как цикл задач выполняется дольше этого ожидания
    return OneWirePin;
}

void OneWireWriteByteAsync(unsigned char value, TPtr pCallbackTask) {
    OneWireAsyncWriteByte = value;
    OneWireAsyncBitIndex = 8;
    OneWireAsyncCallbackPTask = pCallbackTask;
    AddTask(OneWireWriteBitAsyncTask, 0);
}

void OneWireWriteBitAsyncTask() {
    if (OneWireAsyncWriteByte & 1) {
        OneWireWriteBit1Async();
    }
    else {
        OneWireWriteBit0Async();
    }
    OneWireAsyncWriteByte >>= 1;
    if (!(--OneWireAsyncBitIndex)) {
        AddTask(OneWireAsyncCallbackPTask, 0);
    }
    else {
        AddTask(OneWireWriteBitAsyncTask, 0);
    }
}

void OneWireReadByteAsync(unsigned char* value, TPtr pCallbackTask) {
    OneWireAsyncReadByte = value;
    *OneWireAsyncReadByte = 0;
    OneWireAsyncBitIndex = 8;
    OneWireAsyncCallbackPTask = pCallbackTask;
    AddTask(OneWireReadBitAsyncTask, 0);
}

void OneWireReadBitAsyncTask() {
    *OneWireAsyncReadByte >>= 1;
    if (OneWireReadBitAsync()) {
        *OneWireAsyncReadByte |= 0b10000000;
    }
    if (!(--OneWireAsyncBitIndex)) {
        AddTask(OneWireAsyncCallbackPTask, 0);
    }
    else {
        AddTask(OneWireReadBitAsyncTask, 0);
    }
}
