#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>

/** Device: PIC16F88
 * ("16f88.html" and "30487D.pdf")
 */

/** CONFIG1: bit 4, 1-0
 * FOSC<2:0>: Oscillator Selection bits
 * 111 = EXTRCCLK  = EXTRC oscillator; CLKO function on RA6/OSC2/CLKO
 * 110 = EXTRCIO   = EXTRC oscillator; port I/O function on RA6/OSC2/CLKO
 * 101 = INTOSCCLK = INTRC oscillator; CLKO function on RA6/OSC2/CLKO pin and port I/O function on RA7/OSC1/CLKI pin
 * 100 = INTOSCIO  = INTRC oscillator; port I/O function on both RA6/OSC2/CLKO pin and RA7/OSC1/CLKI pin
 * 011 = EC        = ECIO; port I/O function on RA6/OSC2/CLKO
 * 010 = HS        = HS oscillator
 * 001 = XT        = XT oscillator
 * 000 = LP        = LP oscillator
 */
#pragma config FOSC = HS

/** CONFIG1: bit 2
 * WDTE: Watchdog Timer Enable bit
 * 1 = ON  = WDT enabled
 * 0 = OFF = WDT disabled
 */
#pragma config WDTE = OFF

/** CONFIG1: bit 3
 * PWRTE (not): Power-up Timer Enable bit
 * 1 = OFF = PWRT disabled
 * 0 = ON  = PWRT enabled
 */
#pragma config PWRTE = OFF

/** CONFIG1: bit 5
 * MCLRE: RA5/MCLR/VPP Pin Function Select bit
 * 1 = ON  = RA5/MCLR/VPP pin function is MCLR
 * 0 = OFF = RA5/MCLR/VPP pin function is digital I/O, MCLR internally tied to VDD
 */
#pragma config MCLRE = ON

/** CONFIG1: bit 6
 * BOREN: Brown-out Reset Enable bit
 * 1 = ON  = BOR enabled
 * 0 = OFF = BOR disabled
 */
#pragma config BOREN = OFF

/** CONFIG1: bit 7
 * LVP: Low-Voltage Programming Enable bit
 * 1 = ON  = RB3/PGM pin has PGM function, Low-Voltage Programming enabled
 * 0 = OFF = RB3 is digital I/O, HV on MCLR must be used for programming
 */
#pragma config LVP = OFF

/** CONFIG1: bit 8
 * CPD: Data EE Memory Code Protection bit
 * 1 = OFF = Code protection off
 * 0 = ON  = Data EE memory code-protected
 */
#pragma config CPD = OFF

/** CONFIG1: bit 10-9
 * WRT<1:0>: Flash Program Memory Write Enable bits
 * 11 = OFF  = Write protection off
 * 10 = 2048 = 0000h to 00FFh write-protected, 0100h to 0FFFh may be modified by EECON control
 * 01 = 256  = 0000h to 07FFh write-protected, 0800h to 0FFFh may be modified by EECON control
 * 00 = ALL  = 0000h to 0FFFh write-protected
 */
#pragma config WRT = OFF

/** CONFIG1: bit 11
 * DEBUG: In-Circuit Debugger Mode bit
 * 1 = OFF = In-Circuit Debugger disabled, RB6 and RB7 are general purpose I/O pins
 * 0 = ON  = In-Circuit Debugger enabled, RB6 and RB7 are dedicated to the debugger
 */
#pragma config DEBUG = OFF

/** CONFIG1: bit 12
 * CCPMX: CCP1 Pin Selection bit
 * 1 = RB0 = CCP1 function on RB0
 * 0 = RB3 = CCP1 function on RB3
 */
#pragma config CCPMX = RB0

/** CONFIG1: bit 13
 * CP: Flash Program Memory Code Protection bits
 * 1 = OFF = Code protection off
 * 0 = ON  = 0000h to 0FFFh code-protected (all protected)
 */
#pragma config CP = OFF

/** CONFIG2: bit 0
 * FCMEN: Fail-Safe Clock Monitor Enable bit
 * 1 = ON  = Fail-Safe Clock Monitor enabled
 * 0 = OFF = Fail-Safe Clock Monitor disabled
 */
#pragma config FCMEN = OFF

/** CONFIG2: bit 1
 * IESO: Internal External Switchover bit
 * 1 = ON  = Internal External Switchover mode enabled
 * 0 = OFF = Internal External Switchover mode disabled
 */
#pragma config IESO = OFF

/** Тактовая частота контроллера (Гц).
 */
#define F_OSC 4000000.0

/** Коэффициент предделителя для TMR0.
 */
#define PRESCALER_RATE (1.0 / 256.0)

/** Длина очереди задач для диспетчера.
 */
#define TaskManagerQueueSize 5

/** Тип таймера задач для диспетчера.
 */
#define TaskManagerTimerType unsigned char

#endif /* CONFIG_H */
