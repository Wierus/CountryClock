#include "Config.h"
#include "Delay.h"
#include "DHT22Tasks.h"
#include "DS18B20Async.h"
#include "Pins.h"
#include "SevenSegmentDisplayDHT22.h"
#include "SevenSegmentDisplayDS18B20.h"
#include "SR74HC164.h"
#include "TaskManager.h"

/** Время свечения одного индикатора (мс).
 */
#define IndicatorLightingTime 1

#define IndicatorCA

#ifdef IndicatorCA

    /** Значение вывода индикатора для его включения.
     */
    #define IndicatorOn  IndicatorCAOn

    /** Значение вывода индикатора для его выключения.
     */
    #define IndicatorOff IndicatorCAOff

    /** Значение вывода сегмента индикатора для его включения.
     */
    #define SegmentOn    SegmentCAOn

    /** Значение вывода сегмента индикатора для его выключения.
     */
    #define SegmentOff   SegmentCAOff

#else

    /** Значение вывода индикатора для его включения.
     */
    #define IndicatorOn  IndicatorCCOn

    /** Значение вывода индикатора для его выключения.
     */
    #define IndicatorOff IndicatorCCOff

    /** Значение вывода сегмента индикатора для его включения.
     */
    #define SegmentOn    SegmentCCOn

    /** Значение вывода сегмента индикатора для его выключения.
     */
    #define SegmentOff   SegmentCCOff

#endif

/** Количество индикаторов.
 */
#define IndicatorsCount 5

/** Символы на индикаторах (слева направо).
 */
unsigned char indicatorValues[IndicatorsCount];

/** Количество часов в сутках.
 */
#define MaxHours      24

/** Количество минут в часе.
 */
#define MaxMinutes    60

/** Количество секунд в минуте.
 */
#define MaxSeconds    60

/** Количество миллисекунд в секунде.
 */
#define MaxMSeconds 1000

/** Количество микросекунд в миллисекунде.
 */
#define MaxUSeconds 1000

/** Количество наносекунд в микросекунде.
 */
#define MaxNSeconds 1000

/** Текущее значение часов на контроллере.
 */
unsigned char timeHours = 0;

/** Текущее значение минут на контроллере.
 */
unsigned char timeMinutes = 0;

/** Текущее значение секунд на контроллере.
 */
unsigned short timeSeconds = 0;

/** Текущее значение миллисекунд на контроллере.
 */
unsigned short timeMSeconds = 0;

/** Текущее значение микросекунд на контроллере.
 */
unsigned short timeUSeconds = 0;

/** Текущее значение наносекунд на контроллере.
 */
unsigned short timeNSeconds = 0;

/** Устанавливаемая разрешающая способность датчика DS18B20.
 */
#define DS18B20Resolution DS18B20Resolution12Bit

/** Необходимое время удержания кнопки до совершения действия (в единицах T_INT, параметр - в секундах).
 */
#define ButtonPressedTime     GetTaskManagerTimerTime(1.0)

/** Необходимое время удержания кнопки до совершения действия (быстро) (в единицах T_INT, параметр - в секундах).
 */
#define ButtonFastPressedTime GetTaskManagerTimerTime(0.5)

/** Текущее время удержания кнопки "Часы" (в единицах T_INT).
 */
unsigned char buttonHoursPressedTimer = 0;

/** Текущее время удержания кнопки "Минуты" (в единицах T_INT).
 */
unsigned char buttonMinutesPressedTimer = 0;

/** Текущее время удержания кнопки "Режим" (в единицах T_INT).
 */
unsigned char buttonModePressedTimer = 0;

/** Текущее время удержания виртуальной кнопки "Коррекция" (в единицах T_INT).
 */
unsigned char buttonCorrectionPressedTimer = 0;

/** Флаг, показывающий, что кнопка "Часы" нажата.
 */
bit isButtonHoursPressed = 0;

/** Флаг, показывающий, что кнопка "Минуты" нажата.
 */
bit isButtonMinutesPressed = 0;

/** Флаг, показывающий, что кнопка "Режим" нажата.
 */
bit isButtonModePressed = 0;

