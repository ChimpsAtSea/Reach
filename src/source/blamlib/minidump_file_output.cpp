/* ---------- headers */

#include "blamlib\minidump_file_output.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"

#include <string.h>
#include <xtl.h>

/* ---------- constants */

unsigned long const k_minidump_secure_header_signature = 0x6D647363; // 'mdsc'

/* ---------- definitions */

#define SWAP_BYTES_32(value) (((value) >> 24) | (((value) >> 8) & 0x0000FF00) | (((value) << 8) & 0x00FF0000) | ((value) << 24))

/* ---------- prototypes */

/* ---------- globals */

s_minidump_secure_stream_directory g_secure_stream_directory_memory[k_minidump_secure_stream_directory_count];

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_minidump_secure_stream_directory *g_secure_stream_directory_memory; // "?g_secure_stream_directory_memory@@3PAUs_minidump_secure_stream_directory@@A"

// public: c_minidump_file_output_secure::c_minidump_file_output_secure(void);
// public: c_minidump_file_output_interface::c_minidump_file_output_interface(void);
// public: virtual void c_minidump_file_output_secure::open(char const *);
// public: virtual bool c_minidump_file_output_secure::close(void);
// public: virtual bool c_minidump_file_output_secure::is_valid(void);
// public: virtual bool c_minidump_file_output_secure::write(void const *, long);
// public: virtual bool c_minidump_file_output_secure::seek(long);
// public: virtual long c_minidump_file_output_secure::tell(void);
// private: bool c_minidump_file_output_secure::write_header_and_directory_entries(bool);
// RtlSecureZeroMemory;
// private: bool c_minidump_file_output_secure::begin_current_stream(void);
// private: bool c_minidump_file_output_secure::end_current_stream(void);

c_minidump_file_output_secure::c_minidump_file_output_secure(void) :
    m_valid(false),
    m_current_stream_index(0),
    m_position(0)
{
    mangled_ppc("??0c_minidump_file_output_secure@@QAA@XZ");
};

void c_minidump_file_output_secure::open(char const * file_name)
{
    mangled_ppc("?open@c_minidump_file_output_secure@@UAAXPBD@Z");

    unsigned long error;
    bool success = false;
    error = 0;

    file_reference_create_from_path(&m_file, file_name, false);
    if (file_create(&m_file) && file_open(&m_file, FLAG(_permission_read_bit) | FLAG(_permission_write_bit), &error))
    {
        m_aligned_file_writer.initialize(&m_file);
        if (write_header_and_directory_entries(true))
        {
            m_secure_writer_helper.initialize(&m_aligned_file_writer);
            m_current_stream_index = 0;
            if (begin_current_stream())
            {
                success = true;
            }
        }
    }

    if (success)
    {
        m_valid = true;
    }
    else
    {
        close();
    }
};

bool c_minidump_file_output_secure::close(void)
{
    mangled_ppc("?close@c_minidump_file_output_secure@@UAA_NXZ");

    bool success = true;
    s_file_handle file_handle;

    file_reference_get_file_handle(&m_file, &file_handle);
    if (file_handle_is_valid(file_handle))
    {
        if (end_current_stream())
        {
            success = m_aligned_file_writer.flush();
            success = success && write_header_and_directory_entries(false);
        }
        m_secure_writer_helper.clear();
        file_close(&m_file);
    }
    m_valid = false;

    return success;
};

bool c_minidump_file_output_secure::is_valid(void)
{
    mangled_ppc("?is_valid@c_minidump_file_output_secure@@UAA_NXZ");

    return m_valid;
};

bool c_minidump_file_output_secure::write(void const * data, long size)
{
    mangled_ppc("?write@c_minidump_file_output_secure@@UAA_NPBXJ@Z");

    bool success = false;

    if (m_secure_writer_helper.write_to_stream(data, size))
    {
        m_position += size;
        success = true;
    }

    if (!success)
    {
        close();
    }

    return success;
};

bool c_minidump_file_output_secure::seek(long offset)
{
    mangled_ppc("?seek@c_minidump_file_output_secure@@UAA_NJ@Z");

    bool success = false;

    m_position = offset;
    if (end_current_stream())
    {
        m_current_stream_index++;
        if (begin_current_stream())
        {
            success = true;
        }
    }

    if (!success)
    {
        close();
    }

    return success;
};

