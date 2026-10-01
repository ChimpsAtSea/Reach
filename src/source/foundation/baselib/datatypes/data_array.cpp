#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\datatypes\\data_array.cpp"
/* ---------- headers */

#include "foundation\baselib\datatypes\data_array.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\memory\allocation_interface.h"
#include "foundation\baselib\memory\platform\platform_memory_windows.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

#define DATA_ARRAY_DATA(DATA) (*static_cast<void * const *>(offset_pointer(DATA, OFFSETOF(s_data_array, data))))
#define DATA_ARRAY_IN_USE_BIT_VECTOR(DATA) (*static_cast<unsigned long * const *>(offset_pointer(DATA, OFFSETOF(s_data_array, in_use_bit_vector))))

/* ---------- prototypes */

void data_unprotect_all(s_data_array const * data);
void data_update_protection(s_data_array const * data);
short data_make_first_identifier(s_data_array const * data);
void datum_initialize(s_data_array * data, s_datum_header * header, short * next_identifier);
long data_next_absolute_index(s_data_array const * data, long absolute_index);
bool data_should_verify_data_pattern(s_data_array const * data);
void data_set_protection(s_data_array const * data, long unprotected_element_count);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_data_array * data_new(char const *, long, unsigned int, long, char const *, long, class c_allocation_interface *);
// struct s_data_array * data_new_disconnected(char const *, long, unsigned int, long, char const *, long, class c_allocation_interface *);
// void data_dispose(struct s_data_array *, char const *, long);
// unsigned int data_allocation_size(long, unsigned int, long);
// void data_initialize(struct s_data_array *, char const *, long, unsigned int, long, class c_allocation_interface *);
// void data_initialize_disconnected(struct s_data_array *, char const *, long, unsigned int, long, class c_allocation_interface *, unsigned long *);
// void data_connect(struct s_data_array *, long, void *);
// void data_disconnect(struct s_data_array *);
// void data_make_valid(struct s_data_array *);
// void data_make_invalid(struct s_data_array *);
// void data_copy(struct s_data_array const *, struct s_data_array *);
// void data_delete_all(struct s_data_array *);
// long datum_new(struct s_data_array *);
// bool datum_available_at_index(struct s_data_array const *, long);
// long datum_new_at_index(struct s_data_array *, long);
// long datum_new_at_absolute_index(struct s_data_array *, long);
// long datum_new_in_range(struct s_data_array *, long, long, enum e_datum_salt);
// void datum_clear(void *, unsigned int);
// void datum_delete(struct s_data_array *, long);
// void * datum_get(struct s_data_array *, long);
// void * datum_get_absolute(struct s_data_array *, long);
// void * datum_try_and_get(struct s_data_array *, long);
// void * datum_try_and_get_unsafe(struct s_data_array *, long);
// void * datum_try_and_get_absolute(struct s_data_array *, long);
// long datum_absolute_index_to_index(struct s_data_array const *, long);
// void data_iterator_begin(struct s_data_iterator *, struct s_data_array const *);
// void const * data_iterator_next(struct s_data_iterator *);
// long data_next_index(struct s_data_array const *, long);
// long data_last_index(struct s_data_array const *);
// long data_previous_index(struct s_data_array const *, long);
// void data_verify(struct s_data_array const *);
// bool data_is_empty(struct s_data_array const *);
// bool data_is_full(struct s_data_array const *);
// long data_get_count(struct s_data_array const *);
// long data_get_watermark(struct s_data_array const *);
// void data_unprotect_all(struct s_data_array const *);
// void data_set_new_base_address(struct s_data_array **, struct s_data_array *);
// void data_update_protection(struct s_data_array const *);
// short data_make_first_identifier(struct s_data_array const *);
// void datum_initialize(struct s_data_array *, struct s_datum_header *, short *);
// long data_next_absolute_index(struct s_data_array const *, long);
// bool data_should_verify_data_pattern(struct s_data_array const *);
// void data_set_protection(struct s_data_array const *, long);

// $TODO nonmatching
s_data_array * data_new(char const * name, long maximum_count, unsigned int size, long alignment_bits, char const * file, long line, c_allocation_interface * allocation)
{
    mangled_ppc("?data_new@@YAPAUs_data_array@@PBDJIJ0JPAVc_allocation_interface@@@Z");

    unsigned int allocation_size = data_allocation_size(maximum_count, size, alignment_bits);
    s_data_array * data = static_cast<s_data_array *>(allocation->allocate(allocation_size, file, line, "data", NULL, name));
    if (data != NULL)
    {
        data_initialize(data, name, maximum_count, size, alignment_bits, allocation);
        SET_BIT(data->flags, _data_array_protection_bit, true);
    }

    return data;
};

s_data_array * data_new_disconnected(char const * name, long maximum_count, unsigned int size, long alignment_bits, char const * file, long line, c_allocation_interface * allocation)
{
    mangled_ppc("?data_new_disconnected@@YAPAUs_data_array@@PBDJIJ0JPAVc_allocation_interface@@@Z");

    unsigned int allocation_size = BIT_VECTOR_SIZE_IN_BYTES(maximum_count) + sizeof(s_data_array);
    s_data_array * data = static_cast<s_data_array *>(allocation->allocate(allocation_size, file, line, "data", NULL, name));
    if (data != NULL)
    {
        unsigned long * in_use_bit_vector = static_cast<unsigned long *>(offset_pointer(data, sizeof(s_data_array)));
        data_initialize_disconnected(data, name, maximum_count, size, alignment_bits, allocation, in_use_bit_vector);
    }

    return data;
};

