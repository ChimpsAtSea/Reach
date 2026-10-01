#pragma once
#ifndef __MINIDUMP_HELPER_H__
#define __MINIDUMP_HELPER_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

unsigned char bytes_swap(unsigned char value);
unsigned short bytes_swap(unsigned short value);
unsigned int bytes_swap(unsigned int value);
unsigned long bytes_swap(unsigned long value);
unsigned __int64 bytes_swap(unsigned __int64 value);
signed char bytes_swap(signed char value);
short bytes_swap(short value);
int bytes_swap(int value);
long bytes_swap(long value);
__int64 bytes_swap(__int64 value);
void bytes_swap(unsigned short * value);
void bytes_swap(wchar_t * value);
float bytes_swap(float value);
double bytes_swap(double value);
__int64 convert_32bit_address_to_64bit_value(void const * address);
bool is_bad_read_ptr(void const * pointer, unsigned long size);

/* ---------- globals */

/* ---------- public code */

#endif // __MINIDUMP_HELPER_H__

