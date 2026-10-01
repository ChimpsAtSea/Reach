/* ---------- headers */

#include "blamlib\minidump_helper.h"

#include "core\corelib\cseries\cseries_macros.h"

#include <excpt.h>
#include <stdlib.h>
#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// unsigned char bytes_swap(unsigned char);
// unsigned short bytes_swap(unsigned short);
// unsigned int bytes_swap(unsigned int);
// unsigned long bytes_swap(unsigned long);
// unsigned __int64 bytes_swap(unsigned __int64);
// signed char bytes_swap(signed char);
// short bytes_swap(short);
// int bytes_swap(int);
// long bytes_swap(long);
// __int64 bytes_swap(__int64);
// void bytes_swap(unsigned short *);
// void bytes_swap(wchar_t *);
// float bytes_swap(float);
// double bytes_swap(double);
// __int64 convert_32bit_address_to_64bit_value(void const *);
// bool ansi_to_wide(char const *, unsigned short *, long);
// bool ansi_to_wide(char const *, wchar_t *, long);
// bool is_bad_read_ptr(void const *, unsigned long);

unsigned char bytes_swap(unsigned char value)
{
    mangled_ppc("?bytes_swap@@YAEE@Z");
    return value;
};

unsigned short bytes_swap(unsigned short value)
{
    mangled_ppc("?bytes_swap@@YAGG@Z");
    return _byteswap_ushort(value);
};

unsigned int bytes_swap(unsigned int value)
{
    mangled_ppc("?bytes_swap@@YAII@Z");
    unsigned int result = _byteswap_ulong(value);
    return result;
};

unsigned long bytes_swap(unsigned long value)
{
    mangled_ppc("?bytes_swap@@YAKK@Z");
    return _byteswap_ulong(value);
};

unsigned __int64 bytes_swap(unsigned __int64 value)
{
    mangled_ppc("?bytes_swap@@YA_K_K@Z");
    return _byteswap_uint64(value);
};

signed char bytes_swap(signed char value)
{
    mangled_ppc("?bytes_swap@@YACC@Z");
    return value;
};

short bytes_swap(short value)
{
    mangled_ppc("?bytes_swap@@YAFF@Z");
    short result = _byteswap_ushort(value);
    return result;
};

int bytes_swap(int value)
{
    mangled_ppc("?bytes_swap@@YAHH@Z");
    int result = _byteswap_ulong(value);
    return result;
};

long bytes_swap(long value)
{
    mangled_ppc("?bytes_swap@@YAJJ@Z");
    long result = _byteswap_ulong(value);
    return result;
};

__int64 bytes_swap(__int64 value)
{
    mangled_ppc("?bytes_swap@@YA_J_J@Z");
    __int64 result = _byteswap_uint64(value);
    return result;
};

void bytes_swap(unsigned short* value)
{
    mangled_ppc("?bytes_swap@@YAXPAG@Z");
    if (value)
    {
        while (*value)
        {
            *value = _byteswap_ushort(*value);
            value++;
        }
    }
};

void bytes_swap(wchar_t* value)
{
    mangled_ppc("?bytes_swap@@YAXPA_W@Z");
    bytes_swap(reinterpret_cast<unsigned short*>(value));
};

float bytes_swap(float value)
{
    mangled_ppc("?bytes_swap@@YAMM@Z");
    unsigned long result = _byteswap_ulong(*reinterpret_cast<unsigned long*>(&value));
    return *reinterpret_cast<float*>(&result);
};

double bytes_swap(double value)
{
    mangled_ppc("?bytes_swap@@YANN@Z");
    unsigned __int64 result = _byteswap_uint64(*reinterpret_cast<unsigned __int64*>(&value));
    return *reinterpret_cast<double*>(&result);
};

__int64 convert_32bit_address_to_64bit_value(void const* address)
{
    mangled_ppc("?convert_32bit_address_to_64bit_value@@YA_JPBX@Z");
    return reinterpret_cast<long>(address);
};

bool ansi_to_wide(char const* source, unsigned short* destination, long maximum_count)
{
    mangled_ppc("?ansi_to_wide@@YA_NPBDPAGJ@Z");
    bool result = false;
    long index = 0;
    if (source && destination && maximum_count > 0)
    {
        while (index < maximum_count - 1 && *source)
        {
            *destination = static_cast<unsigned short>(*source);
            destination++;
            source++;
            index++;
        }
        *destination = 0;
        result = true;
    }
    return result;
};

bool ansi_to_wide(char const* source, wchar_t* destination, long maximum_count)
{
    mangled_ppc("?ansi_to_wide@@YA_NPBDPA_WJ@Z");
    return ansi_to_wide(source, reinterpret_cast<unsigned short*>(destination), maximum_count);
};

bool is_bad_read_ptr(void const* pointer, unsigned long size)
{
    mangled_ppc("?is_bad_read_ptr@@YA_NPBXK@Z");
    bool result = false;

    {
        unsigned long alignment = 0;

        {
            unsigned long const alignments[] = { 8, 4, 2, 1 };
            for (unsigned long alignment_index = 0; alignment_index < NUMBEROF(alignments); alignment_index++)
            {
                if (size % alignments[alignment_index] == 0)
                {
                    alignment = alignments[alignment_index];
                    break;
                }
            }
        }

        if (alignment > 0)
        {
            unsigned __int64 buffer = 0;
            char const* address = static_cast<char const*>(pointer);
            __try
            {
                for (unsigned long index = 0; index < size / alignment; index++)
                {
                    memmove(&buffer, address + index * alignment, alignment);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER)
            {
                result = true;
            }
        }
        else
        {
            result = true;
        }
    }

    return result;
};