void data_dispose(s_data_array * data, char const * file, long line)
{
    mangled_ppc("?data_dispose@@YAXPAUs_data_array@@PBDJ@Z");

    c_allocation_interface * allocation = data->allocation;
    assert_tag_debug_untracked_jul_11_2011(141, allocation!=NULL);

    data_verify(data);
    data_unprotect_all(data);
    csmemset_inline(data, 0, sizeof(*data));

    if (allocation != NULL)
    {
        allocation->deallocate(data, file, line);
    }
};

unsigned int data_allocation_size(long maximum_count, unsigned int size, long alignment_bits)
{
    mangled_ppc("?data_allocation_size@@YAIJIJ@Z");

    assert_tag_debug_untracked_jul_11_2011(159, maximum_count>=0 && maximum_count<=k_uint16_max);
    assert_tag_debug_untracked_jul_11_2011(160, size>=sizeof(s_datum_header));
    assert_tag_debug_untracked_jul_11_2011(161, alignment_bits>=0);
    assert_tag_debug_untracked_jul_11_2011(162, size==align_address(size, alignment_bits));

    unsigned int allocation_size;
    long alignment_padding = alignment_bits != 0 ? (1 << alignment_bits) - 1 : 0;
    allocation_size = maximum_count * size + sizeof(s_data_array) + alignment_padding + BIT_VECTOR_SIZE_IN_BYTES(maximum_count);

    return allocation_size;
};

// $TODO nonmatching
void data_initialize(s_data_array * data, char const * name, long maximum_count, unsigned int size, long alignment_bits, c_allocation_interface * allocation)
{
    mangled_ppc("?data_initialize@@YAXPAUs_data_array@@PBDJIJPAVc_allocation_interface@@@Z");

    void * datums = align_pointer(data + 1, alignment_bits);
    unsigned long * in_use_bit_vector = static_cast<unsigned long *>(offset_pointer(datums, maximum_count * size));

    data_initialize_disconnected(data, name, maximum_count, size, alignment_bits, allocation, in_use_bit_vector);
    data->data = datums;
    data->offset_to_data = pointer_distance(data, datums);
    SET_BIT(data->flags, _data_array_disconnected_bit, false);
    SET_BIT(data->flags, _data_array_can_disconnect_bit, false);
    csmemset(DATA_ARRAY_IN_USE_BIT_VECTOR(data), 0, BIT_VECTOR_SIZE_IN_BYTES(maximum_count));
    data_update_protection(data);
};

// $TODO nonmatching
void data_initialize_disconnected(s_data_array * data, char const * name, long maximum_count, unsigned int size, long alignment_bits, c_allocation_interface * allocation, unsigned long * in_use_bit_vector)
{
    mangled_ppc("?data_initialize_disconnected@@YAXPAUs_data_array@@PBDJIJPAVc_allocation_interface@@PAK@Z");

    assert_tag_debug_untracked_jul_11_2011(201, data);
    assert_tag_debug_untracked_jul_11_2011(202, name);
    assert_tag_debug_untracked_jul_11_2011(203, maximum_count>=0 && maximum_count<=k_uint16_max);
    assert_tag_debug_untracked_jul_11_2011(204, size>0);
    assert_tag_debug_untracked_jul_11_2011(205, alignment_bits>=0 && alignment_bits<=k_int8_max);
    assert_tag_debug_untracked_jul_11_2011(206, size==align_address(size, alignment_bits));
    assert_tag_debug_untracked_jul_11_2011(207, allocation);
    assert_tag_debug_untracked_jul_11_2011(208, in_use_bit_vector);

    csmemset(data, 0, sizeof(*data));
    data->name.set(name);
    data->maximum_count = maximum_count;
    data->size = size;
    data->alignment_bits = static_cast<char>(alignment_bits);
    data->signature = 'd@t@';
    data->data = NULL;
    data->offset_to_data = 0;
    data->valid = false;
    data->in_use_bit_vector = in_use_bit_vector;
    data->offset_to_bit_vector = pointer_distance(data, in_use_bit_vector);
    data->allocation = allocation;
    SET_BIT(data->flags, _data_array_disconnected_bit, true);
    SET_BIT(data->flags, _data_array_can_disconnect_bit, true);
    SET_BIT(data->flags, _data_array_verify_data_pattern_bit, true);
};