/** Флаг, показывающий, что виртуальная кнопка "Коррекция" нажата (одновременное нажатие кнопок "Часы" и "Минуты").
 */
bit isButtonCorrectionPressed = 0;

/** Необходимое время отображения времени (в единицах T_INT, параметр - в секундах).
 */
#define MaxOutputTimeTimer               GetTaskManagerTimerTime(3.0)

/** Необходимое время отображения температуры с датчика DS18B20 (в единицах T_INT, параметр - в секундах).
 */
#define MaxOutputDS18B20TemperatureTimer GetTaskManagerTimerTime(3.0)

/** Необходимое время отображения температуры с датчика DHT22 (в единицах T_INT, параметр - в секундах).
 */
#define MaxOutputDHT22TemperatureTimer   GetTaskManagerTimerTime(3.0)

/** Необходимое время отображения влажности с датчика DHT22 (в единицах T_INT, параметр - в секундах).
 */
#define MaxOutputDHT22HumidityTimer      GetTaskManagerTimerTime(3.0)

/** Текущее время отображения времени (в единицах T_INT).
 */
unsigned char outputTimeTimer = 0;

/** Текущее время отображения температуры с датчика DS18B20 (в единицах T_INT).
 */
unsigned char outputDS18B20TemperatureTimer = 0;

/** Текущее время отображения температуры с датчика DHT22 (в единицах T_INT).
 */
unsigned char outputDHT22TemperatureTimer = 0;

/** Текущее время отображения влажности с датчика DHT22 (в единицах T_INT).
 */
unsigned char outputDHT22HumidityTimer = 0;

/** Задержка до выполнения задачи CheckPowerTaskDelay (в единицах T_INT, параметр - в секундах).
 */
#define CheckPowerTaskDelay     GetTaskManagerTimerTime(0.0)

/** Задержка до выполнения задачи DrawIndicatorsTask (в единицах T_INT, параметр - в секундах).
 */
#define DrawIndicatorsTaskDelay GetTaskManagerTimerTime(0.0)

/** Задержка до выполнения задачи FillIndicatorsTask (в единицах T_INT, параметр - в секундах).
 */
#define FillIndicatorsTaskDelay GetTaskManagerTimerTime(0.0)

/** Задержка до выполнения задачи ScanButtonsTask (в единицах T_INT, параметр - в секундах).
 */
#define ScanButtonsTaskDelay    GetTaskManagerTimerTime(0.0)

/** Состояние питания при предыдущей проверке.
 */
bit previousPowerState = PowerOff;

/** Режимы работы.
 */
typedef enum WorkMode {

    /** Режим отображения по порядку: времени, температуры с датчика DS18B20, температуры с датчика DHT22, влажности с датчика DHT22.
     */
    ShowAllMode,
    
    /** Режим отображения времени.
     */
    ShowTimeMode,
    
    /** Режим отображения температуры с датчика DS18B20.
     */
    ShowDS18B20TemperatureMode,
    
    /** Режим отображения температуры с датчика DHT22.
     */
    ShowDHT22TemperatureMode,
    
    /** Режим отображения влажности с датчика DHT22.
     */
    ShowDHT22HumidityMode,

} WorkMode;

/** Текущий режим работы.
 */
WorkMode currentWorkMode = ShowAllMode;

/** Текущее выводимое значение в режиме отображения по порядку (ShowAllMode).
 */
WorkMode currentOutputMode = ShowTimeMode;

void IncrementTimeInInterrupt();

void ProcessButtonsInInterrupt();

void ProcessOutputTimersInInterrupt();

void NormalizeTime();

void ActionAtPowerOn();

void ActionAtPowerOff();

inline void InitPins();

/** Обработчик прерывания. Вызывается по переполненеию TMR0 каждые T_INT секунд.
 */
void interrupt Interrupt() {
    if (TMR0IE && TMR0IF) {
        TMR0IF = 0;
        TimerService();
        IncrementTimeInInterrupt();
        ProcessButtonsInInterrupt();
        ProcessOutputTimersInInterrupt();
    }
}

// +T_INT
void IncrementTimeInInterrupt() {
    timeMSeconds +=  65;
    timeUSeconds += 536;
    timeNSeconds +=   0;
    NormalizeTime();
}

