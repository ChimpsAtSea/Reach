#pragma once
#ifndef __ALLOCATION_INTERFACE_H__
#define __ALLOCATION_INTERFACE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_allocation_interface
{
public:
    virtual void * allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name) = 0;
    virtual void deallocate(void * pointer, char const * file, long line) = 0;
};

class c_base_allocation : public c_allocation_interface
{
public:
    virtual void * allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name);
    virtual void deallocate(void * pointer, char const * file, long line);
};

class c_heap_allocation : public c_allocation_interface
{
public:
    virtual void * allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name);
    virtual void deallocate(void * pointer, char const * file, long line);
};

class c_null_allocation : public c_allocation_interface
{
public:
    virtual void * allocate(unsigned int size, char const * file, long line, char const * type, char const * subtype, char const * name);
    virtual void deallocate(void * pointer, char const * file, long line);
};

/* ---------- prototypes */

/* ---------- globals */

extern c_base_allocation * g_base_allocation;
extern c_heap_allocation * g_heap_allocation;
extern c_null_allocation * g_null_allocation;

/* ---------- public code */

#endif // __ALLOCATION_INTERFACE_H__