// $TODO nonmatching
void data_connect(s_data_array * data, long maximum_count, void * datums)
{
    mangled_ppc("?data_connect@@YAXPAUs_data_array@@JPAX@Z");

    assert_tag_debug_untracked_jul_11_2011(236, TEST_BIT(data->flags, _data_array_disconnected_bit));
    assert_tag_debug_untracked_jul_11_2011(237, datums==align_pointer(datums, data->alignment_bits));
    assert_tag_debug_untracked_jul_11_2011(238, data->offset_to_bit_vector!=0);
    assert_tag_debug_untracked_jul_11_2011(239, data->in_use_bit_vector!=0);

    SET_BIT(data->flags, _data_array_disconnected_bit, false);
    data->maximum_count = maximum_count;
    data->offset_to_data = pointer_distance(data, datums);
    data->data = datums;
    data->valid = true;
    data->count = 0;
    data->actual_count = 0;
    data->first_possibly_free_absolute_index = data->maximum_count;
    data->next_identifier = data_make_first_identifier(data);
    data->isolated_next_identifier = ~data->next_identifier | 0x8000;
    data_unprotect_all(data);

    for (long index = 0; index < data->maximum_count; index++)
    {
        s_datum_header * header = static_cast<s_datum_header *>(offset_pointer(DATA_ARRAY_DATA(data), index * data->size));
        bool in_use = header->identifier != 0;

        if (data_should_verify_data_pattern(data) && !in_use)
        {
            csmemset_inline(header, 0xBA, data->size);
            header->identifier = 0;
        }

        BIT_VECTOR_SET_FLAG(DATA_ARRAY_IN_USE_BIT_VECTOR(data), index, in_use);

        if (in_use)
        {
            data->count = index + 1;
            data->actual_count++;
        }
        else if (index < data->first_possibly_free_absolute_index)
        {
            data->first_possibly_free_absolute_index = index;
        }
    }

    data_update_protection(data);
};

// $TODO nonmatching
void data_disconnect(s_data_array * data)
{
    mangled_ppc("?data_disconnect@@YAXPAUs_data_array@@@Z");

    assert_tag_debug_untracked_jul_11_2011(298, !TEST_BIT(data->flags, _data_array_disconnected_bit));
    assert_tag_debug_untracked_jul_11_2011(299, TEST_BIT(data->flags, _data_array_can_disconnect_bit));

    data_unprotect_all(data);
    SET_BIT(data->flags, _data_array_disconnected_bit, true);
    data->data = NULL;
    data->offset_to_data = 0;
    data->valid = false;
};

void data_make_valid(s_data_array * data)
{
    mangled_ppc("?data_make_valid@@YAXPAUs_data_array@@@Z");

    data->valid = true;
    data_delete_all(data);
    data_verify(data);
};

void data_make_invalid(s_data_array * data)
{
    mangled_ppc("?data_make_invalid@@YAXPAUs_data_array@@@Z");

    data_verify(data);
    data->valid = false;
};

void data_copy(s_data_array const * source, s_data_array * destination)
{
    mangled_ppc("?data_copy@@YAXPBUs_data_array@@PAU1@@Z");

    unsigned int size = source->size;

    assert_tag_debug_untracked_jul_11_2011(334, source && destination);
    assert_tag_debug_untracked_jul_11_2011(335, source->size==destination->size);
    assert_tag_debug_untracked_jul_11_2011(336, source->maximum_count==destination->maximum_count);

    for (long absolute_index = data_next_absolute_index(source, NONE); absolute_index != NONE; absolute_index = data_next_absolute_index(source, absolute_index))
    {
        s_datum_header const * source_datum = static_cast<s_datum_header const *>(offset_pointer(DATA_ARRAY_DATA(source), absolute_index * source->size));
        s_datum_header * destination_datum = static_cast<s_datum_header *>(offset_pointer(DATA_ARRAY_DATA(destination), absolute_index * destination->size));

        if (!DATUM_IS_FREE(destination_datum))
        {
            datum_delete(destination, BUILD_DATUM_INDEX(destination_datum->identifier, absolute_index));
        }

        if (!DATUM_IS_FREE(source_datum))
        {
            datum_new_at_index(destination, BUILD_DATUM_INDEX(source_datum->identifier, absolute_index));
            assert_tag_debug_untracked_jul_11_2011(353, destination_datum->identifier==source_datum->identifier);
            csmemcpy(destination_datum, source_datum, size);
        }
    }
};

void data_delete_all(s_data_array * data)
{
    mangled_ppc("?data_delete_all@@YAXPAUs_data_array@@@Z");

    assert_tag_debug_untracked_jul_11_2011(363, data->valid);
    assert_tag_debug_untracked_jul_11_2011(364, data->offset_to_bit_vector);

    data_unprotect_all(data);
    data->count = 0;
    data->actual_count = 0;
    data->first_possibly_free_absolute_index = 0;
    data->next_identifier = data_make_first_identifier(data);
    data->isolated_next_identifier = ~data->next_identifier | 0x8000;

    assert_tag_debug_untracked_jul_11_2011(375, data->next_identifier<0);
    assert_tag_debug_untracked_jul_11_2011(376, data->isolated_next_identifier<0);

    if (data_should_verify_data_pattern(data))
    {
        csmemset_inline(DATA_ARRAY_DATA(data), 0xBA, data->maximum_count * data->size);
    }

    for (long index = 0; index < data->maximum_count; index++)
    {
        static_cast<s_datum_header *>(offset_pointer(DATA_ARRAY_DATA(data), index * data->size))->identifier = 0;
    }

    csmemset(DATA_ARRAY_IN_USE_BIT_VECTOR(data), 0, BIT_VECTOR_SIZE_IN_BYTES(data->maximum_count));
    data_verify(data);
    data_update_protection(data);
};

