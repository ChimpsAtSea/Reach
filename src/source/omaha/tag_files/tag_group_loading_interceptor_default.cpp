#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_group_loading_interceptor_default.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_group_loading_interceptor_default.h"
#include "omaha\tag_files\tag_files.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: virtual bool c_tag_file_backend_loader::load_into_block(struct s_tag_block *, struct s_tag_group const *, char const *, class c_flags<enum e_load_tag_flag, unsigned short, 10, struct s_default_enum_string_resolver>, enum e_tag_file_open_result *, bool *, unsigned long *, class c_tag_alternate_stream_consumer *);
// public: virtual class c_tag_instance_loader * c_default_tag_instance_loader_redirector::lookup_instance_loader(struct s_tag_group const *, char const *, class c_flags<enum e_load_tag_flag, unsigned short, 10, struct s_default_enum_string_resolver>);
// public: virtual char const * c_default_tag_instance_loader_redirector::get_name(void);
// public: virtual void c_default_tag_instance_loader_redirector::release_instance_loader(class c_tag_instance_loader *);

bool c_tag_file_backend_loader::load_into_block(s_tag_block * block, s_tag_group const * group, char const * name, c_load_tag_flag flags, e_tag_file_open_result * open_result, bool * out_unknown, unsigned long * checksum, c_tag_alternate_stream_consumer * stream_consumer)
{
    mangled_ppc("?load_into_block@c_tag_file_backend_loader@@UAA_NPAUs_tag_block@@PBUs_tag_group@@PBDV?$c_flags@W4e_load_tag_flag@@G$09Us_default_enum_string_resolver@@@@PAW4e_tag_file_open_result@@PA_NPAKPAVc_tag_alternate_stream_consumer@@@Z");

    return tag_load_from_backend(block, group, name, flags, open_result, out_unknown, checksum, stream_consumer);
};

c_tag_instance_loader * c_default_tag_instance_loader_redirector::lookup_instance_loader(s_tag_group const * group, char const * name, c_load_tag_flag flags)
{
    mangled_ppc("?lookup_instance_loader@c_default_tag_instance_loader_redirector@@UAAPAVc_tag_instance_loader@@PBUs_tag_group@@PBDV?$c_flags@W4e_load_tag_flag@@G$09Us_default_enum_string_resolver@@@@@Z");

    return &m_default_loader;
};

// $TODO nonmatching: the target "default" literal is pooled into render_mesh.obj, so the target lis/subi carries no relocation
char const * c_default_tag_instance_loader_redirector::get_name(void)
{
    mangled_ppc("?get_name@c_default_tag_instance_loader_redirector@@UAAPBDXZ");

    return "default";
};

void c_default_tag_instance_loader_redirector::release_instance_loader(c_tag_instance_loader * instance_loader)
{
    mangled_ppc("?release_instance_loader@c_default_tag_instance_loader_redirector@@UAAXPAVc_tag_instance_loader@@@Z");

    assert_tag_debug_untracked_jul_11_2011(50, &m_default_loader==instance_loader);
};

