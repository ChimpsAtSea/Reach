#pragma once
#ifndef __HASH_H__
#define __HASH_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_hash
{
public:
    c_hash() :
        m_hash(0),
        m_polynomial_index(0)
    {
        mangled_ppc("??0c_hash@@QAA@XZ");
    };

    ~c_hash()
    {
        mangled_ppc("??1c_hash@@QAA@XZ");
    };

    unsigned long add_byte(unsigned char in_value);
    unsigned long add_data_range(void const * data, unsigned int count);

    unsigned long get_hash() const
    {
        mangled_ppc("?get_hash@c_hash@@QBAKXZ");

        return m_hash;
    };

private:
    unsigned long m_hash;
    long m_polynomial_index;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HASH_H__

