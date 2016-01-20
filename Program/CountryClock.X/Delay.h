#ifndef DELAY_H
#define	DELAY_H

/** Тактовая частота контроллера (Гц).
 */
#define F_OSC 4000000.0

/** Частота инструкций (Гц).
 */
#define F_CYC (F_OSC / 4.0)

/** Коэффициент предделителя для TMR0.
 */
#define PRESCALER_RATE (1.0 / 256.0)

/** Период (в секундах), через который вызывается прерывание по переполнению TMR0.
 * T_INT = 1024 / (F_OSC * PRESCALER_RATE)
 */
#define T_INT (1024.0 / (F_OSC * PRESCALER_RATE))

#define _XTAL_FREQ F_OSC

#endif /* DELAY_H */
