#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\dialogs\\edit_text.cpp"
/* ---------- headers */

#include "omaha\dialogs\edit_text.h"
#include "omaha\cseries\cseries.h"
#include "omaha\input\input.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"

#include <string.h>

/* ---------- constants */

#define valid_edit_text(edit) ((edit) != NULL && (edit)->buffer != NULL && (edit)->maximum_length > 0 && strlen((edit)->buffer) <= static_cast<size_t>((edit)->maximum_length))

/* ---------- definitions */

/* ---------- prototypes */

static void edit_text_fix_selection(edit_text * edit);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void edit_text_new(struct edit_text *);
// void edit_text_handle_key(struct edit_text *, struct key_stroke const *);
// bool character_is_whitespace(char);
// void edit_text_selection_reset(struct edit_text *);
// unsigned char edit_text_get_selection_indices(struct edit_text *, short *, short *);
// void edit_text_fix_selection(struct edit_text *);

void edit_text_new(edit_text * edit)
{
    mangled_ppc("?edit_text_new@@YAXPAUedit_text@@@Z");

    assert_tag_debug_untracked_jul_11_2011(30, valid_edit_text(edit));
    edit_text_selection_reset(edit);
};

inline bool character_is_whitespace(char character);

void edit_text_handle_key(edit_text * edit, key_stroke const * key)
{
    mangled_ppc("?edit_text_handle_key@@YAXPAUedit_text@@PBUkey_stroke@@@Z");

    assert_tag_debug_untracked_jul_11_2011(40, valid_edit_text(edit));
    edit_text_fix_selection(edit);

    if (key->key_code == _key_backspace || key->key_code == _key_delete)
    {
        short selection_end;
        short selection_start;
        if (edit_text_get_selection_indices(edit, &selection_start, &selection_end))
        {
            memmove_guarded(&edit->buffer[selection_start], &edit->buffer[selection_end], strlen(&edit->buffer[selection_end]) + 1, edit->buffer, edit->maximum_length);
            edit->insertion_point_index = selection_start;
            edit->selection_start_index = NONE;
        }
        else if (key->key_code == _key_backspace && edit->insertion_point_index > 0)
        {
            short old_insertion_point_index = edit->insertion_point_index;
            edit->insertion_point_index -= 1;
            memmove_guarded(&edit->buffer[edit->insertion_point_index], &edit->buffer[old_insertion_point_index], strlen(&edit->buffer[old_insertion_point_index]) + 1, edit->buffer, edit->maximum_length);
        }
        else if (key->key_code == _key_delete && static_cast<size_t>(edit->insertion_point_index) < strlen(edit->buffer))
        {
            short deletion_point_index = edit->insertion_point_index;
            deletion_point_index += 1;
            memmove_guarded(&edit->buffer[edit->insertion_point_index], &edit->buffer[deletion_point_index], strlen(&edit->buffer[deletion_point_index]) + 1, edit->buffer, edit->maximum_length);
        }
    }
    else if (key->key_code == _key_left_arrow || key->key_code == _key_right_arrow)
    {
        short selection_end;
        short selection_start;
        if (!TEST_BIT(key->modifier_flags, _key_modifier_shift_bit) && edit_text_get_selection_indices(edit, &selection_start, &selection_end))
        {
            if (key->key_code == _key_left_arrow)
            {
                edit->insertion_point_index = selection_start;
                edit->selection_start_index = NONE;
            }
            else
            {
                edit->insertion_point_index = selection_end;
                edit->selection_start_index = NONE;
            }
        }
        else
        {
            if (TEST_BIT(key->modifier_flags, _key_modifier_shift_bit) && edit->selection_start_index == NONE)
            {
                edit->selection_start_index = edit->insertion_point_index;
            }

            if (key->key_code == _key_left_arrow && edit->insertion_point_index >= 0)
            {
                if (!TEST_BIT(key->modifier_flags, _key_modifier_control_bit))
                {
                    edit->insertion_point_index -= 1;
                }
                else
                {
                    do
                    {
                        edit->insertion_point_index -= 1;
                    } while (edit->insertion_point_index >= 0 && !character_is_whitespace(edit->buffer[edit->insertion_point_index]));
                }
            }
            else if (key->key_code == _key_right_arrow && static_cast<size_t>(edit->insertion_point_index) < strlen(edit->buffer))
            {
                if (!TEST_BIT(key->modifier_flags, _key_modifier_control_bit))
                {
                    edit->insertion_point_index += 1;
                }
                else
                {
                    do
                    {
                        edit->insertion_point_index += 1;
                    } while (static_cast<size_t>(edit->insertion_point_index) < strlen(edit->buffer) && !character_is_whitespace(edit->buffer[edit->insertion_point_index]));
                }
            }

            if (edit->selection_start_index == edit->insertion_point_index)
            {
                edit->selection_start_index = NONE;
            }
        }
    }
    else if (key->ascii_code != 0 && key->ascii_code != NONE)
    {
        short selection_end;
        short selection_start;
        if (edit_text_get_selection_indices(edit, &selection_start, &selection_end))
        {
            memmove_guarded(&edit->buffer[selection_start] + 1, &edit->buffer[selection_end], strlen(&edit->buffer[selection_end]) + 1, edit->buffer, edit->maximum_length);
            edit->insertion_point_index = selection_start;
            edit->selection_start_index = NONE;
            edit->buffer[edit->insertion_point_index++] = key->ascii_code;
        }
        else if (strlen(edit->buffer) < static_cast<size_t>(edit->maximum_length - 1))
        {
            memmove_guarded(&edit->buffer[edit->insertion_point_index] + 1, &edit->buffer[edit->insertion_point_index], strlen(&edit->buffer[edit->insertion_point_index]) + 1, edit->buffer, edit->maximum_length);
            edit->buffer[edit->insertion_point_index++] = key->ascii_code;
        }
    }
    else if (key->key_code == _key_home)
    {
        edit->insertion_point_index = 0;
    }
    else if (key->key_code == _key_end)
    {
        edit->insertion_point_index = static_cast<short>(strlen(edit->buffer));
    }
};

