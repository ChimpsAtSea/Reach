#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib\\multithreading\\profiler\\mt_profiler_store.cpp"
/* ---------- headers */

#include "foundation\threadlib\multithreading\profiler\mt_profiler_store.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "baselib\synchronized_value_windows.h"
#include "foundation\baselib\datatypes\indexed_list.h"

/* ---------- constants */

long const k_mtp_colors_max = 27;
long const k_mtp_max_global_defs = 1024;
long const k_mtp_max_name_defs = 1024;
long const k_mtp_alloc_history_count = 240;
unsigned long const k_profiler_backing_memory_size = 0x20000;

/* ---------- definitions */

/* ---------- prototypes */

float smoothstep(float edge0, float edge1, float x);
unsigned short get_color_index(e_mt_color color);
unsigned short get_name_index(char const * name);
unsigned short get_global_index(unsigned short group_name_index, unsigned short name_index, unsigned short color_index);
void initialize_history(void);
long enough_free(long size);
unsigned char * allocate_frame(long size);
s_profiler_frame_header * get_frame(long offset);

/* ---------- globals */

// the table holds one entry past k_mtp_colors_max (.data size 0x70)
unsigned long g_mtp_profiler_colors[k_mtp_colors_max + 1] =
{
    0xFFFF0000, 0xFF3F0000,
    0xFF00FF00, 0xFF003F00,
    0xFF0000FF, 0xFF00003F,
    0xFF00FFFF, 0xFF003F3F,
    0xFFFF00FF, 0xFF3F003F,
    0xFFFFFF00, 0xFF3F3F00,
    0xFF800080, 0xFF200020,
    0xFFFFC0CB, 0xFF3F3032,
    0xFFFF69B4, 0xFF3F1A2D,
    0xFFFFA500, 0xFF3F2900,
    0x1F7F7F7F, 0x1F1F1F1F,
    0xFFFF0000, 0xFF3F0000,
    0xFFFFFFFF, 0xFF000000,
    0xFFFFFFFF, 0x00000000,
};
bool g_capture_allowed = true;
c_indexed_list<long, k_mtp_alloc_history_count> g_alloc_list;
unsigned char profiler_backing_memory[k_profiler_backing_memory_size];
s_global_def g_mtp_global_defs[k_mtp_max_global_defs];
char const * g_mtp_name_defs[k_mtp_max_name_defs];
long g_cur_offset;
e_mt_profiler_mode g_mt_profiler_mode;
c_synchronized_int32 g_mtp_used_global_defs;
c_synchronized_int32 g_mtp_used_name_defs;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// unsigned long *g_mtp_profiler_colors; // "?g_mtp_profiler_colors@@3PAKA"
// bool g_capture_allowed; // "?g_capture_allowed@@3_NA"
// class c_indexed_list<long, 240> g_alloc_list; // "?g_alloc_list@@3V?$c_indexed_list@J$0PA@@@A"
// unsigned char *profiler_backing_memory; // "?profiler_backing_memory@@3PAEA"
// struct s_global_def *g_mtp_global_defs; // "?g_mtp_global_defs@@3PAUs_global_def@@A"
// char const **g_mtp_name_defs; // "?g_mtp_name_defs@@3PAPBDA"
// long g_cur_offset; // "?g_cur_offset@@3JA"
// enum e_mt_profiler_mode g_mt_profiler_mode; // "?g_mt_profiler_mode@@3W4e_mt_profiler_mode@@A"
// class c_synchronized_int32g_mtp_used_global_defs; // "?g_mtp_used_global_defs@@3Vc_synchronized_int32@@A"
// class c_synchronized_int32g_mtp_used_name_defs; // "?g_mtp_used_name_defs@@3Vc_synchronized_int32@@A"