long c_minidump_file_output_secure::tell(void)
{
    mangled_ppc("?tell@c_minidump_file_output_secure@@UAAJXZ");

    return m_position;
};

// $TODO nonmatching: SET_BIT on header->flags materializes each |=/&= result in a temp in the target
bool c_minidump_file_output_secure::write_header_and_directory_entries(bool initial_write)
{
    mangled_ppc("?write_header_and_directory_entries@c_minidump_file_output_secure@@AAA_N_N@Z");

    bool success = false;

    if (initial_write)
    {
        s_minidump_secure_header empty_header;
        memset(&empty_header, 0, sizeof(empty_header));

        success = m_aligned_file_writer.write(reinterpret_cast<char const *>(&empty_header), sizeof(empty_header));
        success = success && m_aligned_file_writer.write(reinterpret_cast<char const *>(g_secure_stream_directory_memory), sizeof(g_secure_stream_directory_memory));
    }
    else
    {
        s_minidump_secure_header * header = NULL;
        s_minidump_secure_stream_directory * directory = NULL;
        char buffer[0x1000] = { 0 };

        success = file_set_position(&m_file, 0, false);
        success = success && file_read(&m_file, sizeof(buffer), false, buffer);

        header = reinterpret_cast<s_minidump_secure_header *>(buffer);
        header->signature = k_minidump_secure_header_signature;
        SET_BIT(header->flags, _minidump_secure_header_compressed_bit, true);
        SET_BIT(header->flags, _minidump_secure_header_encrypted_bit, true);
        header->stream_count = m_current_stream_index + 1;
        m_secure_writer_helper.get_encrypted_session_key(header->encrypted_session_key);

        header->flags = SWAP_BYTES_32(header->flags);
        header->signature = SWAP_BYTES_32(header->signature);
        header->stream_count = SWAP_BYTES_32(header->stream_count);

        directory = static_cast<s_minidump_secure_stream_directory *>(offset_pointer(buffer, sizeof(s_minidump_secure_header)));
        for (unsigned long stream_index = 0; stream_index < k_minidump_secure_stream_directory_count; stream_index++)
        {
            directory[stream_index].file_offset = SWAP_BYTES_32(g_secure_stream_directory_memory[stream_index].file_offset);
            directory[stream_index].stream_offset = SWAP_BYTES_32(g_secure_stream_directory_memory[stream_index].stream_offset);
            directory[stream_index].flags = SWAP_BYTES_32(g_secure_stream_directory_memory[stream_index].flags);
            directory[stream_index].encrypted_bytes = SWAP_BYTES_32(g_secure_stream_directory_memory[stream_index].encrypted_bytes);
            directory[stream_index].uncompressed_bytes = SWAP_BYTES_32(g_secure_stream_directory_memory[stream_index].uncompressed_bytes);
            directory[stream_index].compressed_bytes = SWAP_BYTES_32(g_secure_stream_directory_memory[stream_index].compressed_bytes);
        }

        success = success && file_set_position(&m_file, 0, false);
        success = success && file_write(&m_file, sizeof(buffer), buffer);

        RtlSecureZeroMemory(header->encrypted_session_key, sizeof(header->encrypted_session_key));
    }

    return success;
};

bool c_minidump_file_output_secure::begin_current_stream(void)
{
    mangled_ppc("?begin_current_stream@c_minidump_file_output_secure@@AAA_NXZ");

    bool success = false;

    if (m_current_stream_index < k_minidump_secure_stream_directory_count)
    {
        s_minidump_secure_stream_directory * stream = &g_secure_stream_directory_memory[m_current_stream_index];
        stream->flags = 0;
        stream->file_offset = m_aligned_file_writer.get_position();
        stream->stream_offset = tell();
        if (m_secure_writer_helper.begin_stream())
        {
            success = true;
        }
    }

    return success;
};

bool c_minidump_file_output_secure::end_current_stream(void)
{
    mangled_ppc("?end_current_stream@c_minidump_file_output_secure@@AAA_NXZ");

    bool success = false;

    {
        s_minidump_secure_stream_directory * stream = &g_secure_stream_directory_memory[m_current_stream_index];
        if (m_secure_writer_helper.end_stream(&stream->compressed_bytes, &stream->encrypted_bytes, &stream->uncompressed_bytes))
        {
            success = true;
        }
    }

    return success;
};
