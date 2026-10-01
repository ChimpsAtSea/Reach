#pragma once
#ifndef __CRC_H__
#define __CRC_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

#define FAST_CHECKSUM_ROTATE_XOR(_value, _bits) (((_value) << (_bits)) ^ ((_value) >> (32 - (_bits))))
// $TODO the target's FINAL rotates compile to srwi/slwi/or, but XDK 9328 cl turns the plain
// `(v << n) | (v >> (32 - n))` idiom into rotlwi; the multiply form blocks that (closest match found)
#define FAST_CHECKSUM_ROTATE(_value, _bits) (((_value) * (1u << (_bits))) | ((_value) >> (32 - (_bits))))

#define FAST_CHECKSUM_MIX(_a, _b, _c) \
do \
{ \
    _a -= _c; _a ^= FAST_CHECKSUM_ROTATE_XOR(_c, 4);  _c += _b; \
    _b -= _a; _b ^= FAST_CHECKSUM_ROTATE_XOR(_a, 6);  _a += _c; \
    _c -= _b; _c ^= FAST_CHECKSUM_ROTATE_XOR(_b, 8);  _b += _a; \
    _a -= _c; _a ^= FAST_CHECKSUM_ROTATE_XOR(_c, 16); _c += _b; \
    _b -= _a; _b ^= FAST_CHECKSUM_ROTATE_XOR(_a, 19); _a += _c; \
    _c -= _b; _c ^= FAST_CHECKSUM_ROTATE_XOR(_b, 4);  _b += _a; \
} \
while (false)

#define FAST_CHECKSUM_FINAL(_a, _b, _c) \
do \
{ \
    _c ^= _b; _c -= FAST_CHECKSUM_ROTATE(_b, 14); \
    _a ^= _c; _a -= FAST_CHECKSUM_ROTATE(_c, 11); \
    _b ^= _a; _b -= FAST_CHECKSUM_ROTATE(_a, 25); \
    _c ^= _b; _c -= FAST_CHECKSUM_ROTATE(_b, 16); \
    _a ^= _c; _a -= FAST_CHECKSUM_ROTATE(_c, 4); \
    _b ^= _a; _b -= FAST_CHECKSUM_ROTATE(_a, 14); \
    _c ^= _b; _c -= FAST_CHECKSUM_ROTATE(_b, 24); \
} \
while (false)

/* ---------- prototypes */

unsigned long crc_checksum_buffer(unsigned long crc, void const * buffer, long buffer_size);
void crc_checksum_buffer_alder32(unsigned long * crc_reference, void const * buffer, long buffer_size);
unsigned long fast_checksum_buffer(unsigned long crc, void const * buffer, long buffer_size);
unsigned long fast_checksum_3(unsigned long crc, unsigned long data0, unsigned long data1, unsigned long data2);

inline unsigned long crc_new()
{
    mangled_ppc("?crc_new@@YAKXZ");

    return 0xFFFFFFFF;
};

// $TODO inline template in the target (f i, determinism_debug_consumers.obj); body not reversed yet
template<typename t_type>
unsigned long fast_checksum(unsigned long crc, t_type const * data);

/* ---------- globals */

/* ---------- public code */

#endif // __CRC_H__