void ProcessButtonsInInterrupt() {
    if ((ButtonHoursPin == ButtonPressed) && (ButtonMinutesPin == ButtonPressed)) {
        buttonCorrectionPressedTimer++;
        if (buttonCorrectionPressedTimer >= ButtonPressedTime) {
            buttonCorrectionPressedTimer -= ButtonPressedTime;
            isButtonCorrectionPressed = 1;
        }
        return;
    }
    else {
        isButtonCorrectionPressed = 0;
        buttonCorrectionPressedTimer = 0;
    }
    if (ButtonHoursPin == ButtonPressed) {
        buttonHoursPressedTimer++;
        if (buttonHoursPressedTimer >= ButtonFastPressedTime) {
            buttonHoursPressedTimer -= ButtonFastPressedTime;
            isButtonHoursPressed = 1;
        }
    }
    else {
        isButtonHoursPressed = 0;
        buttonHoursPressedTimer = 0;
    }
    if (ButtonMinutesPin == ButtonPressed) {
        buttonMinutesPressedTimer++;
        if (buttonMinutesPressedTimer >= ButtonFastPressedTime) {
            buttonMinutesPressedTimer -= ButtonFastPressedTime;
            isButtonMinutesPressed = 1;
        }
    }
    else {
        isButtonMinutesPressed = 0;
        buttonMinutesPressedTimer = 0;
    }
    if (ButtonModePin == ButtonPressed) {
        buttonModePressedTimer++;
        if (buttonModePressedTimer >= ButtonPressedTime) {
            buttonModePressedTimer -= ButtonPressedTime;
            isButtonModePressed = 1;
        }
    }
    else {
        isButtonModePressed = 0;
        buttonModePressedTimer = 0;
    }
}

void ProcessOutputTimersInInterrupt() {
    if (currentWorkMode == ShowAllMode) {
        switch (currentOutputMode) {
            case ShowTimeMode: {
                outputTimeTimer++;
                if (outputTimeTimer >= MaxOutputTimeTimer) {
                    outputTimeTimer = 0;
                    currentOutputMode = ShowDS18B20TemperatureMode;
                }
                break;
            }
            case ShowDS18B20TemperatureMode: {
                outputDS18B20TemperatureTimer++;
                if (outputDS18B20TemperatureTimer >= MaxOutputDS18B20TemperatureTimer) {
                    outputDS18B20TemperatureTimer = 0;
                    currentOutputMode = ShowDHT22TemperatureMode;
                }
                break;
            }
            case ShowDHT22TemperatureMode: {
                outputDHT22TemperatureTimer++;
                if (outputDHT22TemperatureTimer >= MaxOutputDHT22TemperatureTimer) {
                    outputDHT22TemperatureTimer = 0;
                    currentOutputMode = ShowDHT22HumidityMode;
                }
                break;
            }
            case ShowDHT22HumidityMode: {
                outputDHT22HumidityTimer++;
                if (outputDHT22HumidityTimer >= MaxOutputDHT22HumidityTimer) {
                    outputDHT22HumidityTimer = 0;
                    currentOutputMode = ShowTimeMode;
                }
                break;
            }
        }
    }
    else {
        currentOutputMode = ShowTimeMode;
        outputTimeTimer = 0;
        outputDS18B20TemperatureTimer = 0;
        outputDHT22TemperatureTimer = 0;
        outputDHT22HumidityTimer = 0;
    }
}

void NormalizeTime() {
    if (timeNSeconds >= MaxNSeconds) {
        timeNSeconds -= MaxNSeconds;
        timeUSeconds++;
    }
    if (timeUSeconds >= MaxUSeconds) {
        timeUSeconds -= MaxUSeconds;
        timeMSeconds++;
    }
    if (timeMSeconds >= MaxMSeconds) {
        timeMSeconds -= MaxMSeconds;
        timeSeconds++;
    }
    if (timeSeconds >= MaxSeconds) {
        timeSeconds = 0;
        timeMinutes++;
    }
    if (timeMinutes >= MaxMinutes) {
        timeMinutes = 0;
        timeHours++;
    }
    if (timeHours >= MaxHours) {
        timeHours = 0;
    }
}