// unsigned long mt_profiler_get_color_from_index(long);
// float smoothstep(float, float, float);
// unsigned long mt_profiler_get_color_from_user(float, float);
// char const * mt_profiler_get_name_from_index(long);
// unsigned short get_color_index(enum e_mt_color);
// unsigned short get_name_index(char const *);
// unsigned short get_global_index(unsigned short, unsigned short, unsigned short);
// public: void s_global_def::set(unsigned short, unsigned short, unsigned short);
// unsigned short profiler_get_index(char const *, char const *, enum e_mt_color);
// struct s_mt_context_detail mt_profiler_get_context_detail(unsigned short);
// void initialize_history(void);
// long enough_free(long);
// unsigned char * allocate_frame(long);
// struct s_profiler_frame_header * get_frame(long);
// struct s_profiler_frame_header * profiler_storage_request(unsigned long, unsigned long);
// struct s_profiler_frame_header * mt_profiler_get_frame(long);
// void mt_profiler_toggle_capture(void);
// void profiler_publish_frame(struct s_profiler_frame_header *);
// void mt_profiler_initialize(void);
// void mt_profiler_dispose(void);
// void mt_profiler_set_mode(enum e_mt_profiler_mode);
// enum e_mt_profiler_mode mt_profiler_get_mode(void);
// public: class c_indexed_list<long, 240>::iterator c_indexed_list<long, 240>::begin(void);
// public: class c_indexed_list<long, 240>::iterator c_indexed_list<long, 240>::end(void);
// public: long c_indexed_list<long, 240>::count(void) const;
// public: bool c_indexed_list<long, 240>::full(void) const;
// public: c_indexed_list<long, 240>::const_iterator::const_iterator(class c_indexed_list<long, 240>::iterator const &);
// public: long const & c_indexed_list<long, 240>::const_iterator::operator*(void) const;
// public: long & c_indexed_list<long, 240>::iterator::operator*(void);
// public: class c_indexed_list<long, 240>::iterator & c_indexed_list<long, 240>::iterator::operator--(void);
// private: unsigned short c_indexed_list<long, 240>::get_next(unsigned short) const;
// private: unsigned short c_indexed_list<long, 240>::get_prev(unsigned short) const;
// private: unsigned short c_indexed_list<long, 240>::get_head(void) const;
// private: unsigned short c_indexed_list<long, 240>::get_tail(void) const;
// private: long & c_indexed_list<long, 240>::get_data(unsigned short);
// private: long const & c_indexed_list<long, 240>::get_data(unsigned short) const;
// public: c_indexed_list<long, 240>::iterator::iterator(class c_indexed_list<long, 240> *, unsigned short, unsigned short, unsigned short);
// public: void c_indexed_list<long, 240>::initialize(void);
// public: bool c_indexed_list<long, 240>::push_back(long const &);
// public: long c_indexed_list<long, 240>::pop_head(void);
// private: unsigned short c_indexed_list<long, 240>::pop(void);
// private: void c_indexed_list<long, 240>::push(struct s_il_node *);
// public: void c_indexed_list<long, 240>::clear(void);
// void g_mtp_used_global_defs::`dynamic atexit destructor'(void);
// void g_mtp_used_name_defs::`dynamic atexit destructor'(void);

unsigned long mt_profiler_get_color_from_index(long index)
{
    mangled_ppc("?mt_profiler_get_color_from_index@@YAKJ@Z");

    assert_tag_debug_untracked_jul_11_2011(68, index < k_mtp_colors_max);

    return g_mtp_profiler_colors[index];
};

float smoothstep(float edge0, float edge1, float x)
{
    mangled_ppc("?smoothstep@@YAMMMM@Z");

    if (x < edge0)
    {
        return 0.0f;
    }

    if (x >= edge1)
    {
        return 1.0f;
    }

    x = (x - edge0) / (edge1 - edge0);
    return x * x * (3.0f - 2.0f * x);
};

