/** SR74HC164.h
 * v.1.1
 */

#ifndef SR74HC164_H
#define	SR74HC164_H

#include "Pins.h"

#ifndef SR74HC164ClockPin
    #error "SR74HC164ClockPin symbol is not defined, you should define it in file Pins.h before using this library"
#endif

#ifndef SR74HC164ClockPinDirection
    #error "SR74HC164ClockPinDirection symbol is not defined, you should define it in file Pins.h before using this library"
#endif

#ifndef SR74HC164DataPin
    #error "SR74HC164DataPin symbol is not defined, you should define it in file Pins.h before using this library"
#endif

#ifndef SR74HC164DataPinDirection
    #error "SR74HC164DataPinDirection symbol is not defined, you should define it in file Pins.h before using this library"
#endif

/** Инициализирует сдвиговый регистр.
 */
void SR74HC164Initialize();

/** Отправляет байт в сдвиговый регистр, начиная со старшего бита.
 * @param byte Отправляемый байт.
 */
void SR74HC164SendByte(unsigned char value);

#endif	/* SR74HC164_H */