// Объявление задач и действий для них

void CheckPowerTask();
void CheckPowerAction();

void DrawIndicatorsTask();
void DrawIndicatorsAction();

void FillIndicatorsTask();
void FillIndicatorsAction();

void RefreshDS18B20Task();
void RefreshDS18B20Action();

void RefreshDHT22Task();
void RefreshDHT22Action();

void ScanButtonsTask();
void ScanButtonsAction();

// Определение задач

void CheckPowerTask() {
    CheckPowerAction();
    if (PowerStatePin == PowerOn) {
        if (previousPowerState == PowerOff) {
            // PowerOff -> PowerOn
            previousPowerState = PowerOn;
            ActionAtPowerOn();
            AddTask(DrawIndicatorsTask, 0);
            AddTask(FillIndicatorsTask, 0);
            AddTask(RefreshDS18B20Task, 0);
            AddTask(RefreshDHT22Task, 0);
            AddTask(ScanButtonsTask, 0);
        }
    }
    else {
        if (previousPowerState == PowerOn) {
            // PowerOn -> PowerOff
            previousPowerState = PowerOff;
            ActionAtPowerOff();
            RemoveTask(DrawIndicatorsTask);
            RemoveTask(FillIndicatorsTask);
            RemoveTask(RefreshDS18B20Task);
            RemoveTask(RefreshDHT22Task);
            RemoveTask(ScanButtonsTask);
            DS18B20RemoveAllAsyncTasks();
        }
    }
    AddTask(CheckPowerTask, CheckPowerTaskDelay);
}

void DrawIndicatorsTask() {
    DrawIndicatorsAction();
    AddTask(DrawIndicatorsTask, DrawIndicatorsTaskDelay);
}

void FillIndicatorsTask() {
    FillIndicatorsAction();
    AddTask(FillIndicatorsTask, FillIndicatorsTaskDelay);
}

void RefreshDS18B20Task() {
    RefreshDS18B20Action();
    DS18B20CommandStage = DS18B20WriteScratchpadCommandStage;
    AddTask(DS18B20ResetPulseStageTask, 0);
}

void RefreshDHT22Task() {
    RefreshDHT22Action();
    AddTask(DHT22InitializeSensorTask, 0);
}

void ScanButtonsTask() {
    ScanButtonsAction();
    AddTask(ScanButtonsTask, ScanButtonsTaskDelay);
}

// Дополнительные функции действий для задач

void FillIndicatorsWithTime() {
    indicatorValues[0] = (timeHours < 10) ? SymbolNull : GetIndicatorDigit(GetD1OfU08(timeHours));
    indicatorValues[1] = GetIndicatorDigit(GetD0OfU08(timeHours));
    indicatorValues[2] = (timeMSeconds >= 500) ? SymbolLine : SymbolNull;
    indicatorValues[3] = GetIndicatorDigit(GetD1OfU08(timeMinutes));
    indicatorValues[4] = GetIndicatorDigit(GetD0OfU08(timeMinutes));
}

void FillIndicatorsWithDS18B20Temperature() {
    FillIndicators5WithDS18B20TemperatureAndSymbolDegree(indicatorValues);
}

void FillIndicatorsWithDHT22Temperature() {
    FillIndicators5WithDHT22TemperatureAndSymbolDegree(indicatorValues);
}

void FillIndicatorsWithDHT22Humidity() {
    FillIndicators5WithDHT22HumidityAndSymbolLowerLetterH(indicatorValues);
}

// Определение действий для задач

void CheckPowerAction() {
}

void DrawIndicatorsAction() {
    SR74HC164SendByte(indicatorValues[0]);
    Indicator0Pin = IndicatorOn;
    __delay_ms(IndicatorLightingTime);
    Indicator0Pin = IndicatorOff;
    SR74HC164SendByte(indicatorValues[1]);
    Indicator1Pin = IndicatorOn;
    __delay_ms(IndicatorLightingTime);
    Indicator1Pin = IndicatorOff;
    SR74HC164SendByte(indicatorValues[2]);
    Indicator2Pin = IndicatorOn;
    __delay_ms(IndicatorLightingTime);
    Indicator2Pin = IndicatorOff;
    SR74HC164SendByte(indicatorValues[3]);
    Indicator3Pin = IndicatorOn;
    __delay_ms(IndicatorLightingTime);
    Indicator3Pin = IndicatorOff;
    SR74HC164SendByte(indicatorValues[4]);
    Indicator4Pin = IndicatorOn;
    __delay_ms(IndicatorLightingTime);
    Indicator4Pin = IndicatorOff;
}