unsigned long mt_profiler_get_color_from_user(float user, float max_user)
{
    mangled_ppc("?mt_profiler_get_color_from_user@@YAKMM@Z");

    // local names chosen to reproduce the target stack layout
    float red_start;
    float green_lower;
    float blue_value;
    float blue_max;
    unsigned char blue_char;
    float fraction;
    float red;
    float green_amount;
    unsigned char red_bits;
    float green_end_value;
    float red_to;
    float blue_min;
    unsigned char green_u8;

    fraction = user / max_user;
    red_start = 0.0f;
    red_to = 0.3f;
    green_lower = 0.2f;
    green_end_value = 0.4f;
    blue_min = 0.3f;
    blue_max = 1.0f;
    red = smoothstep(red_start, red_to, fraction);
    green_amount = smoothstep(green_lower, green_end_value, fraction);
    blue_value = smoothstep(blue_min, blue_max, fraction);

    red -= 3.0f * green_amount;
    green_amount -= 3.0f * blue_value;

    if (red < 0.0f || red > 1.0f)
    {
        red = 0.0f;
    }
    if (green_amount < 0.0f || green_amount > 1.0f)
    {
        green_amount = 0.0f;
    }
    if (blue_value < 0.0f || blue_value > 1.0f)
    {
        blue_value = 0.0f;
    }

    red *= 255.0f;
    green_amount *= 255.0f;
    blue_value *= 255.0f;

    blue_char = static_cast<unsigned char>(blue_value);
    green_u8 = static_cast<unsigned char>(green_amount);
    red_bits = static_cast<unsigned char>(red);

    return (0xFF << 24) | (blue_char << 16) | (green_u8 << 8) | red_bits;
};

char const * mt_profiler_get_name_from_index(long index)
{
    mangled_ppc("?mt_profiler_get_name_from_index@@YAPBDJ@Z");

    assert_tag_debug_untracked_jul_11_2011(168, index < g_mtp_used_name_defs.peek());

    return g_mtp_name_defs[index];
};

unsigned short get_color_index(e_mt_color color)
{
    mangled_ppc("?get_color_index@@YAGW4e_mt_color@@@Z");

    return static_cast<unsigned short>(color);
};

unsigned short get_name_index(char const * name)
{
    mangled_ppc("?get_name_index@@YAGPBD@Z");

    for (long used_count = g_mtp_used_name_defs.peek(), index = 0; index < used_count; index++)
    {
        if (name == g_mtp_name_defs[index])
        {
            return static_cast<unsigned short>(index);
        }
    }

    long new_index = g_mtp_used_name_defs.increment() - 1;
    g_mtp_name_defs[new_index] = name;
    return static_cast<unsigned short>(new_index);
};

unsigned short get_global_index(unsigned short group_name_index, unsigned short name_index, unsigned short color_index)
{
    mangled_ppc("?get_global_index@@YAGGGG@Z");

    s_global_def global_def;
    global_def.set(group_name_index, name_index, color_index);
    for (long used_count = g_mtp_used_global_defs.peek(), index = 0; index < used_count; index++)
    {
        if (global_def.value == g_mtp_global_defs[index].value)
        {
            return static_cast<unsigned short>(index);
        }
    }

    long new_index = g_mtp_used_global_defs.increment() - 1;
    g_mtp_global_defs[new_index].set(group_name_index, name_index, color_index);
    return static_cast<unsigned short>(new_index);
};

unsigned short profiler_get_index(char const * group_name, char const * name, e_mt_color color)
{
    mangled_ppc("?profiler_get_index@@YAGPBD0W4e_mt_color@@@Z");

    unsigned short global_index;
    unsigned short name_index;
    unsigned short color_index;
    unsigned short group_name_index;

    group_name_index = get_name_index(group_name);
    name_index = get_name_index(name);
    color_index = get_color_index(color);
    global_index = get_global_index(group_name_index, name_index, color_index);
    return global_index;
};

s_mt_context_detail mt_profiler_get_context_detail(unsigned short id)
{
    mangled_ppc("?mt_profiler_get_context_detail@@YA?AUs_mt_context_detail@@G@Z");

    assert_tag_debug_untracked_jul_11_2011(255, id < g_mtp_used_global_defs);

    s_mt_context_detail detail;
    detail.color_index = g_mtp_global_defs[id].color;
    detail.name_index = g_mtp_global_defs[id].name;
    return detail;
};

void initialize_history(void)
{
    mangled_ppc("?initialize_history@@YAXXZ");

    g_alloc_list.initialize();
    g_alloc_list.push_back(0);
};

