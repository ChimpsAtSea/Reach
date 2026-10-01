/* ---------- headers */

#include "blamlib\string_table.h"
#include "omaha\physics\havok_memory.h"

/* ---------- constants */

long const k_string_table_scratch_buffer_size = 0x4B000;

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static c_havok_overflow_memory_borrower borrower;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_string_table_scratch_buffer::c_string_table_scratch_buffer(void);
// public: c_string_table_scratch_buffer::~c_string_table_scratch_buffer(void);
// public: void * c_string_table_scratch_buffer::get_buffer(void);
// public: unsigned long c_string_table_scratch_buffer::get_buffer_size(void);

c_string_table_scratch_buffer::c_string_table_scratch_buffer()
{
    mangled_ppc("??0c_string_table_scratch_buffer@@QAA@XZ");

    borrower.initialize("string table scratch buffer", k_string_table_scratch_buffer_size);
};

c_string_table_scratch_buffer::~c_string_table_scratch_buffer()
{
    mangled_ppc("??1c_string_table_scratch_buffer@@QAA@XZ");

    borrower.dispose();
};

void * c_string_table_scratch_buffer::get_buffer()
{
    mangled_ppc("?get_buffer@c_string_table_scratch_buffer@@QAAPAXXZ");

    return borrower.get_buffer();
};

unsigned long c_string_table_scratch_buffer::get_buffer_size()
{
    mangled_ppc("?get_buffer_size@c_string_table_scratch_buffer@@QAAKXZ");

    return borrower.get_buffer_size();
};