long datum_new(s_data_array * data)
{
    mangled_ppc("?datum_new@@YAJPAUs_data_array@@@Z");

    long index = NONE;
    long absolute_index = NONE;

    assert_tag_debug_untracked_jul_11_2011(402, !TEST_BIT(data->flags, _data_array_disconnected_bit));
    assert_tag_debug_untracked_jul_11_2011(403, data->offset_to_data!=NULL);
    assert_tag_debug_untracked_jul_11_2011(404, data->data!=NULL);

    data_verify(data);
    assert_tag_debug_untracked_jul_11_2011(407, data->valid);

    {
        unsigned long * bit_vector = DATA_ARRAY_IN_USE_BIT_VECTOR(data);
        long last_index = data->count;
        for (long current_index = data->first_possibly_free_absolute_index; current_index < last_index; current_index++)
        {
            if (!BIT_VECTOR_TEST_FLAG(bit_vector, current_index))
            {
                absolute_index = current_index;
                break;
            }
        }

        if (absolute_index == NONE && last_index < data->maximum_count)
        {
            absolute_index = last_index;
        }
    }

    if (absolute_index != NONE)
    {
        s_datum_header * header = static_cast<s_datum_header *>(offset_pointer(DATA_ARRAY_DATA(data), absolute_index * data->size));

        BIT_VECTOR_SET_FLAG(DATA_ARRAY_IN_USE_BIT_VECTOR(data), absolute_index, true);
        data->actual_count++;
        data->first_possibly_free_absolute_index = absolute_index + 1;

        if (data->count <= absolute_index)
        {
            data->count = absolute_index + 1;
            data_update_protection(data);
        }

        assert_tag_debug_untracked_jul_11_2011(445, DATUM_IS_FREE(header));

        datum_initialize(data, header, &data->next_identifier);
        index = BUILD_DATUM_INDEX(header->identifier, absolute_index);
    }

    if (index != NONE)
    {
        void * result = datum_get(data, index);
    }

    return index;
};

bool datum_available_at_index(s_data_array const * data, long requested_index)
{
    mangled_ppc("?datum_available_at_index@@YA_NPBUs_data_array@@J@Z");

    long absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(requested_index);
    short identifier = DATUM_INDEX_TO_IDENTIFIER(requested_index);
    bool available = false;

    assert_tag_debug_untracked_jul_11_2011(471, identifier!=0);

    data_verify(data);
    assert_tag_debug_untracked_jul_11_2011(474, data->valid);

    if (VALID_INDEX(absolute_index, data->maximum_count))
    {
        s_datum_header * header = static_cast<s_datum_header *>(offset_pointer(DATA_ARRAY_DATA(data), absolute_index * data->size));
        available = DATUM_IS_FREE(header);
    }

    return available;
};

long datum_new_at_index(s_data_array * data, long requested_index)
{
    mangled_ppc("?datum_new_at_index@@YAJPAUs_data_array@@J@Z");

    long absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(requested_index);
    short identifier = DATUM_INDEX_TO_IDENTIFIER(requested_index);
    long index = NONE;

    assert_tag_debug_untracked_jul_11_2011(497, identifier!=0);

    data_verify(data);
    assert_tag_debug_untracked_jul_11_2011(500, data->valid);

    if (VALID_INDEX(absolute_index, data->maximum_count))
    {
        s_datum_header * header = static_cast<s_datum_header *>(offset_pointer(DATA_ARRAY_DATA(data), absolute_index * data->size));
        if (DATUM_IS_FREE(header))
        {
            BIT_VECTOR_SET_FLAG(DATA_ARRAY_IN_USE_BIT_VECTOR(data), absolute_index, true);
            data->actual_count++;

            if (absolute_index >= data->count)
            {
                data->count = absolute_index + 1;
                data_update_protection(data);
            }

            datum_initialize(data, header, &data->next_identifier);
            header->identifier = identifier;
            index = BUILD_DATUM_INDEX(header->identifier, absolute_index);
        }
    }

    assert_tag_debug_untracked_jul_11_2011(523, index==NONE || index==requested_index);

    return index;
};

long datum_new_at_absolute_index(s_data_array * data, long absolute_index)
{
    mangled_ppc("?datum_new_at_absolute_index@@YAJPAUs_data_array@@J@Z");

    long index = NONE;

    assert_tag_debug_untracked_jul_11_2011(536, DATUM_INDEX_TO_ABSOLUTE_INDEX(absolute_index)==absolute_index);
    assert_tag_debug_untracked_jul_11_2011(537, DATUM_INDEX_TO_IDENTIFIER(absolute_index)==0);

    data_verify(data);
    assert_tag_debug_untracked_jul_11_2011(540, data->valid);

    if (VALID_INDEX(absolute_index, data->maximum_count))
    {
        s_datum_header * header = static_cast<s_datum_header *>(offset_pointer(DATA_ARRAY_DATA(data), absolute_index * data->size));
        if (DATUM_IS_FREE(header))
        {
            BIT_VECTOR_SET_FLAG(DATA_ARRAY_IN_USE_BIT_VECTOR(data), absolute_index, true);
            data->actual_count++;

            if (absolute_index >= data->count)
            {
                data->count = absolute_index + 1;
                data_update_protection(data);
            }

            datum_initialize(data, header, &data->next_identifier);
            index = BUILD_DATUM_INDEX(header->identifier, absolute_index);
        }
    }

    assert_tag_debug_untracked_jul_11_2011(561, index==NONE || DATUM_INDEX_TO_ABSOLUTE_INDEX(index)==absolute_index);

    return index;
};

