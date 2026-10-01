#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\datatypes\\hash.cpp"
/* ---------- headers */

#include "foundation\baselib\datatypes\hash.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

long const k_hash_polynomial_count = 15;

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static unsigned char const k_hash_polynomial[k_hash_polynomial_count] = { 3, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59 };

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: unsigned long c_hash::add_byte(unsigned char);
// public: unsigned long c_hash::add_data_range(void const *, unsigned int);

unsigned long c_hash::add_byte(unsigned char in_value)
{
    mangled_ppc("?add_byte@c_hash@@QAAKE@Z");

    unsigned long key = in_value;
    assert_tag_debug_untracked_jul_11_2011(27, VALID_INDEX(m_polynomial_index, k_hash_polynomial_count));

    unsigned long hash_polynomial = k_hash_polynomial[m_polynomial_index];
    m_polynomial_index = (m_polynomial_index + 1) % k_hash_polynomial_count;
    m_hash += key * hash_polynomial;

    return m_hash;
};

unsigned long c_hash::add_data_range(void const * data, unsigned int count)
{
    mangled_ppc("?add_data_range@c_hash@@QAAKPBXI@Z");

    unsigned char const * bytes = static_cast<unsigned char const *>(data);
    for (unsigned int byte_index = 0; byte_index < count; byte_index++)
    {
        add_byte(bytes[byte_index]);
    }

    return m_hash;
};

