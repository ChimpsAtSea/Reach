#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\blamlib\\levels_internal.cpp"
/* ---------- headers */

#include "blamlib\levels_internal.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\networking\tools\network_blf.h"
#include "omaha\tag_files\files.h"

/* ---------- constants */

enum
{
    k_campaign_info_file_maximum_size = 0x18AC,
    k_level_info_file_maximum_size = 0xD22C,

    k_blf_chunk_campaign_type = 'cmpn',
    k_blf_chunk_campaign_version_major = 1,
    k_blf_chunk_scenario_type = 'levl',
    k_blf_chunk_scenario_version_major = 7,
    k_blf_chunk_end_of_file_type = '_eof',
    k_blf_chunk_end_of_file_version_major = 1,
};

// sizeof(s_blf_chunk_end_of_file_with_rsa)
unsigned long const k_blf_chunk_end_of_file_with_rsa_size = 0x111;

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void levels_find_campaign_chunk(struct s_file_reference *, char *const, struct s_blf_chunk_campaign const **, bool *);
// void levels_find_scenario_chunk(struct s_file_reference *, char *const, struct s_blf_chunk_scenario const **, bool *);

void levels_find_campaign_chunk(s_file_reference * file, char * const buffer, s_blf_chunk_campaign const ** out_campaign_chunk, bool * out_must_byte_swap)
{
    mangled_ppc("?levels_find_campaign_chunk@@YAXPAUs_file_reference@@QADPAPBUs_blf_chunk_campaign@@PA_N@Z");

    char file_name[256];
    bool valid = false;
    unsigned long unused_error_code;

    *out_campaign_chunk = NULL;
    *out_must_byte_swap = false;

    if (file_open(file, FLAG(_permission_read_bit), &unused_error_code))
    {
        unsigned long file_size;
        if (file_get_size(file, &file_size))
        {
            if (file_size <= k_campaign_info_file_maximum_size)
            {
                if (file_read(file, file_size, false, buffer))
                {
                    long chunk_size;
                    bool must_byte_swap;
                    char const * found_chunk;
                    s_blf_chunk_campaign const * campaign_chunk = NULL;
                    bool eof_found;
                    found_chunk = NULL;
                    chunk_size = 0;
                    eof_found = false;

                    if (network_blf_verify_start_of_file(buffer, file_size, &must_byte_swap, &chunk_size))
                    {
                        if (network_blf_find_chunk(buffer, file_size, must_byte_swap, k_blf_chunk_campaign_type, k_blf_chunk_campaign_version_major, &chunk_size, &found_chunk, NULL, NULL, &eof_found))
                        {
                            campaign_chunk = found_chunk ? reinterpret_cast<s_blf_chunk_campaign const *>(found_chunk - sizeof(s_blf_header)) : NULL;

                            if (campaign_chunk && network_blf_find_chunk(buffer, file_size, must_byte_swap, k_blf_chunk_end_of_file_type, k_blf_chunk_end_of_file_version_major, &chunk_size, &found_chunk, NULL, NULL, &eof_found))
                            {
                                if (found_chunk && chunk_size == k_blf_chunk_end_of_file_with_rsa_size && eof_found && network_blf_verify_end_of_file(buffer, file_size, must_byte_swap, found_chunk - sizeof(s_blf_header), _blf_file_authentication_type_rsa))
                                {
                                    valid = true;
                                }
                                else
                                {
                                    event_wrapped(_event_warning, "levels: failed to verify blf end of file chunk");
                                }
                            }
                            else
                            {
                                event_wrapped(_event_warning, "levels: failed to find blf end of file chunk");
                            }
                        }
                        else
                        {
                            event_wrapped(_event_warning, "levels: failed to find blf campaign chunk");
                        }
                    }
                    else
                    {
                        event_wrapped(_event_warning, "levels: failed to verify blf start of file for campaign info file");
                    }

                    if (valid)
                    {
                        *out_campaign_chunk = campaign_chunk;
                        *out_must_byte_swap = must_byte_swap;
                    }
                }
                else
                {
                    event_wrapped(_event_warning, "levels: failed to read campaign info file");
                }
            }
            else
            {
                event_wrapped(_event_warning, "levels: unexpected file size for campaign info file");
            }
        }
        else
        {
            event_wrapped(_event_warning, "levels: failed to get file size of campaign info file");
        }

        file_close(file);
    }
    else
    {
        event_wrapped(_event_warning, "levels: failed to open campaign info file");
    }

    if (!valid)
    {
        event_wrapped(_event_warning, "levels: failed to add campaign file '%s'", file_reference_get_name(file, _name_full_mask, file_name, NUMBEROF(file_name)));
    }
};

