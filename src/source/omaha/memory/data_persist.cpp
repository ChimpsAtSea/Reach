#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\data_persist.cpp"
/* ---------- headers */

#include "omaha\memory\data_persist.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\byte_swapping.h"
#include "omaha\memory\persist.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

/* ---------- definitions */

#define DATA_ARRAY_DATA(DATA) (*static_cast<void * const *>(offset_pointer(DATA, OFFSETOF(s_data_array, data))))

/* ---------- prototypes */

// owned by data_array.obj
void data_unprotect_all(s_data_array const * data);
void data_update_protection(s_data_array const * data);

/* ---------- globals */

template<> long const c_byte_swap_traits<s_data_array_persist_header>::g_bs_codes_internal[] = { _begin_bs_array, 1, 32, _4byte, _4byte, _4byte, _4byte, _4byte, _end_bs_array };
template<> byte_swap_definition c_byte_swap_traits<s_data_array_persist_header>::g_bs_definition_internal = { "s_data_array_persist_header", sizeof(s_data_array_persist_header), c_byte_swap_traits<s_data_array_persist_header>::g_bs_codes_internal, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 37, BYTE_SWAP_DEFINITION_SIGNATURE, false };
template<> byte_swap_definition * c_byte_swap_traits<s_data_array_persist_header>::g_bs_definition = c_byte_swap_traits<s_data_array_persist_header>::get_bs_definition();

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const *const const c_byte_swap_traits<struct s_data_array_persist_header>::g_bs_codes_internal; // "?g_bs_codes_internal@?$c_byte_swap_traits@Us_data_array_persist_header@@@@2QBJB"
// public: static struct byte_swap_definition c_byte_swap_traits<struct s_data_array_persist_header>::g_bs_definition_internal; // "?g_bs_definition_internal@?$c_byte_swap_traits@Us_data_array_persist_header@@@@2Ubyte_swap_definition@@A"
// public: static struct byte_swap_definition *c_byte_swap_traits<struct s_data_array_persist_header>::g_bs_definition; // "?g_bs_definition@?$c_byte_swap_traits@Us_data_array_persist_header@@@@2PAUbyte_swap_definition@@A"

// long data_persist_compact_size(struct s_data_array const *);
// bool data_persist(struct s_data_array const *, class c_persist_stream *, struct byte_swap_definition *, class c_datum_persister *);
// public: s_data_array_persist_header::s_data_array_persist_header(void);
// bool data_restore(struct s_data_array *, class c_persist_stream *, struct byte_swap_definition *, class c_datum_restorer *);
// bool data_restore_with_header(struct s_data_array *, struct s_data_array_persist_header const *, class c_persist_stream *, struct byte_swap_definition *, class c_datum_restorer *);
// bool data_recreate_from_stream(struct s_data_array **, class c_persist_stream *, char const *, unsigned int, long, long, class c_allocation_interface *, struct byte_swap_definition *, class c_datum_restorer *);
// public: bool c_persist_stream::write_typed<struct s_data_array_persist_header>(struct s_data_array_persist_header *, long);
// public: bool c_persist_stream::read_typed<struct s_data_array_persist_header>(struct s_data_array_persist_header *, long);
// public: static struct byte_swap_definition * c_byte_swap_traits<struct s_data_array_persist_header>::get_bs_definition(void);

long data_persist_compact_size(s_data_array const * data)
{
    mangled_ppc("?data_persist_compact_size@@YAJPBUs_data_array@@@Z");

    return data->actual_count * (data->size + sizeof(long) + sizeof(unsigned long)) + sizeof(s_data_array_persist_header) + sizeof(unsigned long);
};

bool data_persist(s_data_array const * data, c_persist_stream * persist_stream, byte_swap_definition * datum_bs_definition, c_datum_persister * datum_persister)
{
    mangled_ppc("?data_persist@@YA_NPBUs_data_array@@PAVc_persist_stream@@PAUbyte_swap_definition@@PAVc_datum_persister@@@Z");

    bool success = false;
    assert_tag_debug_untracked_jul_11_2011(67, persist_stream);

    if (persist_stream)
    {
        s_data_array_persist_header header;
        header.name.set(data->name);
        header.count = data->count;
        header.actual_count = data->actual_count;
        header.size = data->size;
        header.next_identifier = data->next_identifier;
        header.signature = data->signature;

        if (!persist_stream->write_typed(&header, 1))
        {
            goto function_exit;
        }

        for (long index = data_next_index(data, NONE), i = 1; index != NONE; index = data_next_index(data, index), i++)
        {
            if (i > data->actual_count)
            {
                goto function_exit;
            }

            void * datum = offset_pointer(DATA_ARRAY_DATA(data), DATUM_INDEX_TO_ABSOLUTE_INDEX(index) * data->size);
            if (!persist_stream->write_typed(&index, 1))
            {
                goto function_exit;
            }

            if (datum_persister)
            {
                c_basic_buffer<void const> datum_buffer(datum, data->size);
                if (!datum_persister->persist_datum(datum_buffer, persist_stream))
                {
                    goto function_exit;
                }
            }
            else if (datum_bs_definition)
            {
                if (!persist_stream->write_bs(datum, data->size, 1, datum_bs_definition))
                {
                    goto function_exit;
                }
            }
            else
            {
                dassert_tag_debug_untracked_jul_11_2011(118, false, "if you need to persist a datum array, you need to give it a byte_swap definition");
                goto function_exit;
            }

            {
                unsigned long datum_marker = '!@#$';
                if (!persist_stream->write_typed(&datum_marker, 1))
                {
                    goto function_exit;
                }
            }
        }

        {
            unsigned long end_marker = 'd@ft';
            if (!persist_stream->write_typed(&end_marker, 1))
            {
                goto function_exit;
            }
        }

        success = true;
    }

function_exit:
    return success;
};

