/* ---------- headers */

#include "threadlib\job_signature.h"
#include "foundation\baselib\datatypes\hash.h"

#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_job_pre_post::c_job_pre_post(void (*)(void), void (*)(void), char const *);
// unsigned long context_string_hash(char const *);

c_job_pre_post::c_job_pre_post(job_pre_post_function_t pre_function, job_pre_post_function_t post_function, char const * name)
{
    mangled_ppc("??0c_job_pre_post@@QAA@P6AXXZ0PBD@Z");

    m_pre_function = pre_function;
    m_post_function = post_function;
    m_name = name;
    m_hash = context_string_hash(name);
};

unsigned long context_string_hash(char const * string)
{
    mangled_ppc("?context_string_hash@@YAKPBD@Z");

    c_hash hash;
    hash.add_data_range(string, strnlen(string, 256));
    return hash.get_hash();
};

