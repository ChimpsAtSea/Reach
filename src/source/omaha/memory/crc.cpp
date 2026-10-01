#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\crc.cpp"
/* ---------- headers */

#include "omaha\memory\crc.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"

#pragma optimize("gt", on)

/* ---------- constants */

long const k_crc_table_size = 256;
unsigned long const k_crc32_polynomial = 0xEDB88320;
unsigned long const k_crc_prefetch_size = 128 * 1024;
long const k_adler32_block_size = 5552;
unsigned long const k_adler32_base = 65521;
unsigned long const k_fast_checksum_seed = 0xDEADBEEF;

/* ---------- definitions */

/* ---------- prototypes */

void build_crc_table(unsigned long * crc_table);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// unsigned long crc_checksum_buffer(unsigned long, void const *, long);
// void crc_checksum_buffer_alder32(unsigned long *, void const *, long);
// unsigned long fast_checksum_buffer(unsigned long, void const *, long);
// unsigned long fast_checksum_3(unsigned long, unsigned long, unsigned long, unsigned long);
// void build_crc_table(unsigned long *);

// $TODO nonmatching
unsigned long crc_checksum_buffer(unsigned long crc, void const * buffer, long buffer_size)
{
    mangled_ppc("?crc_checksum_buffer@@YAKKPBXJ@Z");

    static unsigned long crc_table[k_crc_table_size];
    static bool crc_table_built = false;

    prefetch_block(buffer, MIN(static_cast<unsigned long>(buffer_size), k_crc_prefetch_size));
    assert_tag_debug_untracked_jul_11_2011(49, buffer_size>=0);

    if (!crc_table_built)
    {
        build_crc_table(crc_table);
        crc_table_built = true;
    }

    unsigned char const * p = static_cast<unsigned char const *>(buffer);
    unsigned long a;
    unsigned long b;

    while (buffer_size > 0)
    {
        a = (crc >> 8) & 0x00FFFFFF;
        b = crc_table[(crc ^ *p++) & 0xFF];
        crc = a ^ b;
        buffer_size--;
    }

    return crc;
};

void crc_checksum_buffer_alder32(unsigned long * crc_reference, void const * buffer, long buffer_size)
{
    mangled_ppc("?crc_checksum_buffer_alder32@@YAXPAKPBXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(84, buffer);
    assert_tag_debug_untracked_jul_11_2011(85, buffer_size>=0);

    unsigned char const * p = static_cast<unsigned char const *>(buffer);
    unsigned long s1 = 1;
    unsigned long s2 = 0;

    while (buffer_size > 0)
    {
        long block_size = buffer_size < k_adler32_block_size ? buffer_size : k_adler32_block_size;
        buffer_size -= block_size;

        while (block_size-- != 0)
        {
            s1 += *p++;
            s2 += s1;
        }

        s1 %= k_adler32_base;
        s2 %= k_adler32_base;
    }

    *crc_reference = (s2 << 16) | s1;
};

// $TODO nonmatching
unsigned long fast_checksum_buffer(unsigned long crc, void const * buffer, long buffer_size)
{
    mangled_ppc("?fast_checksum_buffer@@YAKKPBXJ@Z");

    unsigned long const * k = static_cast<unsigned long const *>(buffer);
    unsigned long length = static_cast<unsigned long>(buffer_size);

    unsigned long a;
    unsigned long b;
    unsigned long c;

    long prefetch_size = MIN(length, k_crc_prefetch_size);
    a = b = c = k_fast_checksum_seed + length + crc;
    prefetch_block(buffer, prefetch_size);

    while (length > 12)
    {
        a += k[0];
        b += k[1];
        c += k[2];
        FAST_CHECKSUM_MIX(a, b, c);
        length -= 12;
        k += 3;
    }

    if (length != 0)
    {
        switch (length)
        {
        case 12:
            a += k[0];
            b += k[1];
            c += k[2];
            break;
        case 11:
            a += k[0];
            b += k[1];
            c += k[2] >> 8;
            break;
        case 10:
            a += k[0];
            b += k[1];
            c += k[2] >> 16;
            break;
        case 9:
            a += k[0];
            b += k[1];
            c += k[2] >> 24;
            break;
        case 8:
            a += k[0];
            b += k[1];
            break;
        case 7:
            a += k[0];
            b += k[1] >> 8;
            break;
        case 6:
            a += k[0];
            b += k[1] >> 16;
            break;
        case 5:
            a += k[0];
            b += k[1] >> 24;
            break;
        case 4:
            a += k[0];
            break;
        case 3:
            a += k[0] >> 8;
            break;
        case 2:
            a += k[0] >> 16;
            break;
        case 1:
            a += k[0] >> 24;
            break;
        default:
            break;
        }

        FAST_CHECKSUM_FINAL(a, b, c);
    }

    return c;
};

// $TODO nonmatching
unsigned long fast_checksum_3(unsigned long crc, unsigned long data0, unsigned long data1, unsigned long data2)
{
    mangled_ppc("?fast_checksum_3@@YAKKKKK@Z");

    unsigned long a;
    unsigned long b;
    unsigned long c;

    a = b = c = k_fast_checksum_seed + 12 + crc;

    a += data0;
    b += data1;
    c += data2;

    FAST_CHECKSUM_FINAL(a, b, c);

    return c;
};

//void build_crc_table(unsigned long *)
//{
//    mangled_ppc("?build_crc_table@@YAXPAK@Z");
//};