void FillIndicatorsAction() {
    switch (currentWorkMode) {
        case ShowAllMode: {
            switch (currentOutputMode) {
                case ShowTimeMode: {
                    FillIndicatorsWithTime();
                    break;
                }
                case ShowDS18B20TemperatureMode: {
                    FillIndicatorsWithDS18B20Temperature();
                    break;
                }
                case ShowDHT22TemperatureMode: {
                    FillIndicatorsWithDHT22Temperature();
                    break;
                }
                case ShowDHT22HumidityMode: {
                    FillIndicatorsWithDHT22Humidity();
                    break;
                }
            }
            break;
        }
        case ShowTimeMode: {
            FillIndicatorsWithTime();
            break;
        }
        case ShowDS18B20TemperatureMode: {
            FillIndicatorsWithDS18B20Temperature();
            break;
        }
        case ShowDHT22TemperatureMode: {
            FillIndicatorsWithDHT22Temperature();
            break;
        }
        case ShowDHT22HumidityMode: {
            FillIndicatorsWithDHT22Humidity();
            break;
        }
    }
}

void RefreshDS18B20Action() {
}

void RefreshDHT22Action() {
}

void ScanButtonsAction() {
    if (isButtonHoursPressed) {
        isButtonHoursPressed = 0;
        if (currentWorkMode == ShowTimeMode) {
            timeHours++;
            NormalizeTime();
        }
    }
    if (isButtonMinutesPressed) {
        isButtonMinutesPressed = 0;
        if (currentWorkMode == ShowTimeMode) {
            timeMinutes++;
            NormalizeTime();
        }
    }
    if (isButtonModePressed) {
        isButtonModePressed = 0;
        switch (currentWorkMode) {
            case ShowAllMode: {
                currentWorkMode = ShowTimeMode;
                break;
            }
            case ShowTimeMode: {
                currentWorkMode = ShowDS18B20TemperatureMode;
                break;
            }
            case ShowDS18B20TemperatureMode: {
                currentWorkMode = ShowDHT22TemperatureMode;
                break;
            }
            case ShowDHT22TemperatureMode: {
                currentWorkMode = ShowDHT22HumidityMode;
                break;
            }
            case ShowDHT22HumidityMode: {
                currentWorkMode = ShowAllMode;
                break;
            }
        }
    }
    if (isButtonCorrectionPressed) {
        isButtonCorrectionPressed = 0;
        if (currentWorkMode == ShowTimeMode) {
            if (timeMinutes >= 30) {
                timeHours++;
                NormalizeTime();
            }
            timeMinutes  = 0;
            timeSeconds  = 0;
            timeMSeconds = 0;
            timeUSeconds = 0;
            timeNSeconds = 0;
        }
    }
}

/** Действия, выполняемые при включении основного питания.
 */
void ActionAtPowerOn() {
    InitPins();
    DS18B20SetResolution(DS18B20Resolution);
    SR74HC164Initialize();
}

/** Действия, выполняемые при выключении основного питания.
 */
void ActionAtPowerOff() {
    TRISA = 0b11111111;
    TRISB = 0b11111111;
}

inline void InitOptionReg();
inline void InitIntConReg();
inline void InitADCon0Reg();
inline void InitADCon1Reg();
inline void InitAnSelReg();

inline void InitRegisters() {
    InitOptionReg();
    InitIntConReg();
    InitADCon0Reg();
    InitADCon1Reg();
    InitAnSelReg();
}

