/** Math.h
 * v.1.0
 */

#ifndef MATH_H
#define	MATH_H

unsigned char GetD0OfU08(unsigned char value);
unsigned char GetD1OfU08(unsigned char value);
unsigned char GetD2OfU08(unsigned char value);

unsigned char GetD0OfU16(unsigned short value);
unsigned char GetD1OfU16(unsigned short value);
unsigned char GetD2OfU16(unsigned short value);
unsigned char GetD3OfU16(unsigned short value);
unsigned char GetD4OfU16(unsigned short value);

unsigned char GetD0OfBCD(unsigned char value);
unsigned char GetD1OfBCD(unsigned char value);

#endif /* MATH_H */