long datum_new_in_range(s_data_array * data, long minimum_index, long count_indices, e_datum_salt salt_type)
{
    mangled_ppc("?datum_new_in_range@@YAJPAUs_data_array@@JJW4e_datum_salt@@@Z");

    long index = NONE;
    long absolute_index = NONE;

    assert_tag_debug_untracked_jul_11_2011(576, !TEST_BIT(data->flags, _data_array_disconnected_bit));
    assert_tag_debug_untracked_jul_11_2011(577, data->offset_to_data != NULL);
    assert_tag_debug_untracked_jul_11_2011(578, VALID_INDEX(salt_type, k_datum_salt_count));

    data_verify(data);
    assert_tag_debug_untracked_jul_11_2011(581, data->valid);
    assert_tag_debug_untracked_jul_11_2011(582, minimum_index+count_indices<=data->maximum_count);

    {
        long maximum_index = MIN(minimum_index + count_indices, data->count);
        unsigned long * bit_vector = DATA_ARRAY_IN_USE_BIT_VECTOR(data);
        long current_index;
        for (current_index = minimum_index; current_index < maximum_index; current_index++)
        {
            if (!BIT_VECTOR_TEST_FLAG(bit_vector, current_index))
            {
                absolute_index = current_index;
                break;
            }
        }

        if (absolute_index == NONE && current_index < minimum_index + count_indices)
        {
            absolute_index = current_index;
        }
    }

    if (absolute_index != NONE)
    {
        s_datum_header * header = static_cast<s_datum_header *>(offset_pointer(DATA_ARRAY_DATA(data), absolute_index * data->size));

        BIT_VECTOR_SET_FLAG(DATA_ARRAY_IN_USE_BIT_VECTOR(data), absolute_index, true);
        data->actual_count++;

        if (data->count <= absolute_index)
        {
            data->count = absolute_index + 1;
            data_update_protection(data);
        }

        assert_tag_debug_untracked_jul_11_2011(619, DATUM_IS_FREE(header));

        datum_initialize(data, header, salt_type == _datum_salt_isolated ? &data->isolated_next_identifier : &data->next_identifier);
        index = BUILD_DATUM_INDEX(header->identifier, absolute_index);
    }

    if (index != NONE)
    {
        void * result = datum_get(data, index);
    }

    return index;
};

void datum_clear(void * address, unsigned int size)
{
    mangled_ppc("?datum_clear@@YAXPAXI@Z");

    csmemset_inline(offset_pointer(address, sizeof(s_datum_header)), 0, size - sizeof(s_datum_header));
};

void datum_delete(s_data_array * data, long index)
{
    mangled_ppc("?datum_delete@@YAXPAUs_data_array@@J@Z");

    s_datum_header * header = static_cast<s_datum_header *>(datum_get(data, index));
    long absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);

    if (data_should_verify_data_pattern(data))
    {
        csmemset_inline(header, 0xBA, data->size);
    }

    BIT_VECTOR_SET_FLAG(DATA_ARRAY_IN_USE_BIT_VECTOR(data), absolute_index, false);
    header->identifier = 0;

    if (absolute_index < data->first_possibly_free_absolute_index)
    {
        data->first_possibly_free_absolute_index = absolute_index;
    }

    if (absolute_index + 1 == data->count)
    {
        do
        {
            header = static_cast<s_datum_header *>(offset_pointer(header, -data->size));
            data->count--;
        }
        while (data->count > 0 && header->identifier == 0);

        data_update_protection(data);
    }

    data->actual_count--;
};

void * datum_get(s_data_array * data, long index)
{
    mangled_ppc("?datum_get@@YAPAXPAUs_data_array@@J@Z");

    long absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);
    s_datum_header * header = static_cast<s_datum_header *>(offset_pointer(DATA_ARRAY_DATA(data), absolute_index * data->size));

    assert_tag_debug_untracked_jul_11_2011(693, data);
    assert_tag_debug_untracked_jul_11_2011(694, data->valid);
    vassert_tag_debug_untracked_jul_11_2011(696, index != NONE, "tried to access %s index NONE", data->name.get_string());
    vassert_tag_debug_untracked_jul_11_2011(697, DATUM_INDEX_TO_IDENTIFIER(index) != 0, "tried to access %s using datum_get() with an absolute index #%d", data->name.get_string(), index);
    vassert_tag_debug_untracked_jul_11_2011(698, VALID_INDEX(absolute_index, data->count), "%s index #%d (0x%x) is out of range (%d)", data->name.get_string(), absolute_index, index, data->count);
    vassert_tag_debug_untracked_jul_11_2011(699, !DATUM_IS_FREE(header), "%s index #%d (0x%x) is unused", data->name.get_string(), absolute_index, index);
    vassert_tag_debug_untracked_jul_11_2011(701, header->identifier == DATUM_INDEX_TO_IDENTIFIER(index), "%s index #%d (0x%x) is changed, should be 0x%x", data->name.get_string(), absolute_index, index, BUILD_DATUM_INDEX(header->identifier, absolute_index));
    assert_tag_debug_untracked_jul_11_2011(702, data->alignment_bits==0 || header==align_pointer(header, data->alignment_bits));

    return header;
};

