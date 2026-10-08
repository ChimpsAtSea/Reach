#pragma once
#ifndef __ALLOCATION_INTERFACE_H__
#define __ALLOCATION_INTERFACE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_allocation_interface
{
public:
    c_allocation_interface(void);

    virtual void * allocate(unsigned int, char const *, long, char const *, char const *, char const *) = 0;
    virtual void deallocate(void *, char const *, long) = 0;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __ALLOCATION_INTERFACE_H__