bool data_restore(s_data_array * data, c_persist_stream * persist_stream, byte_swap_definition * datum_bs_definition, c_datum_restorer * datum_restorer)
{
    mangled_ppc("?data_restore@@YA_NPAUs_data_array@@PAVc_persist_stream@@PAUbyte_swap_definition@@PAVc_datum_restorer@@@Z");

    bool success = false;
    assert_tag_debug_untracked_jul_11_2011(258, persist_stream);

    if (persist_stream)
    {
        s_data_array_persist_header header;
        if (!persist_stream->read_typed(&header, 1))
        {
            goto function_exit;
        }

        if (!header.name.is_equal(data->name))
        {
            goto function_exit;
        }

        if (header.signature != data->signature)
        {
            goto function_exit;
        }

        if (header.size != data->size && (!datum_restorer || !datum_restorer->accept_datum_size(header.size)))
        {
            goto function_exit;
        }

        if (header.count > data->maximum_count)
        {
            goto function_exit;
        }

        if (header.actual_count > header.count)
        {
            goto function_exit;
        }

        success = data_restore_with_header(data, &header, persist_stream, datum_bs_definition, datum_restorer);
    }

function_exit:
    return success;
};

bool data_restore_with_header(s_data_array * data, s_data_array_persist_header const * header, c_persist_stream * persist_stream, byte_swap_definition * datum_bs_definition, c_datum_restorer * datum_restorer)
{
    mangled_ppc("?data_restore_with_header@@YA_NPAUs_data_array@@PBUs_data_array_persist_header@@PAVc_persist_stream@@PAUbyte_swap_definition@@PAVc_datum_restorer@@@Z");

    bool success = false;
    bool protected_data = TEST_BIT(data->flags, _data_array_protection_bit);

    if (header->signature == data->signature)
    {
        if (data->valid)
        {
            data_delete_all(data);
        }
        else
        {
            data_make_valid(data);
        }

        data_unprotect_all(data);
        false ? (data->flags |= (1u << static_cast<unsigned long>(_data_array_protection_bit))) : (data->flags &= ~(1u << static_cast<unsigned long>(_data_array_protection_bit)));

        for (long i = 0; i < header->actual_count; i++)
        {
            long index;
            if (!persist_stream->read_typed(&index, 1))
            {
                goto function_exit;
            }

            long new_index = datum_new_at_index(data, index);
            if (new_index == NONE || index != new_index)
            {
                goto function_exit;
            }

            void * datum = offset_pointer(DATA_ARRAY_DATA(data), DATUM_INDEX_TO_ABSOLUTE_INDEX(index) * data->size);
            if (datum_restorer)
            {
                c_basic_buffer<void> datum_buffer(datum, data->size);
                if (!datum_restorer->restore_datum(datum_buffer, persist_stream))
                {
                    goto function_exit;
                }
            }
            else if (datum_bs_definition)
            {
                if (!persist_stream->read_bs(datum, data->size, 1, datum_bs_definition))
                {
                    goto function_exit;
                }
            }
            else
            {
                dassert_tag_debug_untracked_jul_11_2011(208, false, "if you need to restore a datum array, you need to give it a byte_swap definition");
                goto function_exit;
            }

            {
                unsigned long datum_marker;
                if (!persist_stream->read_typed(&datum_marker, 1) || datum_marker != '!@#$')
                {
                    goto function_exit;
                }
            }
        }

        {
            unsigned long end_marker;
            if (!persist_stream->read_typed(&end_marker, 1) || end_marker != 'd@ft')
            {
                goto function_exit;
            }
        }

        event_wrapped(_event_status, "system:data_array:restore:overage: %s: %d bytes", data->name.get_string(), data->size * (data->maximum_count - data->count));

        data->next_identifier = static_cast<short>(header->next_identifier);
        data->isolated_next_identifier = ~data->next_identifier;
        data->isolated_next_identifier |= 0x8000u;
        success = true;
    }

function_exit:
    if (protected_data)
    {
        SET_BIT(data->flags, _data_array_protection_bit, true);
    }
    data_update_protection(data);

    return success;
};

//bool data_recreate_from_stream(struct s_data_array **, class c_persist_stream *, char const *, unsigned int, long, long, class c_allocation_interface *, struct byte_swap_definition *, class c_datum_restorer *)
//{
//    mangled_ppc("?data_recreate_from_stream@@YA_NPAPAUs_data_array@@PAVc_persist_stream@@PBDIJJPAVc_allocation_interface@@PAUbyte_swap_definition@@PAVc_datum_restorer@@@Z");
//};
