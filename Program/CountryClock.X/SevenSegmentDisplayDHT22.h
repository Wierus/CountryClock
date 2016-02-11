/** SevenSegmentDisplayDHT22.h
 * v.1.0
 */

#ifndef SEVENSEGMENTDISPLAYDHT22_H
#define	SEVENSEGMENTDISPLAYDHT22_H

/** Выводит значение влажности с датчика DHT22 и символ "h" на 5 семисегментных индикаторов.
 * @param indicatorValues Массив, в который будет выведено значение влажности и символ "h". Массив должен иметь длину равную пяти.
 */
void FillIndicators5WithDHT22HumidityAndSymbolLowerLetterH(unsigned char* indicatorValues);

/** Выводит значение температуры с датчика DHT22 и символ "градус" на 5 семисегментных индикаторов.
 * @param indicatorValues Массив, в который будет выведено значение температуры и символ "градус". Массив должен иметь длину равную пяти.
 */
void FillIndicators5WithDHT22TemperatureAndSymbolDegree(unsigned char* indicatorValues);

#endif	/* SEVENSEGMENTDISPLAYDHT22_H */
