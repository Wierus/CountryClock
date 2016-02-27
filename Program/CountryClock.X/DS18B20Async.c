/** DS18B20Async.c
 * v.1.5
 */

#include "DS18B20Async.h"

void DS18B20ResetPulseStageTask() {
    OneWireResetPulseAsync(DS18B20SendCommandStageTask);
}

void DS18B20SendCommandStageTask() {
    if (!OneWireHasPresencePulseDetected) {
        DS18B20LastError = DS18B20PrecencePulseNotDetected;
        DS18B20TemperatureValueIsCorrect = 0;
        DS18B20CommandStage = DS18B20WriteScratchpadCommandStage;
        AddTask(DS18B20ResetPulseStageTask, DS18B20PresencePulseNotDetectedDelay);
        return;
    }
    DS18B20LastError = DS18B20OperationOK;
    switch (DS18B20CommandStage) {
        case DS18B20WriteScratchpadCommandStage: {
            OneWireWriteByteAsync(DS18B20SkipROMCommand, DS18B20SendWriteScratchpadCommandTask);
            break;
        }
        case DS18B20ConvertTCommandStage: {
            OneWireWriteByteAsync(DS18B20SkipROMCommand, DS18B20SendConvertTCommandTask);
            break;
        }
        case DS18B20ReadScratchpadCommandStage: {
            OneWireWriteByteAsync(DS18B20SkipROMCommand, DS18B20SendReadScratchpadCommandTask);
            break;
        }
    }
}

void DS18B20SendWriteScratchpadCommandTask() {
    DS18B20ScratchpadIndex = DS18B20ScratchpadOffsetUserBytes;
    DS18B20ScratchpadMemory[2] = DS18B20ScratchpadByte2;
    DS18B20ScratchpadMemory[3] = DS18B20ScratchpadByte3;
    DS18B20ScratchpadMemory[4] = DS18B20DesiredResolution;
    OneWireWriteByteAsync(DS18B20WriteScratchpadCommand, DS18B20WriteScratchpadByteTask);
}

void DS18B20WriteScratchpadByteTask() {
    if (DS18B20ScratchpadIndex == (DS18B20ScratchpadOffsetUserBytes + DS18B20ScratchpadUserBytesCount)) {
        DS18B20CommandStage = DS18B20ConvertTCommandStage;
        AddTask(DS18B20ResetPulseStageTask, 0);
    }
    else {
        OneWireWriteByteAsync(DS18B20ScratchpadMemory[DS18B20ScratchpadIndex++], DS18B20WriteScratchpadByteTask);
    }
}

void DS18B20SendConvertTCommandTask() {
    OneWireWriteByteAsync(DS18B20ConvertTCommand, DS18B20WaitConvertTemperatureTask);
}

void DS18B20WaitConvertTemperatureTask() {
    DS18B20CommandStage = DS18B20ReadScratchpadCommandStage;
    AddTask(DS18B20ResetPulseStageTask, DS18B20ConvertTemperatureDelay);
}

void DS18B20SendReadScratchpadCommandTask() {
    DS18B20ScratchpadIndex = 0;
    DS18B20ScratchpadCRC = OneWireCRC8Init;
    OneWireWriteByteAsync(DS18B20ReadScratchpadCommand, DS18B20ReadScratchpadByteTask);
}

void DS18B20ReadScratchpadByteTask() {
    OneWireReadByteAsync(&(DS18B20ScratchpadMemory[DS18B20ScratchpadIndex]), DS18B20ReadScratchpadByteCRCTask);
}

void DS18B20ReadScratchpadByteCRCTask() {
    DS18B20ScratchpadCRC = OneWireCRC8(DS18B20ScratchpadMemory[DS18B20ScratchpadIndex++], DS18B20ScratchpadCRC);
    if (DS18B20ScratchpadIndex == DS18B20ScratchpadLength) {
        AddTask(DS18B20CheckReadErrorsTask, 0);
    }
    else {
        AddTask(DS18B20ReadScratchpadByteTask, 0);
    }
}

void DS18B20CheckReadErrorsTask() {
    if (
        (DS18B20ScratchpadCRC       != 0)                        ||
        (DS18B20ScratchpadMemory[2] != DS18B20ScratchpadByte2)   ||
        (DS18B20ScratchpadMemory[3] != DS18B20ScratchpadByte3)   ||
        (DS18B20ScratchpadMemory[4] != DS18B20DesiredResolution) ||
        (DS18B20ScratchpadMemory[5] != DS18B20ScratchpadByte5)   ||
        (DS18B20ScratchpadMemory[7] != DS18B20ScratchpadByte7)
    ) {
        DS18B20LastError = DS18B20ScratchpadReadError;
        DS18B20ReadErrorsCount++;
        if (DS18B20ReadErrorsCount > DS18B20MaxReadErrorsCount) {
            DS18B20TemperatureValueIsCorrect = 0;
        }
        DS18B20CommandStage = DS18B20WriteScratchpadCommandStage;
        AddTask(DS18B20ResetPulseStageTask, DS18B20ReadScratchpadErrorDelay);
        return;
    }
    AddTask(DS18B20CalculateTemperatureValueTask, 0);
}

void DS18B20CalculateTemperatureValueTask() {
    unsigned short temperatureRegister = (DS18B20ScratchpadMemory[1] << 8) | DS18B20ScratchpadMemory[0];
    DS18B20TemperatureValue.sign = (DS18B20ScratchpadMemory[1] & DS18B20TemperatureSignMask) ? 1 : 0;
    if (DS18B20TemperatureValue.sign) {
        temperatureRegister = (~temperatureRegister) + 1;
    }
    DS18B20TemperatureValue.integerPart = temperatureRegister >> DS18B20TemperatureFractionalPartMaskBitsCount;
    DS18B20TemperatureValue.fractionalPart = (temperatureRegister & DS18B20TemperatureFractionalPartMask) * (10000 / 16);
    DS18B20LastError = DS18B20OperationOK;
    DS18B20ReadErrorsCount = 0;
    DS18B20TemperatureValueIsCorrect = 1;
    DS18B20CommandStage = DS18B20ConvertTCommandStage;
    AddTask(DS18B20ResetPulseStageTask, DS18B20ReadScratchpadSuccessfullyDelay - DS18B20ConvertTemperatureDelay);
}

void DS18B20RemoveAllAsyncTasks() {
    RemoveTask(DS18B20ResetPulseStageTask);
    RemoveTask(DS18B20SendCommandStageTask);
    RemoveTask(DS18B20SendWriteScratchpadCommandTask);
    RemoveTask(DS18B20WriteScratchpadByteTask);
    RemoveTask(DS18B20SendConvertTCommandTask);
    RemoveTask(DS18B20WaitConvertTemperatureTask);
    RemoveTask(DS18B20SendReadScratchpadCommandTask);
    RemoveTask(DS18B20ReadScratchpadByteTask);
    RemoveTask(DS18B20ReadScratchpadByteCRCTask);
    RemoveTask(DS18B20CheckReadErrorsTask);
    RemoveTask(DS18B20CalculateTemperatureValueTask);
}
