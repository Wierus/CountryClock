/** SevenSegmentDisplayDS18B20.h
 * v.1.5
 */

#ifndef SEVENSEGMENTDISPLAYDS18B20_H
#define	SEVENSEGMENTDISPLAYDS18B20_H

#include "DS18B20.h"
#include "Math.h"
#include "SevenSegmentDisplay.h"

/** Выводит значение температуры с датчика DS18B20 на 3 семисегментных индикатора.
 * @param indicatorValues Массив, в который будет выведено значение температуры. Массив должен иметь длину равную трем.
 */
void FillIndicators3WithDS18B20Temperature(unsigned char* indicatorValues);

/** Выводит значение температуры с датчика DS18B20 на индикатор символа "минус" и 3 семисегментных индикатора.
 * @param indicatorValues Массив, в который будет выведено значение температуры. Массив должен иметь длину равную трем.
 * @param indicatorSign Указатель на переменную, в которую будет записано состояние индикатора символа "минус" (включен или выключен).
 */
void FillIndicators3AndSignWithDS18B20Temperature(unsigned char* indicatorValues, unsigned char* indicatorSign);

/** Выводит значение температуры с датчика DS18B20 и символ "градус" на 5 семисегментных индикаторов.
 * @param indicatorValues Массив, в который будет выведено значение температуры и символ "градус". Массив должен иметь длину равную пяти.
 */
void FillIndicators5WithDS18B20TemperatureAndSymbolDegree(unsigned char* indicatorValues);

#endif	/* SEVENSEGMENTDISPLAYDS18B20_H */
