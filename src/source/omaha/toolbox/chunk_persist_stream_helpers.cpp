#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\toolbox\\chunk_persist_stream_helpers.cpp"
/* ---------- headers */

#include "omaha\toolbox\chunk_persist_stream_helpers.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool persist_chunk_with_archiver(class c_persist_archiver const *, class c_typed_pointer_holder &, class c_persist_chunk_writer *);
// bool persist_chunk_with_archiver_explicit(class c_persist_archiver const *, class c_typed_pointer_holder &, class c_persist_stream *);
// bool restore_chunk_with_archiver(class c_persist_archiver const *, class c_typed_pointer_holder &, class c_persist_chunk_iterator *);
// bool restore_chunk_with_archiver_explicit(class c_persist_archiver const *, class c_typed_pointer_holder &, struct s_persist_chunk_header const *, class c_persist_stream *);
// bool save_or_restore_with_archiver(class c_persist_archiver const *, class c_typed_pointer_holder &, class c_persist_stream *, enum e_chunk_archive_action);

bool persist_chunk_with_archiver(c_persist_archiver const * archiver, c_typed_pointer_holder & pointer_holder, c_persist_chunk_writer * chunk_writer)
{
    mangled_ppc("?persist_chunk_with_archiver@@YA_NPBVc_persist_archiver@@AAVc_typed_pointer_holder@@PAVc_persist_chunk_writer@@@Z");

    bool success = false;
    c_persist_stream * chunk_stream = chunk_writer->add_variable_chunk();
    if (chunk_stream)
    {
        bool persisted = persist_chunk_with_archiver_explicit(archiver, pointer_holder, chunk_stream);
        if (persisted)
        {
            success = chunk_writer->commit_variable_chunk(archiver->get_chunk_tag(), archiver->get_chunk_version(), chunk_stream);
        }
        else
        {
            chunk_writer->abort_variable_chunk(chunk_stream);
        }
    }
    return success;
};

// $TODO nonmatching (stack slots only: target has success@0x50 below event_context@0x60)
bool persist_chunk_with_archiver_explicit(c_persist_archiver const * archiver, c_typed_pointer_holder & pointer_holder, c_persist_stream * persist_stream)
{
    mangled_ppc("?persist_chunk_with_archiver_explicit@@YA_NPBVc_persist_archiver@@AAVc_typed_pointer_holder@@PAVc_persist_stream@@@Z");

    bool success;
    c_event_context event_context("", 0, "%s", archiver->get_description());

    success = archiver->persist(pointer_holder, persist_stream);
    if (!success)
    {
        event_wrapped(_event_warning, "archiver '%s' failed in ::persist", archiver->get_description());
    }
    return success;
};

bool restore_chunk_with_archiver(c_persist_archiver const * archiver, c_typed_pointer_holder & pointer_holder, c_persist_chunk_iterator * chunk_iterator)
{
    mangled_ppc("?restore_chunk_with_archiver@@YA_NPBVc_persist_archiver@@AAVc_typed_pointer_holder@@PAVc_persist_chunk_iterator@@@Z");

    bool success = false;
    s_persist_chunk_header const * chunk_header = chunk_iterator->get_chunk_header();
    c_persist_stream * chunk_stream = chunk_iterator->acquire_chunk_stream();
    success = restore_chunk_with_archiver_explicit(archiver, pointer_holder, chunk_header, chunk_stream);
    chunk_iterator->release_chunk_stream();
    return success;
};

// $TODO nonmatching (stack slots only: target has success@0x50 below event_context@0x60)
bool restore_chunk_with_archiver_explicit(c_persist_archiver const * archiver, c_typed_pointer_holder & pointer_holder, s_persist_chunk_header const * chunk_header, c_persist_stream * persist_stream)
{
    mangled_ppc("?restore_chunk_with_archiver_explicit@@YA_NPBVc_persist_archiver@@AAVc_typed_pointer_holder@@PBUs_persist_chunk_header@@PAVc_persist_stream@@@Z");

    c_event_context event_context("", 0, "%s", archiver->get_description());

    bool success = false;
    if (archiver->can_handle_chunk(chunk_header->tag, chunk_header->version))
    {
        if (archiver->restore(chunk_header, pointer_holder, persist_stream))
        {
            success = true;
        }
        else
        {
            s_static_string<5> tag_string;
            event_wrapped(_event_warning, "archiver '%s' failed reading chunk (%s, %d)", archiver->get_description(), tag_string.from_tag(chunk_header->tag), chunk_header->version);
        }
    }
    else
    {
        s_static_string<5> tag_string;
        event_wrapped(_event_warning, "archiver '%s' cannot handle chunk (%s, %d)", archiver->get_description(), tag_string.from_tag(chunk_header->tag), chunk_header->version);
    }
    return success;
};

bool save_or_restore_with_archiver(c_persist_archiver const * archiver, c_typed_pointer_holder & pointer_holder, c_persist_stream * persist_stream, e_chunk_archive_action action)
{
    mangled_ppc("?save_or_restore_with_archiver@@YA_NPBVc_persist_archiver@@AAVc_typed_pointer_holder@@PAVc_persist_stream@@W4e_chunk_archive_action@@@Z");

    bool success = false;
    switch (action)
    {
    case _chunk_archive_action_save:
    {
        c_persist_chunk_writer chunk_writer(persist_stream);
        success = persist_chunk_with_archiver(archiver, pointer_holder, &chunk_writer);
    }
    break;
    case _chunk_archive_action_load:
    {
        c_persist_stream * ancestor_stream = persist_stream->get_ancestor_stream();
        c_persist_chunk_iterator chunk_iterator(ancestor_stream, persist_stream);
        if (chunk_iterator.next())
        {
            success = restore_chunk_with_archiver(archiver, pointer_holder, &chunk_iterator);
        }
    }
    break;
    default:
        dassert_tag_debug_untracked_jul_11_2011(133, false, "unreachable");
        break;
    }
    return success;
};