void * datum_get_absolute(s_data_array * data, long absolute_index)
{
    mangled_ppc("?datum_get_absolute@@YAPAXPAUs_data_array@@J@Z");

    s_datum_header * header = static_cast<s_datum_header *>(offset_pointer(DATA_ARRAY_DATA(data), absolute_index * data->size));

    assert_tag_debug_untracked_jul_11_2011(783, data);
    assert_tag_debug_untracked_jul_11_2011(784, data->valid);
    vassert_tag_debug_untracked_jul_11_2011(786, absolute_index != NONE, "tried to access %s index NONE", data->name.get_string());
    vassert_tag_debug_untracked_jul_11_2011(787, DATUM_INDEX_TO_IDENTIFIER(absolute_index) == 0, "tried to access %s using datum_get_absolute() with a non absolute index #%d", data->name.get_string(), absolute_index);
    vassert_tag_debug_untracked_jul_11_2011(788, VALID_INDEX(absolute_index, data->count), "%s absolute index #%d is out of range (%d)", data->name.get_string(), absolute_index, data->count);
    vassert_tag_debug_untracked_jul_11_2011(789, !DATUM_IS_FREE(header), "%s absolute index #%d is unused", data->name.get_string(), absolute_index);
    assert_tag_debug_untracked_jul_11_2011(790, data->alignment_bits==0 || header==align_pointer(header, data->alignment_bits));

    return header;
};

void * datum_try_and_get(s_data_array * data, long index)
{
    mangled_ppc("?datum_try_and_get@@YAPAXPAUs_data_array@@J@Z");

    void * result = NULL;

    assert_tag_debug_untracked_jul_11_2011(803, data);
    assert_tag_debug_untracked_jul_11_2011(804, data->valid);

    if (index != NONE)
    {
        long absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);
        short identifier = DATUM_INDEX_TO_IDENTIFIER(index);

        vassert_tag_debug_untracked_jul_11_2011(811, identifier != 0, "tried to access %s using datum_try_and_get() with an absolute index #%d", data->name.get_string(), index);
        vassert_tag_debug_untracked_jul_11_2011(813, VALID_INDEX(absolute_index, data->maximum_count), "tried to access %s using datum_try_and_get() with an index 0x%08X outside maximum range [0, %d)", data->name.get_string(), index, data->maximum_count);

        if (absolute_index < data->count)
        {
            s_datum_header * header = static_cast<s_datum_header *>(offset_pointer(DATA_ARRAY_DATA(data), absolute_index * data->size));
            if (!DATUM_IS_FREE(header) && header->identifier == identifier)
            {
                result = header;
            }
        }
    }

    assert_tag_debug_untracked_jul_11_2011(827, result==align_pointer(result, data->alignment_bits));

    return result;
};

void * datum_try_and_get_unsafe(s_data_array * data, long index)
{
    mangled_ppc("?datum_try_and_get_unsafe@@YAPAXPAUs_data_array@@J@Z");

    void * result = NULL;

    assert_tag_debug_untracked_jul_11_2011(842, data);
    assert_tag_debug_untracked_jul_11_2011(843, data->valid);

    if (index != NONE)
    {
        long absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index);
        short identifier = DATUM_INDEX_TO_IDENTIFIER(index);

        if (VALID_INDEX(absolute_index, data->count))
        {
            s_datum_header * header = static_cast<s_datum_header *>(offset_pointer(DATA_ARRAY_DATA(data), absolute_index * data->size));
            if (!DATUM_IS_FREE(header) && header->identifier == identifier)
            {
                result = header;
            }
        }
    }

    assert_tag_debug_untracked_jul_11_2011(862, result==align_pointer(result, data->alignment_bits));

    return result;
};

void * datum_try_and_get_absolute(s_data_array * data, long absolute_index)
{
    mangled_ppc("?datum_try_and_get_absolute@@YAPAXPAUs_data_array@@J@Z");

    void * result = NULL;

    assert_tag_debug_untracked_jul_11_2011(873, data);
    assert_tag_debug_untracked_jul_11_2011(874, data->valid);

    if (absolute_index != NONE)
    {
        vassert_tag_debug_untracked_jul_11_2011(879, DATUM_INDEX_TO_IDENTIFIER(absolute_index) == 0, "tried to access %s using datum_try_and_get_absolute() with a non absolute index #%d (0x%x)", data->name.get_string(), DATUM_INDEX_TO_ABSOLUTE_INDEX(absolute_index), absolute_index);
        vassert_tag_debug_untracked_jul_11_2011(881, VALID_INDEX(absolute_index, data->maximum_count), "tried to access %s using datum_try_and_get_absolute() with an absolute index 0x%04X outside maximum range [0, %d)", data->name.get_string(), absolute_index, data->maximum_count);

        if (VALID_INDEX(absolute_index, data->count))
        {
            s_datum_header * header = static_cast<s_datum_header *>(offset_pointer(DATA_ARRAY_DATA(data), absolute_index * data->size));
            if (!DATUM_IS_FREE(header))
            {
                result = header;
            }
        }
    }

    assert_tag_debug_untracked_jul_11_2011(894, result==align_pointer(result, data->alignment_bits));

    return result;
};