void levels_find_scenario_chunk(s_file_reference * file, char * const buffer, s_blf_chunk_scenario const ** out_scenario_chunk, bool * out_must_byte_swap)
{
    mangled_ppc("?levels_find_scenario_chunk@@YAXPAUs_file_reference@@QADPAPBUs_blf_chunk_scenario@@PA_N@Z");

    char file_name[256];
    bool valid = false;
    unsigned long unused_error_code;

    *out_scenario_chunk = NULL;
    *out_must_byte_swap = false;

    if (file_open(file, FLAG(_permission_read_bit), &unused_error_code))
    {
        unsigned long file_size;
        if (file_get_size(file, &file_size))
        {
            if (file_size <= k_level_info_file_maximum_size)
            {
                if (file_read(file, file_size, false, buffer))
                {
                    long chunk_size;
                    s_blf_chunk_scenario const * scenario_chunk = NULL;
                    bool must_byte_swap;
                    char const * found_chunk;
                    bool eof_found;
                    found_chunk = NULL;
                    chunk_size = 0;
                    eof_found = false;

                    if (network_blf_verify_start_of_file(buffer, file_size, &must_byte_swap, &chunk_size))
                    {
                        if (network_blf_find_chunk(buffer, file_size, must_byte_swap, k_blf_chunk_scenario_type, k_blf_chunk_scenario_version_major, &chunk_size, &found_chunk, NULL, NULL, &eof_found))
                        {
                            scenario_chunk = found_chunk ? reinterpret_cast<s_blf_chunk_scenario const *>(found_chunk - sizeof(s_blf_header)) : NULL;

                            if (scenario_chunk && network_blf_find_chunk(buffer, file_size, must_byte_swap, k_blf_chunk_end_of_file_type, k_blf_chunk_end_of_file_version_major, &chunk_size, &found_chunk, NULL, NULL, &eof_found))
                            {
                                if (found_chunk && chunk_size == k_blf_chunk_end_of_file_with_rsa_size && eof_found)
                                {
                                    if (network_blf_verify_end_of_file(buffer, file_size, must_byte_swap, found_chunk - sizeof(s_blf_header), _blf_file_authentication_type_rsa))
                                    {
                                        valid = true;
                                    }
                                    else
                                    {
                                        event_wrapped(_event_warning, "levels: failed to verify blf end of file chunk");
                                    }
                                }
                                else
                                {
                                    event_wrapped(_event_warning, "levels: failed to find expected blf end of file chunk");
                                }
                            }
                            else
                            {
                                event_wrapped(_event_warning, "levels: failed to find blf end of file chunk");
                            }
                        }
                        else
                        {
                            event_wrapped(_event_warning, "levels: failed to find blf scenario chunk");
                        }
                    }
                    else
                    {
                        event_wrapped(_event_warning, "levels: failed to verify blf start of file");
                    }

                    if (valid)
                    {
                        *out_scenario_chunk = scenario_chunk;
                        *out_must_byte_swap = must_byte_swap;
                    }
                }
                else
                {
                    event_wrapped(_event_warning, "levels: failed to read level info file");
                }
            }
            else
            {
                event_wrapped(_event_warning, "levels: level info file had unexpected size");
            }
        }
        else
        {
            event_wrapped(_event_warning, "levels: failed to get file size for level info file");
        }

        file_close(file);
    }
    else
    {
        event_wrapped(_event_warning, "levels: failed to open level info file");
    }

    if (!valid)
    {
        event_wrapped(_event_warning, "levels: failed to add level file '%s'", file_reference_get_name(file, _name_full_mask, file_name, NUMBEROF(file_name)));
    }
};

