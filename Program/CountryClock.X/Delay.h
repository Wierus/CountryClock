/** Delay.h
 * v.1.0
 */

#ifndef DELAY_H
#define	DELAY_H

#include "Config.h"

/** Тактовая частота контроллера (Гц).
 */
#ifndef F_OSC
    #error "F_OSC symbol is not defined, you should define it in file Config.h before using this library"
#endif

/** Коэффициент предделителя для TMR0.
 */
#ifndef PRESCALER_RATE
    #error "PRESCALER_RATE symbol is not defined, you should define it in file Config.h before using this library"
#endif

/** Частота инструкций (Гц).
 */
#define F_CYC (F_OSC / 4.0)

/** Период инструкций (с).
 */
#define T_CYC (1.0 / F_CYC)

/** Количество инструкций для переполнения TMR0.
 */
#define N_CYC_INT (256.0 / PRESCALER_RATE)

/** Период (в секундах), через который вызывается прерывание по переполнению TMR0.
 * T_INT = N_CYC_INT * T_CYC
 */
#define T_INT (1024.0 / (F_OSC * PRESCALER_RATE))

#define _XTAL_FREQ F_OSC

#endif /* DELAY_H */
