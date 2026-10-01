#pragma once
#ifndef __BITMAP_USAGE_H__
#define __BITMAP_USAGE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_bitmap_usage
{
public:
    enum e_format
    {
        // 59 entries matching bitmap_usage_format_def (enumerator names unknown)
        _format_use_default = 0,

        k_format_count = 59
    };

public:
    static long get_pc_bitmap_format(e_format format);
    static long get_xenon_bitmap_format(e_format format);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __BITMAP_USAGE_H__

