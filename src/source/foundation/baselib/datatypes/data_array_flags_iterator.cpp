#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\datatypes\\data_array_flags_iterator.cpp"
/* ---------- headers */

#include "foundation\baselib\datatypes\data_array_flags_iterator.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

typedef unsigned short uint16;

#define DATA_ARRAY_DATA(DATA) (*static_cast<void * const *>(offset_pointer(DATA, OFFSETOF(s_data_array, data))))
#define DATA_ARRAY_IN_USE_BIT_VECTOR(DATA) (*static_cast<unsigned long * const *>(offset_pointer(DATA, OFFSETOF(s_data_array, in_use_bit_vector))))

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void * data_iterator_next_with_word_flags(struct s_data_iterator *, long, unsigned short, unsigned short);
// long data_next_absolute_index_with_word_flags(struct s_data_array const *, long, long, unsigned short, unsigned short);

void * data_iterator_next_with_word_flags(s_data_iterator * iterator, long flag_offset, unsigned short flag_mask, unsigned short flag_value)
{
    mangled_ppc("?data_iterator_next_with_word_flags@@YAPAXPAUs_data_iterator@@JGG@Z");

    s_data_array const * data = iterator->data;

    dassert_tag_debug_untracked_jul_11_2011(34, iterator->signature == (reinterpret_cast<unsigned long>(data) ^ 'iter'), "uninitialized iterator passed to iterator_next()");

    data_verify(data);
    assert_tag_debug_untracked_jul_11_2011(38, data->valid);
    assert_tag_debug_untracked_jul_11_2011(39, data->size>=0);
    assert_tag_debug_untracked_jul_11_2011(41, flag_offset>=sizeof(s_datum_header) && flag_offset+sizeof(uint16)<=data->size);
    assert_tag_debug_untracked_jul_11_2011(42, flag_mask!=0);
    assert_tag_debug_untracked_jul_11_2011(43, (flag_value&~flag_mask)==0);

    long absolute_index = data_next_absolute_index_with_word_flags(data, iterator->absolute_index + 1, flag_offset, flag_mask, flag_value);
    void * result;
    if (absolute_index != NONE)
    {
        s_datum_header * header = static_cast<s_datum_header *>(offset_pointer(DATA_ARRAY_DATA(data), absolute_index * data->size));
        assert_tag_debug_untracked_jul_11_2011(52, (*reinterpret_cast<uint16 *>(offset_pointer(header, flag_offset))&flag_mask)==flag_value);
        iterator->absolute_index = absolute_index;
        iterator->index = BUILD_DATUM_INDEX(header->identifier, absolute_index);
        result = header;
    }
    else
    {
        iterator->absolute_index = iterator->data->maximum_count;
        iterator->index = NONE;
        result = NULL;
    }

    assert_tag_debug_untracked_jul_11_2011(65, (result==NULL && iterator->index==NONE) || (result!=NULL && iterator->index!=NONE));

    return result;
};

long data_next_absolute_index_with_word_flags(s_data_array const * data, long absolute_index, long flag_offset, unsigned short flag_mask, unsigned short flag_value)
{
    mangled_ppc("?data_next_absolute_index_with_word_flags@@YAJPBUs_data_array@@JJGG@Z");

    long result = NONE;

    data_verify(data);
    assert_tag_debug_untracked_jul_11_2011(82, data->valid);

    if (VALID_INDEX(absolute_index, data->count))
    {
        unsigned long const * bit_vector = DATA_ARRAY_IN_USE_BIT_VECTOR(data);
        void const * data_pointer = DATA_ARRAY_DATA(data);
        unsigned int datum_size = data->size;
        uint16 const * flags = static_cast<uint16 const *>(offset_pointer(data_pointer, absolute_index * datum_size + flag_offset));
        long index = absolute_index;
        do
        {
            prefetch_memory(flags, 0);
            if (BIT_VECTOR_TEST_FLAG(bit_vector, index) && (*flags & flag_mask) == flag_value)
            {
                result = index;
                break;
            }
            index++;
            flags = static_cast<uint16 const *>(offset_pointer(flags, datum_size));
        }
        while (index < data->count);
    }

    return result;
};

