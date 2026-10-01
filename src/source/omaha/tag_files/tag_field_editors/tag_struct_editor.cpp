#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_field_editors\\tag_struct_editor.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_field_editors\tag_struct_editor.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\memory\persist.h"
#include "omaha\tag_files\tag_copy_paste.h"
#include "omaha\tag_files\tag_field_scan.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "omaha\toolbox\chunk_persist_streams.h"

/* ---------- constants */

unsigned long const k_tag_struct_chunk_tag = 'tgst';

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_tag_struct_editor g_tag_struct_editor;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long volatile `public: virtual bool __cdecl c_tag_struct_editor::write(void *, void *, void const *, class c_persist_chunk_writer *, class c_tag_persist_context *)'::`27'::x_event_category_index; // "?x_event_category_index@?BL@??write@c_tag_struct_editor@@UAA_NPAX0PBXPAVc_persist_chunk_writer@@PAVc_tag_persist_context@@@Z@4JC"
// long volatile `public: virtual bool __cdecl c_tag_struct_editor::read(void *, struct s_tag_struct_definition const *, void *, void const *, struct s_persist_chunk_header const *, class c_persist_stream *, class c_tag_persist_context *)'::`25'::x_event_category_index; // "?x_event_category_index@?BJ@??read@c_tag_struct_editor@@UAA_NPAXPBUs_tag_struct_definition@@0PBXPBUs_persist_chunk_header@@PAVc_persist_stream@@PAVc_tag_persist_context@@@Z@4JC"
// class c_tag_struct_editor g_tag_struct_editor; // "?g_tag_struct_editor@@3Vc_tag_struct_editor@@A"

// class c_tag_field_editor * get_default_tag_struct_editor(void);
// public: c_tag_struct_editor::c_tag_struct_editor(void);
// public: virtual bool c_tag_struct_editor::write(void *, void *, void const *, class c_persist_chunk_writer *, class c_tag_persist_context *);
// public: virtual bool c_tag_struct_editor::create(void *, void const *, class c_tag_persist_context *);
// public: virtual void c_tag_struct_editor::dispose(void *, void const *, class c_tag_persist_context *);
// public: virtual bool c_tag_struct_editor::read(void *, struct s_tag_struct_definition const *, void *, void const *, struct s_persist_chunk_header const *, class c_persist_stream *, class c_tag_persist_context *);
// private: static void c_tag_struct_editor::initialize_tag_field_scan_state(struct tag_field_scan_state *, void *, struct s_tag_struct_definition const *, class c_tag_field_editor_manager *);

c_tag_field_editor * get_default_tag_struct_editor()
{
    mangled_ppc("?get_default_tag_struct_editor@@YAPAVc_tag_field_editor@@XZ");

    return &g_tag_struct_editor;
};

c_tag_struct_editor::c_tag_struct_editor()
{
    mangled_ppc("??0c_tag_struct_editor@@QAA@XZ");
};

bool c_tag_struct_editor::write(void * data, void * runtime_data, void const * definition, c_persist_chunk_writer * chunk_writer, c_tag_persist_context * context)
{
    mangled_ppc("?write@c_tag_struct_editor@@UAA_NPAX0PBXPAVc_persist_chunk_writer@@PAVc_tag_persist_context@@@Z");

    bool success = true;
    c_persist_stream * chunk_stream = chunk_writer->add_variable_chunk();
    {
        c_persist_chunk_writer struct_chunk_writer(chunk_stream);
        c_tag_field_editor_manager * editor_manager = context->get_editor_manager();
        tag_field_scan_state scan_state;
        initialize_tag_field_scan_state(&scan_state, runtime_data, static_cast<s_tag_struct_definition const *>(definition), editor_manager);
        while (success && tag_field_scan(&scan_state))
        {
            c_tag_field_editor * field_editor = editor_manager->tag_field_editor_get(scan_state.field->type, scan_state.field->definition);
            assert_tag_debug_untracked_jul_11_2011(42, field_editor);
            success = field_editor->write(runtime_data, scan_state.field_address, scan_state.field->definition, &struct_chunk_writer, context);
        }
    }

    if (success)
    {
        unsigned long chunk_version;
        if (chunk_stream->get_total_size(&chunk_version))
        {
            success = chunk_writer->commit_variable_chunk(k_tag_struct_chunk_tag, chunk_version, chunk_stream);
            if (!success)
            {
                event_wrapped(_event_warning, "failed to commit tag struct chunk");
            }
        }
        else
        {
            chunk_writer->abort_variable_chunk(chunk_stream);
            success = false;
        }
    }
    else
    {
        chunk_writer->abort_variable_chunk(chunk_stream);
    }

    return success;
};

