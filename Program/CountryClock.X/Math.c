/** Math.c
 * v.1.0
 */

#include "Math.h"

unsigned char GetD0OfU08(unsigned char value) {
    while (value >= 100) {
        value -=100;
    }
    while (value >= 10) {
        value -=10;
    }
    return value;
}

unsigned char GetD1OfU08(unsigned char value) {
    unsigned char d1 = 0;
    while (value >= 100) {
        value -=100;
    }
    while (value >= 10) {
        value -=10;
        ++d1;
    }
    return d1;
}

unsigned char GetD2OfU08(unsigned char value) {
    unsigned char d2 = 0;
    while (value >= 100) {
        value -=100;
        ++d2;
    }
    return d2;
}

unsigned char GetD0OfU16(unsigned short value) {
    while (value >= 10000) {
        value -=10000;
    }
    while (value >= 1000) {
        value -=1000;
    }
    while (value >= 100) {
        value -=100;
    }
    while (value >= 10) {
        value -=10;
    }
    return value;
}

unsigned char GetD1OfU16(unsigned short value) {
    unsigned char d1 = 0;
    while (value >= 10000) {
        value -=10000;
    }
    while (value >= 1000) {
        value -=1000;
    }
    while (value >= 100) {
        value -=100;
    }
    while (value >= 10) {
        value -= 10;
        ++d1;
    }
    return d1;
}

unsigned char GetD2OfU16(unsigned short value) {
    unsigned char d2 = 0;
    while (value >= 10000) {
        value -=10000;
    }
    while (value >= 1000) {
        value -=1000;
    }
    while (value >= 100) {
        value -= 100;
        ++d2;
    }
    return d2;
}

unsigned char GetD3OfU16(unsigned short value) {
    unsigned char d3 = 0;
    while (value >= 10000) {
        value -=10000;
    }
    while (value >= 1000) {
        value -= 1000;
        ++d3;
    }
    return d3;
}

unsigned char GetD4OfU16(unsigned short value) {
    unsigned char d4 = 0;
    while (value >= 10000) {
        value -=10000;
        ++d4;
    }
    return d4;
}

unsigned char GetD0OfBCD(unsigned char value) {
    return value & 0x0F;
}

unsigned char GetD1OfBCD(unsigned char value) {
    return value >> 4;
}
