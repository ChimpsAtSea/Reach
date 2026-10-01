/* ---------- headers */

#include "blamlib\tag_files_sync_source_default.h"
#include "omaha\tag_files\tag_files.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: virtual void c_default_tag_file_sync_source::idle(void);
// public: virtual bool c_default_tag_file_sync_source::any_changes(void);
// public: virtual void c_default_tag_file_sync_source::begin(void);
// public: virtual class c_tag_file_difference_iterator * c_default_tag_file_sync_source::get_difference_iterator(void);
// public: virtual void c_default_tag_file_sync_source::dispose_difference_iterator(class c_tag_file_difference_iterator *);
// public: virtual void c_default_tag_file_sync_source::end(void);
// public: virtual char const * c_default_tag_file_sync_source::get_name(void);

void c_default_tag_file_sync_source::idle(void)
{
    mangled_ppc("?idle@c_default_tag_file_sync_source@@UAAXXZ");

    tag_files_sync_idle();
};

bool c_default_tag_file_sync_source::any_changes(void)
{
    mangled_ppc("?any_changes@c_default_tag_file_sync_source@@UAA_NXZ");

    return tag_files_sync_tags_changed();
};

void c_default_tag_file_sync_source::begin(void)
{
    mangled_ppc("?begin@c_default_tag_file_sync_source@@UAAXXZ");

    tag_files_sync_reload_begin();
};

c_tag_file_difference_iterator * c_default_tag_file_sync_source::get_difference_iterator(void)
{
    mangled_ppc("?get_difference_iterator@c_default_tag_file_sync_source@@UAAPAVc_tag_file_difference_iterator@@XZ");

    return tag_files_sync_get_difference_iterator();
};

void c_default_tag_file_sync_source::dispose_difference_iterator(c_tag_file_difference_iterator * iterator)
{
    mangled_ppc("?dispose_difference_iterator@c_default_tag_file_sync_source@@UAAXPAVc_tag_file_difference_iterator@@@Z");

    tag_files_sync_dispose_difference_iterator(iterator);
};

void c_default_tag_file_sync_source::end(void)
{
    mangled_ppc("?end@c_default_tag_file_sync_source@@UAAXXZ");

    tag_files_sync_reload_end();
};

// $TODO nonmatching: target loads the string address without a relocation (lis 0x822d / subi); instructions otherwise identical
char const * c_default_tag_file_sync_source::get_name(void)
{
    mangled_ppc("?get_name@c_default_tag_file_sync_source@@UAAPBDXZ");

    return "tag_files";
};