bool c_tag_struct_editor::create(void * data, void const * definition, c_tag_persist_context * context)
{
    mangled_ppc("?create@c_tag_struct_editor@@UAA_NPAXPBXPAVc_tag_persist_context@@@Z");

    bool success = true;
    s_tag_struct_definition const * struct_definition = static_cast<s_tag_struct_definition const *>(definition);
    c_tag_field_editor_manager * editor_manager = context->get_editor_manager();
    tag_field_scan_state scan_state;
    initialize_tag_field_scan_state(&scan_state, data, struct_definition, editor_manager);
    while (success && tag_field_scan(&scan_state))
    {
        c_tag_field_editor * field_editor = editor_manager->tag_field_editor_get(scan_state.field->type, scan_state.field->definition);
        assert_tag_debug_untracked_jul_11_2011(92, field_editor);
        success = field_editor->create(scan_state.field_address, scan_state.field->definition, context);
    }

    return success;
};

void c_tag_struct_editor::dispose(void * data, void const * definition, c_tag_persist_context * context)
{
    mangled_ppc("?dispose@c_tag_struct_editor@@UAAXPAXPBXPAVc_tag_persist_context@@@Z");

    s_tag_struct_definition const * struct_definition = static_cast<s_tag_struct_definition const *>(definition);
    c_tag_field_editor_manager * editor_manager = context->get_editor_manager();
    tag_field_scan_state scan_state;
    initialize_tag_field_scan_state(&scan_state, data, struct_definition, editor_manager);
    while (tag_field_scan(&scan_state))
    {
        c_tag_field_editor * field_editor = editor_manager->tag_field_editor_get(scan_state.field->type, scan_state.field->definition);
        assert_tag_debug_untracked_jul_11_2011(114, field_editor);
        field_editor->dispose(scan_state.field_address, scan_state.field->definition, context);
    }
};

// $TODO nonmatching: else branch volatile-register numbering is one step behind the target (target consumes one extra scratch register somewhere after the field_editor->read call); the static x_event_category_index scope is `19' here vs `25' in the target
bool c_tag_struct_editor::read(void * data, s_tag_struct_definition const * parent_struct_definition, void * runtime_data, void const * definition, s_persist_chunk_header const * chunk_header, c_persist_stream * chunk_stream, c_tag_persist_context * context)
{
    mangled_ppc("?read@c_tag_struct_editor@@UAA_NPAXPBUs_tag_struct_definition@@0PBXPBUs_persist_chunk_header@@PAVc_persist_stream@@PAVc_tag_persist_context@@@Z");

    s_tag_struct_definition const * struct_definition = static_cast<s_tag_struct_definition const *>(definition);
    bool success;

    // the nested scope places chunk_iterator above struct_definition/success on the stack, as in the target
    {
        c_persist_chunk_iterator chunk_iterator(context->get_root_data_stream(), chunk_stream);
        success = false;
        if (chunk_header->tag == k_tag_struct_chunk_tag)
        {
            success = true;
            c_tag_field_editor_manager * editor_manager = context->get_editor_manager();
            tag_field_scan_state scan_state;
            initialize_tag_field_scan_state(&scan_state, runtime_data, struct_definition, editor_manager);
            while (success && chunk_iterator.next() && tag_field_scan(&scan_state))
            {
                c_tag_field_editor * field_editor = editor_manager->tag_field_editor_get(scan_state.field->type, scan_state.field->definition);
                assert_tag_debug_untracked_jul_11_2011(152, field_editor);
                success = field_editor->read(runtime_data, struct_definition, scan_state.field_address, scan_state.field->definition, chunk_iterator.get_chunk_header(), chunk_iterator.acquire_chunk_stream(), context);
                chunk_iterator.release_chunk_stream();
            }
        }
        else
        {
            s_static_string<5> expected_tag_string;
            s_static_string<5> chunk_tag_string;
            event_wrapped(_event_warning, "cannot read tag struct '%s', invalid chunk tag ('%s' should be '%s')", struct_definition->get_name(), chunk_tag_string.from_tag(chunk_header->tag), expected_tag_string.from_tag(k_tag_struct_chunk_tag));
        }

        return success;
    }
};

void c_tag_struct_editor::initialize_tag_field_scan_state(tag_field_scan_state * scan_state, void * data, s_tag_struct_definition const * struct_definition, c_tag_field_editor_manager * editor_manager)
{
    mangled_ppc("?initialize_tag_field_scan_state@c_tag_struct_editor@@CAXPAUtag_field_scan_state@@PAXPBUs_tag_struct_definition@@PAVc_tag_field_editor_manager@@@Z");

    tag_field_scan_state_new(scan_state, struct_definition, data);
    editor_manager->set_tag_field_scanner_fields(scan_state);
};