inline bool character_is_whitespace(char character)
{
    mangled_ppc("?character_is_whitespace@@YA_ND@Z");

    return character == ' ';
};

void edit_text_selection_reset(edit_text * edit)
{
    mangled_ppc("?edit_text_selection_reset@@YAXPAUedit_text@@@Z");

    assert_tag_debug_untracked_jul_11_2011(195, valid_edit_text(edit));
    edit_text_fix_selection(edit);
    edit->insertion_point_index = static_cast<short>(strlen(edit->buffer));
    edit->selection_start_index = NONE;
};

unsigned char edit_text_get_selection_indices(edit_text * edit, short * start_index, short * end_index)
{
    mangled_ppc("?edit_text_get_selection_indices@@YAEPAUedit_text@@PAF1@Z");

    unsigned char selection_valid = false;
    assert_tag_debug_untracked_jul_11_2011(210, valid_edit_text(edit));
    edit_text_fix_selection(edit);

    if (edit->selection_start_index != NONE)
    {
        *start_index = CEILING(edit->selection_start_index, edit->insertion_point_index);
        *end_index = MAX(edit->selection_start_index, edit->insertion_point_index);
        selection_valid = true;
    }

    return selection_valid;
};

static void edit_text_fix_selection(edit_text * edit)
{
    mangled_ppc("?edit_text_fix_selection@@YAXPAUedit_text@@@Z");

    short length = static_cast<short>(strlen(edit->buffer));
    edit->insertion_point_index = PIN(edit->insertion_point_index, 0, length);
    edit->selection_start_index = PIN(edit->selection_start_index, NONE, length);
    if (edit->insertion_point_index == edit->selection_start_index)
    {
        edit->selection_start_index = NONE;
    }
    edit->selection_start_index != NONE;
};