long enough_free(long size)
{
    mangled_ppc("?enough_free@@YAJJ@Z");

    long free_size;
    {
        c_indexed_list<long, k_mtp_alloc_history_count>::const_iterator oldest = g_alloc_list.begin();
        free_size = *oldest - g_cur_offset;
        if (free_size < 0)
        {
            if (g_cur_offset + size > k_profiler_backing_memory_size)
            {
                g_cur_offset = 0;
                free_size = *oldest;
            }
            else
            {
                free_size = k_profiler_backing_memory_size - g_cur_offset;
            }
        }
    }

    return free_size >= size;
};

unsigned char * allocate_frame(long size)
{
    mangled_ppc("?allocate_frame@@YAPAEJ@Z");

    size = (size + 15) & ~15;
    if (static_cast<unsigned long>(size) < k_profiler_backing_memory_size)
    {
        while (!enough_free(size) && g_alloc_list.count() > 0)
        {
            g_alloc_list.pop_head();
        }

        long offset = g_cur_offset;
        g_cur_offset += size;
        return &profiler_backing_memory[offset];
    }

    return NULL;
};

s_profiler_frame_header * get_frame(long offset)
{
    mangled_ppc("?get_frame@@YAPAUs_profiler_frame_header@@J@Z");

    return static_cast<s_profiler_frame_header *>(offset_pointer(profiler_backing_memory, offset));
};

s_profiler_frame_header * profiler_storage_request(unsigned long context_count, unsigned long thread_count)
{
    mangled_ppc("?profiler_storage_request@@YAPAUs_profiler_frame_header@@KK@Z");

    if (!g_capture_allowed)
    {
        return NULL;
    }

    unsigned long size = sizeof(s_profiler_frame_header);
    size += context_count * sizeof(s_storage_context);
    size += thread_count * sizeof(s_storage_thread);
    assert_tag_debug_untracked_jul_11_2011(412, size < k_profiler_backing_memory_size);

    s_profiler_frame_header * frame = reinterpret_cast<s_profiler_frame_header *>(allocate_frame(size));
    frame->size = size;
    frame->context_count = context_count;
    frame->thread_count = static_cast<unsigned short>(thread_count);
    return frame;
};

s_profiler_frame_header * mt_profiler_get_frame(long frame_offset)
{
    mangled_ppc("?mt_profiler_get_frame@@YAPAUs_profiler_frame_header@@J@Z");

    long count = g_alloc_list.count();
    if (count == 0)
    {
        return NULL;
    }

    frame_offset = frame_offset < 0 ? -frame_offset : frame_offset;
    frame_offset = frame_offset > count ? count : frame_offset;

    c_indexed_list<long, k_mtp_alloc_history_count>::iterator it = g_alloc_list.end();
    --it;
    while (frame_offset != 0)
    {
        --it;
        frame_offset--;
    }

    s_profiler_frame_header * frame = get_frame(*it);
    return frame;
};

void mt_profiler_toggle_capture(void)
{
    mangled_ppc("?mt_profiler_toggle_capture@@YAXXZ");

    g_capture_allowed = g_capture_allowed ? false : true;
};

void profiler_publish_frame(s_profiler_frame_header * frame)
{
    mangled_ppc("?profiler_publish_frame@@YAXPAUs_profiler_frame_header@@@Z");

    if (g_capture_allowed && frame != NULL)
    {
        long offset = pointer_distance(profiler_backing_memory, frame);
        if (g_alloc_list.full())
        {
            g_alloc_list.pop_head();
        }
        g_alloc_list.push_back(offset);
    }
};

void mt_profiler_initialize(void)
{
    mangled_ppc("?mt_profiler_initialize@@YAXXZ");

    g_capture_allowed = true;
    initialize_history();
};

void mt_profiler_dispose(void)
{
    mangled_ppc("?mt_profiler_dispose@@YAXXZ");
};

void mt_profiler_set_mode(e_mt_profiler_mode mode)
{
    mangled_ppc("?mt_profiler_set_mode@@YAXW4e_mt_profiler_mode@@@Z");

    g_mt_profiler_mode = mode;
};

e_mt_profiler_mode mt_profiler_get_mode(void)
{
    mangled_ppc("?mt_profiler_get_mode@@YA?AW4e_mt_profiler_mode@@XZ");

    return g_mt_profiler_mode;
};
