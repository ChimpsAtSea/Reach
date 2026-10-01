/* ---------- headers */

#include "omaha\game\challenges\challenge_definitions.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game_globals.h"
#include "omaha\scenario\scenario.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

unsigned long const CHALLENGE_GLOBALS_DEFINITION_TAG = 'chdg';

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition challenge_globals_definition_block; // "?challenge_globals_definition_block@@3Us_tag_block_definition@@A"
// struct s_tag_group_legacy_vtable legacy_challenge_globals_definition_vtable; // "?legacy_challenge_globals_definition_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group challenge_globals_definition_group; // "?challenge_globals_definition_group@@3Us_tag_group@@A"
// struct s_tag_group_stream_definition legacy_challenge_globals_definition_stream_definition; // "?legacy_challenge_globals_definition_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_challenge_globals_definition_xsync_declaration; // "?legacy_challenge_globals_definition_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_challenge_globals_definition_vtable_shim; // "?legacy_challenge_globals_definition_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// public: c_challenge_definition_iterator::c_challenge_definition_iterator(struct s_challenge_globals_definition const *);
// public: bool c_challenge_definition_iterator::next(void);
// public: struct s_challenge_definition const * c_challenge_definition_iterator::get(void);
// public: struct s_challenge_category_definition const * c_challenge_definition_iterator::get_category(void);
// struct s_challenge_definition const * challenge_definition_find(long);
// struct s_challenge_globals_definition const * challenge_globals_definition_try_and_get(void);
// struct s_challenge_category_definition const * challenge_category_definition_try_and_get(long);
// struct s_challenge_definition const * challenge_definition_try_and_get(long, long);
// bool challenge_globals_postprocess(long, bool);

c_challenge_definition_iterator::c_challenge_definition_iterator(s_challenge_globals_definition const * globals)
{
    mangled_ppc("??0c_challenge_definition_iterator@@QAA@PBUs_challenge_globals_definition@@@Z");

    m_challenge_index = NONE;
    m_category_index = NONE;
    m_globals = globals;
};

bool c_challenge_definition_iterator::next(void)
{
    mangled_ppc("?next@c_challenge_definition_iterator@@QAA_NXZ");

    bool result = false;
    if (m_globals != NULL)
    {
        bool valid = true;
        m_challenge_index += 1;
        if (m_category_index == NONE)
        {
            m_category_index = 0;
            m_challenge_index = 0;
        }

        while (!result && valid)
        {
            if (VALID_INDEX(m_category_index, m_globals->challenge_categories.count))
            {
                s_challenge_category_definition const * category = static_cast<s_challenge_category_definition const *>(tag_block_get_element_with_size(&m_globals->challenge_categories, m_category_index, sizeof(s_challenge_category_definition)));
                if (VALID_INDEX(m_challenge_index, category->challenges.count))
                {
                    result = true;
                }
                else
                {
                    m_category_index += 1;
                    m_challenge_index = 0;
                }
            }
            else
            {
                valid = false;
            }
        }
    }

    return result;
};

s_challenge_definition const * c_challenge_definition_iterator::get(void)
{
    mangled_ppc("?get@c_challenge_definition_iterator@@QAAPBUs_challenge_definition@@XZ");

    s_challenge_definition const * challenge = static_cast<s_challenge_definition const *>(tag_block_get_element_with_size(&get_category()->challenges, m_challenge_index, sizeof(s_challenge_definition)));
    return challenge;
};

s_challenge_category_definition const * c_challenge_definition_iterator::get_category(void)
{
    mangled_ppc("?get_category@c_challenge_definition_iterator@@QAAPBUs_challenge_category_definition@@XZ");

    s_challenge_category_definition const * category = static_cast<s_challenge_category_definition const *>(tag_block_get_element_with_size(&m_globals->challenge_categories, m_category_index, sizeof(s_challenge_category_definition)));
    return category;
};

s_challenge_definition const * challenge_definition_find(long challenge_name)
{
    mangled_ppc("?challenge_definition_find@@YAPBUs_challenge_definition@@J@Z");

    s_challenge_definition const * result = NULL;
    if (s_challenge_globals_definition const * globals = challenge_globals_definition_try_and_get())
    {
        c_challenge_definition_iterator iterator(globals);
        while (iterator.next())
        {
            if (iterator.get()->challenge_name == challenge_name)
            {
                result = iterator.get();
                break;
            }
        }
    }

    return result;
};