long datum_absolute_index_to_index(s_data_array const * data, long absolute_index)
{
    mangled_ppc("?datum_absolute_index_to_index@@YAJPBUs_data_array@@J@Z");

    long index = NONE;
    if (absolute_index != NONE)
    {
        s_datum_header * header = static_cast<s_datum_header *>(datum_get_absolute(const_cast<s_data_array *>(data), absolute_index));
        index = BUILD_DATUM_INDEX(header->identifier, absolute_index);
    }

    return index;
};

void data_iterator_begin(s_data_iterator * iterator, s_data_array const * data)
{
    mangled_ppc("?data_iterator_begin@@YAXPAUs_data_iterator@@PBUs_data_array@@@Z");

    data_verify(data);
    assert_tag_debug_untracked_jul_11_2011(920, data->valid);

    iterator->data = data;
    iterator->absolute_index = NONE;
    iterator->index = NONE;
    iterator->signature = reinterpret_cast<unsigned long>(data) ^ 'iter';
};

void const * data_iterator_next(s_data_iterator * iterator)
{
    mangled_ppc("?data_iterator_next@@YAPBXPAUs_data_iterator@@@Z");

    s_data_array const * data = iterator->data;

    assert_tag_debug_untracked_jul_11_2011(938, data);
    assert_tag_debug_untracked_jul_11_2011(939, data->valid);
    dassert_tag_debug_untracked_jul_11_2011(943, iterator->signature == (reinterpret_cast<unsigned long>(data) ^ 'iter'), "uninitialized iterator passed to iterator_next()");

    data_verify(data);

    long absolute_index = data_next_absolute_index(data, iterator->absolute_index + 1);
    void const * result;
    if (absolute_index != NONE)
    {
        s_datum_header const * header = static_cast<s_datum_header const *>(offset_pointer(DATA_ARRAY_DATA(data), absolute_index * data->size));
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

    assert_tag_debug_untracked_jul_11_2011(964, (result==NULL && iterator->index==NONE) || (result!=NULL && iterator->index!=NONE));

    return result;
};

long data_next_index(s_data_array const * data, long index)
{
    mangled_ppc("?data_next_index@@YAJPBUs_data_array@@J@Z");

    long absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(index + 1);
    long next_absolute_index = data_next_absolute_index(data, absolute_index);

    return datum_absolute_index_to_index(data, next_absolute_index);
};

long data_last_index(s_data_array const * data)
{
    mangled_ppc("?data_last_index@@YAJPBUs_data_array@@@Z");

    long last = NONE;

    assert_tag_debug_untracked_jul_11_2011(986, data->valid);

    long index;
    while ((index = data_next_index(data, last)) != NONE)
    {
        last = index;
    }

    return last;
};

long data_previous_index(s_data_array const * data, long index)
{
    mangled_ppc("?data_previous_index@@YAJPBUs_data_array@@J@Z");

    long previous_index = NONE;

    data_verify(data);
    assert_tag_debug_untracked_jul_11_2011(1004, data->valid);

    long absolute_index = index == NONE ? data->count - 1 : DATUM_INDEX_TO_ABSOLUTE_INDEX(index) - 1;
    if (VALID_INDEX(absolute_index, data->count))
    {
        s_datum_header const * header = static_cast<s_datum_header const *>(offset_pointer(DATA_ARRAY_DATA(data), absolute_index * data->size));
        do
        {
            if (!DATUM_IS_FREE(header))
            {
                previous_index = BUILD_DATUM_INDEX(header->identifier, absolute_index);
                break;
            }

            header = static_cast<s_datum_header const *>(offset_pointer(header, -data->size));
        }
        while (absolute_index-- >= 0);
    }

    return previous_index;
};

void data_verify(s_data_array const * data)
{
    mangled_ppc("?data_verify@@YAXPBUs_data_array@@@Z");

    assert_tag_debug_untracked_jul_11_2011(1032, data);
    vassert_tag_debug_untracked_jul_11_2011(1048,
        data->signature == 'd@t@' &&
        data->maximum_count >= 0 &&
        data->count >= 0 &&
        data->count <= data->maximum_count &&
        data->first_possibly_free_absolute_index >= 0 &&
        data->first_possibly_free_absolute_index <= data->maximum_count &&
        data->actual_count >= 0 &&
        data->actual_count <= data->count &&
        (TEST_BIT(data->flags, _data_array_disconnected_bit) || data->offset_to_data != 0) &&
        data->offset_to_bit_vector != 0 &&
        true, // a trailing compile-time-constant term (folded) produces the final beq/b pair
        "%s data array @%p is bad or not allocated", data->name.get_string(), data);
};

bool data_is_empty(s_data_array const * data)
{
    mangled_ppc("?data_is_empty@@YA_NPBUs_data_array@@@Z");

    assert_tag_debug_untracked_jul_11_2011(1056, data);
    assert_tag_debug_untracked_jul_11_2011(1057, data->valid);

    return data->count == 0;
};

bool data_is_full(s_data_array const * data)
{
    mangled_ppc("?data_is_full@@YA_NPBUs_data_array@@@Z");

    assert_tag_debug_untracked_jul_11_2011(1064, data);
    assert_tag_debug_untracked_jul_11_2011(1065, data->valid);

    return data->count == data->maximum_count;
};

long data_get_count(s_data_array const * data)
{
    mangled_ppc("?data_get_count@@YAJPBUs_data_array@@@Z");

    assert_tag_debug_untracked_jul_11_2011(1072, data);
    assert_tag_debug_untracked_jul_11_2011(1073, data->valid);

    return data->actual_count;
};

long data_get_watermark(s_data_array const * data)
{
    mangled_ppc("?data_get_watermark@@YAJPBUs_data_array@@@Z");

    assert_tag_debug_untracked_jul_11_2011(1080, data);
    assert_tag_debug_untracked_jul_11_2011(1081, data->valid);

    return data->count;
};

void data_unprotect_all(s_data_array const * data)
{
    mangled_ppc("?data_unprotect_all@@YAXPBUs_data_array@@@Z");

    data_set_protection(data, data->maximum_count);
};

void data_set_new_base_address(s_data_array ** pointer_to_set, s_data_array * new_address)
{
    mangled_ppc("?data_set_new_base_address@@YAXPAPAUs_data_array@@PAU1@@Z");

    if (new_address)
    {
        if (new_address->offset_to_data)
        {
            void * datums = offset_pointer(new_address, new_address->offset_to_data);
            if (new_address->data != datums)
            {
                new_address->data = datums;
            }
        }
        else
        {
            new_address->data = NULL;
        }

        if (new_address->offset_to_bit_vector)
        {
            unsigned long * in_use_bit_vector = static_cast<unsigned long *>(offset_pointer(new_address, new_address->offset_to_bit_vector));
            if (new_address->in_use_bit_vector != in_use_bit_vector)
            {
                new_address->in_use_bit_vector = in_use_bit_vector;
            }
        }
        else
        {
            new_address->in_use_bit_vector = NULL;
        }
    }

    *pointer_to_set = new_address;
};

void data_update_protection(s_data_array const * data)
{
    mangled_ppc("?data_update_protection@@YAXPBUs_data_array@@@Z");

    data_set_protection(data, data->count);
};

short data_make_first_identifier(s_data_array const * data)
{
    mangled_ppc("?data_make_first_identifier@@YAFPBUs_data_array@@@Z");

    short identifier = static_cast<short>(static_cast<unsigned char>(data->name[0]) | (data->name[1] << 8) | 0x8000);

    return identifier;
};

void datum_initialize(s_data_array * data, s_datum_header * header, short * next_identifier)
{
    mangled_ppc("?datum_initialize@@YAXPAUs_data_array@@PAUs_datum_header@@PAF@Z");

    assert_tag_debug_untracked_jul_11_2011(1152, !memory_is_bad_read_pointer(data, sizeof(*data)));
    assert_tag_debug_untracked_jul_11_2011(1153, !memory_is_bad_read_pointer(header, data->size));

    if (data_should_verify_data_pattern(data))
    {
        unsigned char const * bytes = reinterpret_cast<unsigned char const *>(header);
        for (unsigned int byte_index = sizeof(s_datum_header); byte_index < data->size; byte_index++)
        {
            vassert_tag_debug_untracked_jul_11_2011(1165, bytes[byte_index] == 0xBA, "%s index #%d byte#%d @%p isn't as free as it should be (something is writing to an unused datum)", data->name.get_string(), pointer_distance(DATA_ARRAY_DATA(data), header) / data->size, byte_index, &bytes[byte_index]);
        }
    }

    csmemset_inline(header, 0, data->size);

    {
        short identifier = *next_identifier;
        if (identifier == NONE)
        {
            identifier = static_cast<short>(0x8000);
        }

        header->identifier = identifier;
        assert_tag_debug_untracked_jul_11_2011(1182, header->identifier!=0 && header->identifier!=NONE);

        *next_identifier = identifier + 1;
    }
};

long data_next_absolute_index(s_data_array const * data, long absolute_index)
{
    mangled_ppc("?data_next_absolute_index@@YAJPBUs_data_array@@J@Z");

    long result = NONE;

    data_verify(data);
    assert_tag_debug_untracked_jul_11_2011(1196, data->valid);

    if (VALID_INDEX(absolute_index, data->count))
    {
        unsigned long const * bit_vector = DATA_ARRAY_IN_USE_BIT_VECTOR(data);
        void const * data_pointer = DATA_ARRAY_DATA(data);
        unsigned int datum_size = data->size;
        long index = absolute_index;
        do
        {
            prefetch_memory(data_pointer, index * datum_size);
            if (BIT_VECTOR_TEST_FLAG(bit_vector, index))
            {
                result = index;
                break;
            }
        }
        while (++index < data->count);
    }

    return result;
};

bool data_should_verify_data_pattern(s_data_array const * data)
{
    mangled_ppc("?data_should_verify_data_pattern@@YA_NPBUs_data_array@@@Z");

    bool result = TEST_BIT(data->flags, _data_array_verify_data_pattern_bit);

    return result;
};

void data_set_protection(s_data_array const * data, long unprotected_element_count)
{
    mangled_ppc("?data_set_protection@@YAXPBUs_data_array@@J@Z");
};