inline void InitOptionReg() {
    /** OPTION_REG: bit 2-0
     * PS<2:0>: Prescaler Rate Select bits
     * BIT VALUE | TMR0 RATE | WDT RATE
     * 000       | 1 :   2   | 1 :   1
     * 001       | 1 :   4   | 1 :   2
     * 010       | 1 :   8   | 1 :   4
     * 011       | 1 :  16   | 1 :   8
     * 100       | 1 :  32   | 1 :  16
     * 101       | 1 :  64   | 1 :  32
     * 110       | 1 : 128   | 1 :  64
     * 111       | 1 : 256   | 1 : 128
     */
    OPTION_REGbits.PS = 0b111;
    /** OPTION_REG: bit 3
     * PSA: Prescaler Assignment bit
     * 1 = Prescaler is assigned to the WDT
     * 0 = Prescaler is assigned to the Timer0 module
     */
    OPTION_REGbits.PSA = 0;
    /** OPTION_REG: bit 4
     * T0SE: TMR0 Source Edge Select bit
     * 1 = Increment on high-to-low transition on RA4/T0CKI/C2OUT pin
     * 0 = Increment on low-to-high transition on RA4/T0CKI/C2OUT pin
     */
    OPTION_REGbits.T0SE = 0;
    /** OPTION_REG: bit 5
     * T0CS: TMR0 Clock Source Select bit
     * 1 = Transition on RA4/T0CKI/C2OUT pin
     * 0 = Internal instruction cycle clock (CLKO)
     */
    OPTION_REGbits.T0CS = 0;
    /** OPTION_REG: bit 6
     * INTEDG: Interrupt Edge Select bit
     * 1 = Interrupt on rising edge of RB0/INT pin
     * 0 = Interrupt on falling edge of RB0/INT pin
     */ 
     OPTION_REGbits.INTEDG = 0;
     /** OPTION_REG: bit 7
     * RBPU (not): PORTB Pull-up Enable bit
     * 1 = PORTB pull-ups are disabled
     * 0 = PORTB pull-ups are enabled by individual port latch values
     */
    OPTION_REGbits.nRBPU = 1;
}

inline void InitIntConReg() {
    /** INTCON: bit 0
     * RBIF: RB Port Change Interrupt Flag bit
     * A mismatch condition will continue to set flag bit RBIF. Reading PORTB will end the mismatch condition and allow flag bit RBIF to be cleared.
     * 1 = At least one of the RB7:RB4 pins changed state (must be cleared in software)
     * 0 = None of the RB7:RB4 pins have changed state
     */
    /** INTCON: bit 1
     * INT0IF: RB0/INT External Interrupt Flag bit
     * 1 = The RB0/INT external interrupt occurred (must be cleared in software)
     * 0 = The RB0/INT external interrupt did not occur
     */
    /** INTCON: bit 2
     * TMR0IF: TMR0 Overflow Interrupt Flag bit
     * 1 = TMR0 register has overflowed (must be cleared in software)
     * 0 = TMR0 register did not overflow
     */
    /** INTCON: bit 3
     * RBIE: RB Port Change Interrupt Enable bit
     * 1 = Enables the RB port change interrupt
     * 0 = Disables the RB port change interrupt
     */
    INTCONbits.RBIE = 0;
    /** INTCON: bit 4
     * INT0IE: RB0/INT External Interrupt Enable bit
     * 1 = Enables the RB0/INT external interrupt
     * 0 = Disables the RB0/INT external interrupt
     */
    INTCONbits.INT0IE = 0;
    /** INTCON: bit 5
     * TMR0IE: TMR0 Overflow Interrupt Enable bit
     * 1 = Enables the TMR0 interrupt
     * 0 = Disables the TMR0 interrupt
     */
    INTCONbits.TMR0IE = 1;
    /** INTCON: bit 6
     * PEIE: Peripheral Interrupt Enable bit
     * 1 = Enables all unmasked peripheral interrupts
     * 0 = Disables all peripheral interrupts
     */
    INTCONbits.PEIE = 0;
    /** INTCON: bit 7
     * GIE: Global Interrupt Enable bit
     * 1 = Enables all unmasked interrupts
     * 0 = Disables all interrupts
     */
    INTCONbits.GIE = 0;
}