s_challenge_globals_definition const * challenge_globals_definition_try_and_get(void)
{
    mangled_ppc("?challenge_globals_definition_try_and_get@@YAPBUs_challenge_globals_definition@@XZ");

    s_challenge_globals_definition const * result = NULL;
    {
        s_game_globals * game_globals;
        {
            c_game_tag_defense_push_scope tag_defense_scope(false);
            game_globals = scenario_try_and_get_game_globals();
            if (game_globals != NULL && game_globals->challenge_globals.index != NONE)
            {
                result = static_cast<s_challenge_globals_definition const *>(tag_get(CHALLENGE_GLOBALS_DEFINITION_TAG, game_globals->challenge_globals.index));
            }

            return result;
        }
    }
};

s_challenge_category_definition const * challenge_category_definition_try_and_get(long category_index)
{
    mangled_ppc("?challenge_category_definition_try_and_get@@YAPBUs_challenge_category_definition@@J@Z");

    s_challenge_category_definition const * result = NULL;
    if (s_challenge_globals_definition const * globals = challenge_globals_definition_try_and_get())
    {
        if (VALID_INDEX(category_index, globals->challenge_categories.count))
        {
            result = static_cast<s_challenge_category_definition const *>(tag_block_get_element_with_size(&globals->challenge_categories, category_index, sizeof(s_challenge_category_definition)));
        }
        else
        {
            event_wrapped(_event_error, "challenges: challenge_category_definition_try_and_get() fed invalid category index (lsp?).");
        }
    }

    return result;
};

s_challenge_definition const * challenge_definition_try_and_get(long category_index, long challenge_index)
{
    mangled_ppc("?challenge_definition_try_and_get@@YAPBUs_challenge_definition@@JJ@Z");

    s_challenge_definition const * result = NULL;
    if (s_challenge_globals_definition const * globals = challenge_globals_definition_try_and_get())
    {
        if (VALID_INDEX(category_index, globals->challenge_categories.count))
        {
            s_challenge_category_definition const * category = static_cast<s_challenge_category_definition const *>(tag_block_get_element_with_size(&globals->challenge_categories, category_index, sizeof(s_challenge_category_definition)));
            if (VALID_INDEX(challenge_index, category->challenges.count))
            {
                result = static_cast<s_challenge_definition const *>(tag_block_get_element_with_size(&category->challenges, challenge_index, sizeof(s_challenge_definition)));
            }
            else
            {
                event_wrapped(_event_error, "challenges: challenge_definition_try_and_get() fed invalid challenge index (lsp?).");
            }
        }
        else
        {
            event_wrapped(_event_error, "challenges: challenge_definition_try_and_get() fed invalid category index (lsp?).");
        }
    }

    return result;
};

bool challenge_globals_postprocess(long tag_index, bool for_editor)
{
    mangled_ppc("?challenge_globals_postprocess@@YA_NJ_N@Z");

    s_challenge_globals_definition const * globals = static_cast<s_challenge_globals_definition const *>(tag_get(CHALLENGE_GLOBALS_DEFINITION_TAG, tag_index));
    c_challenge_definition_iterator iterator(globals);
    while (iterator.next())
    {
        s_challenge_definition const * challenge = iterator.get();
        c_challenge_definition_iterator other_iterator(globals);
        while (other_iterator.next())
        {
            s_challenge_definition const * other_challenge = other_iterator.get();
            if (challenge != other_challenge && challenge->challenge_name == other_challenge->challenge_name && challenge->challenge_name != -1 && challenge->challenge_name != 0)
            {
                event_wrapped(_event_warning, "challenges: duplicate name found - challenge named %s found in both category %s and %s - both challenges may progress simultaneously! TELL LUKE SMITH.",
                    string_id_get(challenge->challenge_name),
                    string_id_get(iterator.get_category()->category_name),
                    string_id_get(other_iterator.get_category()->category_name));
            }
        }
    }

    return true;
};
