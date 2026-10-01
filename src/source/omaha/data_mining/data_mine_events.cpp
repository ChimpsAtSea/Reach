#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\data_mining\\data_mine_events.cpp"
/* ---------- headers */

#include <string.h>
#include "omaha\data_mining\data_mine_events.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\data_mining\data_mine_management.h"
#include "omaha\data_mining\data_mining.h"
#include "omaha\networking\logic\network_life_cycle.h"
#include "omaha\networking\session\network_session.h"
#include "omaha\networking\transport\transport_security.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void datamine_event_handler(enum e_event_level, char const *, char const *, char *);
// public: long s_static_string<512>::index_of(char const *) const;
// public: long s_static_string<512>::next_index_of(char const *, long) const;
// public: bool s_static_string<512>::substring(long, long, class s_static_string<512> *) const;
// public: c_static_string<512>::c_static_string<512>(char const *);
// public: void s_static_string<512>::set(char const *);

void datamine_event_handler(e_event_level event_level, char const * context, char const * format, char * arglist)
{
    mangled_ppc("?datamine_event_handler@@YAXW4e_event_level@@PBD1PAD@Z");

    assert_tag_debug_untracked_jul_11_2011(22, format);

    if (data_mine_enabled() && strncmp(format, "", 1) != 0)
    {
        c_static_string<512> event_name(format);
        c_static_string<32> categories[16];
        c_network_session * session = NULL;
        long category_count = 0;
        long previous_index = 0;
        long category_end = event_name.index_of(" ");
        if (category_end == NONE)
        {
            category_end = event_name.length();
        }

        while (category_count < 16)
        {
            long category_separator = event_name.next_index_of(":", previous_index);
            if (category_separator != NONE && category_separator < category_end)
            {
                c_static_string<512> category;
                event_name.substring(previous_index, category_separator - previous_index, &category);
                categories[category_count].set(category.get_string());
                category_count++;
                previous_index = category_separator + 1;
            }
            else
            {
                break;
            }
        }

        if (category_count == 0)
        {
            categories[category_count++].set("uncategorized");
        }

        {
            c_datamine datamine(event_level, event_name.get_string(), 0);
            for (long category_index = 0; category_index < category_count; category_index++)
            {
                datamine.additional_category(categories[category_index].get_string());
            }

            {
                __int64 squad_session_id = 0;
                long squad_session_timestamp = 0;
                __int64 target_session_id = 0;
                long target_session_timestamp = 0;
                __int64 group_session_id = 0;
                long group_session_timestamp = 0;

                if (network_life_cycle_in_squad_session(&session) && session && session->get_session_id(NULL) && session->time_exists())
                {
                    session->get_session_id(reinterpret_cast<s_transport_secure_identifier *>(&squad_session_id));
                    squad_session_timestamp = session->time_get();
                }

                if (network_life_cycle_in_target_session(&session) && session && session->get_session_id(NULL) && session->time_exists())
                {
                    session->get_session_id(reinterpret_cast<s_transport_secure_identifier *>(&target_session_id));
                    target_session_timestamp = session->time_get();
                }

                if (network_life_cycle_in_group_session(&session) && session && session->get_session_id(NULL) && session->time_exists())
                {
                    session->get_session_id(reinterpret_cast<s_transport_secure_identifier *>(&group_session_id));
                    group_session_timestamp = session->time_get();
                }

                datamine.add_int64("squad session id", squad_session_id);
                datamine.add_long("squad session timestamp", squad_session_timestamp);
                datamine.add_int64("target session id", target_session_id);
                datamine.add_long("target session timestamp", target_session_timestamp);
                datamine.add_int64("group session id", group_session_id);
                datamine.add_long("group session timestamp", group_session_timestamp);
                datamine.add_string("context", context);
                datamine.add_args(format, arglist);
            }
        }
    }
};