inline void InitADCon0Reg() {
    /** ADCON0: bit 0
     * ADON: A/D On bit
     * 1 = A/D converter module is operating
     * 0 = A/D converter module is shut off and consumes no operating current
     */
    ADCON0bits.ADON = 0;
    /** ADCON0: bit 1
     * Unimplemented: Read as '0'
     */
    /** ADCON0: bit 2
     * GO/DONE (not): A/D Conversion Status bit
     * If ADON = 1:
     * 1 = A/D conversion in progress (setting this bit starts the A/D conversion)
     * 0 = A/D conversion not in progress (this bit is automatically cleared by hardware when the A/D conversion is complete)
     */
    /** ADCON0: bit 5-3
     * CHS<2:0>: Analog Channel Select bits
     * 000 = Channel 0 (RA0/AN0)
     * 001 = Channel 1 (RA1/AN1)
     * 010 = Channel 2 (RA2/AN2)
     * 011 = Channel 3 (RA3/AN3)
     * 100 = Channel 4 (RA4/AN4)
     * 101 = Channel 5 (RB6/AN5)
     * 110 = Channel 6 (RB7/AN6)
     */
    /** ADCON0: bit 7-6
     * ADCS<1:0>: A/D Conversion Clock Select bits
     * If ADCS2 = 0:
     * 00 = FOSC/2
     * 01 = FOSC/8
     * 10 = FOSC/32
     * 11 = FRC (clock derived from the internal A/D module RC oscillator)
     * If ADCS2 = 1:
     * 00 = FOSC/4
     * 01 = FOSC/16
     * 10 = FOSC/64
     * 11 = FRC (clock derived from the internal A/D module RC oscillator)
     */
}

inline void InitADCon1Reg() {
    /** ADCON1: bit 3-0
     * Unimplemented: Read as '0'
     */
    /** ADCON1: bit 5-4
     * VCFG<1:0>: A/D Voltage Reference Configuration bits
     * Logic State | VREF+ | VREF-
     * 00          | AVDD  | AVSS
     * 01          | AVDD  | VREF-
     * 10          | VREF+ | AVSS
     * 11          | VREF+ | VREF
     * Note: The ANSEL bits for AN3 and AN2 inputs must be configured as analog inputs for the VREF+ and VREF- external pins to be used.
     */
    /** ADCON1: bit 6
     * ADCS2: A/D Clock Divide by 2 Select bit
     * 1 = A/D clock source is divided by 2 when system clock is used
     * 0 = Disabled
     */
    /** ADCON1: bit 7
     * ADFM: A/D Result Format Select bit
     * 1 = Right justified. Six Most Significant bits of ADRESH are read as '0'
     * 0 = Left justified. Six Least Significant bits of ADRESL are read as '0'
     */
}

inline void InitAnSelReg() {
    /** ANSEL: bit 6-0
     * ANS<6:0>: Analog Input Select bits
     * Bits select input function on corresponding AN<6:0> pins.
     * 1 = Analog I/O
     * 0 = Digital I/O
     */
    ANSELbits.ANS0 = 0;
    ANSELbits.ANS1 = 0;
    ANSELbits.ANS2 = 0;
    ANSELbits.ANS3 = 0;
    ANSELbits.ANS4 = 0;
    ANSELbits.ANS5 = 0;
    ANSELbits.ANS6 = 0;
}

inline void InitPins() {
    Indicator0Pin = IndicatorOff;
    Indicator1Pin = IndicatorOff;
    Indicator2Pin = IndicatorOff;
    Indicator3Pin = IndicatorOff;
    Indicator4Pin = IndicatorOff;
    Indicator0PinDirection = OutputPinDirection;
    Indicator1PinDirection = OutputPinDirection;
    Indicator2PinDirection = OutputPinDirection;
    Indicator3PinDirection = OutputPinDirection;
    Indicator4PinDirection = OutputPinDirection;
    ButtonHoursPinDirection   = InputPinDirection;
    ButtonMinutesPinDirection = InputPinDirection;
    ButtonModePinDirection    = InputPinDirection;
    PowerStatePinDirection = InputPinDirection;
}

void main() {
    TRISA = 0b11111111;
    TRISB = 0b11111111;
    InitRegisters();
    InitPins();
    InitRTOS();
    RunRTOS();
    AddTask(CheckPowerTask, 0);
    while (1) {
        di();
        TaskManager();
        ei();
    }
}
