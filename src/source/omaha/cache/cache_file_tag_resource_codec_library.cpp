#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\cache_file_tag_resource_codec_library.cpp"
/* ---------- headers */

#include "omaha\cache\cache_file_tag_resource_codec_library.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"
#include "omaha\toolbox\stl_helpers.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_cache_file_tag_resource_codec_library::add_codec(struct s_cache_file_codec_definition const &);
// public: long c_cache_file_tag_resource_codec_library::create_uncompressed_identifier(void) const;
// public: bool c_cache_file_tag_resource_codec_library::is_uncompressed(long) const;
// public: long c_cache_file_tag_resource_codec_library::get_codec_index(struct s_cache_file_codec_definition const &) const;
// public: long c_cache_file_tag_resource_codec_library::create_codec_identifier(struct s_cache_file_codec_definition const &) const;
// public: long c_cache_file_tag_resource_codec_library::get_codec_index(long) const;
// public: bool c_cache_file_tag_resource_codec_library::is_codec_index(long) const;
// public: long c_cache_file_tag_resource_codec_library::create_sublocation_table_identifier(void) const;
// public: bool c_cache_file_tag_resource_codec_library::is_sublocation_table(long) const;
// public: struct s_cache_file_codec_definition const & c_cache_file_tag_resource_codec_library::get_codec_definition(long) const;
// public: long c_cache_file_tag_resource_codec_library::get_codec_count(void) const;
// public: long c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127>::count(void) const;
// public: struct s_cache_file_codec_definition const & c_array_operator_interface<class c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127>, struct s_cache_file_codec_definition>::operator[](long) const;
// public: struct s_cache_file_codec_definition const * c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127>::begin(void) const;
// public: bool c_array_operator_interface<class c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127>, struct s_cache_file_codec_definition>::valid_index(long) const;
// public: class c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127> const * c_recursive_template_pattern<class c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127> >::get_super_class(void) const;
// public: long c_array_operator_interface<class c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127>, struct s_cache_file_codec_definition>::count(void) const;
// public: struct s_cache_file_codec_definition const * s_static_array<struct s_cache_file_codec_definition, 127>::begin(void) const;
// long find_or_add_container_value<class c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127>, struct s_cache_file_codec_definition>(class c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127> *, struct s_cache_file_codec_definition const &);
// bool find_container_value_index<class c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127>, struct s_cache_file_codec_definition>(class c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127> const &, struct s_cache_file_codec_definition const &, long *);
// public: long c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127>::new_element_index(void);
// public: struct s_cache_file_codec_definition * c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127>::begin(void);
// public: struct s_cache_file_codec_definition & c_array_operator_interface<class c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127>, struct s_cache_file_codec_definition>::operator[](long);
// public: class c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127> * c_recursive_template_pattern<class c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127> >::get_super_class(void);
// public: struct s_cache_file_codec_definition * s_static_array<struct s_cache_file_codec_definition, 127>::begin(void);
// class c_memcmp_value_compare<struct s_cache_file_codec_definition> value_compare<struct s_cache_file_codec_definition>(struct s_cache_file_codec_definition const &);
// bool find_if_container_value<class c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127>, class c_memcmp_value_compare<struct s_cache_file_codec_definition>, struct s_cache_file_codec_definition const *>(class c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127> const &, class c_memcmp_value_compare<struct s_cache_file_codec_definition>, struct s_cache_file_codec_definition const **);
// public: static bool s_static_array<struct s_cache_file_codec_definition, 127>::valid<long>(long);
// public: struct s_cache_file_codec_definition const * c_static_sized_dynamic_array<struct s_cache_file_codec_definition, 127>::end(void) const;
// public: c_memcmp_value_compare<struct s_cache_file_codec_definition>::c_memcmp_value_compare<struct s_cache_file_codec_definition>(struct s_cache_file_codec_definition const &);
// struct s_cache_file_codec_definition const * std::find_if<struct s_cache_file_codec_definition const *, class c_memcmp_value_compare<struct s_cache_file_codec_definition> >(struct s_cache_file_codec_definition const *, struct s_cache_file_codec_definition const *, class c_memcmp_value_compare<struct s_cache_file_codec_definition>);
// struct s_cache_file_codec_definition const * std::_Checked_base<struct s_cache_file_codec_definition const *>(struct s_cache_file_codec_definition const *&);
// struct s_cache_file_codec_definition const * std::_Find_if<struct s_cache_file_codec_definition const *, class c_memcmp_value_compare<struct s_cache_file_codec_definition> >(struct s_cache_file_codec_definition const *, struct s_cache_file_codec_definition const *, class c_memcmp_value_compare<struct s_cache_file_codec_definition>);
// void std::_Checked_assign_from_base<struct s_cache_file_codec_definition const *>(struct s_cache_file_codec_definition const *&, struct s_cache_file_codec_definition const *const &);
// public: bool c_memcmp_value_compare<struct s_cache_file_codec_definition>::operator()(struct s_cache_file_codec_definition const &) const;
// struct s_cache_file_codec_definition const * std::_Checked_base<struct s_cache_file_codec_definition const *>(struct s_cache_file_codec_definition const *&, struct std::_Unchanged_checked_iterator_base_type_tag);
// void std::_Debug_range<struct s_cache_file_codec_definition const *>(struct s_cache_file_codec_definition const *, struct s_cache_file_codec_definition const *, wchar_t const *, unsigned int);
// void std::_Debug_pointer<class c_memcmp_value_compare<struct s_cache_file_codec_definition> >(class c_memcmp_value_compare<struct s_cache_file_codec_definition> &, wchar_t const *, unsigned int);
// struct std::random_access_iterator_tag std::_Iter_cat<struct s_cache_file_codec_definition const *>(struct s_cache_file_codec_definition const *const &);
// void std::_Debug_range2<struct s_cache_file_codec_definition const *>(struct s_cache_file_codec_definition const *, struct s_cache_file_codec_definition const *, wchar_t const *, unsigned int, struct std::random_access_iterator_tag);
// void std::_Debug_pointer<struct s_cache_file_codec_definition>(struct s_cache_file_codec_definition const *, wchar_t const *, unsigned int);

void c_cache_file_tag_resource_codec_library::add_codec(s_cache_file_codec_definition const & codec_definition)
{
    mangled_ppc("?add_codec@c_cache_file_tag_resource_codec_library@@QAAXABUs_cache_file_codec_definition@@@Z");

    long new_index = find_or_add_container_value(&m_codecs, codec_definition);
    assert_tag_debug_untracked_jul_11_2011(15, new_index!=NONE);
};

long c_cache_file_tag_resource_codec_library::create_uncompressed_identifier() const
{
    mangled_ppc("?create_uncompressed_identifier@c_cache_file_tag_resource_codec_library@@QBAJXZ");

    return NONE;
};

bool c_cache_file_tag_resource_codec_library::is_uncompressed(long identifier) const
{
    mangled_ppc("?is_uncompressed@c_cache_file_tag_resource_codec_library@@QBA_NJ@Z");

    return identifier == static_cast<long>(NONE);
};

long c_cache_file_tag_resource_codec_library::get_codec_index(s_cache_file_codec_definition const & codec_definition) const
{
    mangled_ppc("?get_codec_index@c_cache_file_tag_resource_codec_library@@QBAJABUs_cache_file_codec_definition@@@Z");

    long codec_index;
    if (!find_container_value_index(m_codecs, codec_definition, &codec_index))
    {
        codec_index = NONE;
    }

    return codec_index;
};

long c_cache_file_tag_resource_codec_library::create_codec_identifier(s_cache_file_codec_definition const & codec_definition) const
{
    mangled_ppc("?create_codec_identifier@c_cache_file_tag_resource_codec_library@@QBAJABUs_cache_file_codec_definition@@@Z");

    long codec_index = get_codec_index(codec_definition);
    assert_tag_debug_untracked_jul_11_2011(51, codec_index!=NONE);

    return codec_index & 0x7FFFFFFF;
};

long c_cache_file_tag_resource_codec_library::get_codec_index(long decompressor_identifier) const
{
    mangled_ppc("?get_codec_index@c_cache_file_tag_resource_codec_library@@QBAJJ@Z");

    assert_tag_debug_untracked_jul_11_2011(59, is_codec_index(decompressor_identifier));

    return decompressor_identifier & 0x7FFFFFFF;
};

bool c_cache_file_tag_resource_codec_library::is_codec_index(long identifier) const
{
    mangled_ppc("?is_codec_index@c_cache_file_tag_resource_codec_library@@QBA_NJ@Z");

    return identifier != static_cast<long>(NONE) && !TEST_BIT(identifier, 31);
};

long c_cache_file_tag_resource_codec_library::create_sublocation_table_identifier() const
{
    mangled_ppc("?create_sublocation_table_identifier@c_cache_file_tag_resource_codec_library@@QBAJXZ");

    return FLAG(31);
};

bool c_cache_file_tag_resource_codec_library::is_sublocation_table(long identifier) const
{
    mangled_ppc("?is_sublocation_table@c_cache_file_tag_resource_codec_library@@QBA_NJ@Z");

    return identifier != static_cast<long>(NONE) && TEST_BIT(identifier, 31);
};

s_cache_file_codec_definition const & c_cache_file_tag_resource_codec_library::get_codec_definition(long codec_index) const
{
    mangled_ppc("?get_codec_definition@c_cache_file_tag_resource_codec_library@@QBAABUs_cache_file_codec_definition@@J@Z");

    return m_codecs[codec_index];
};

long c_cache_file_tag_resource_codec_library::get_codec_count() const
{
    mangled_ppc("?get_codec_count@c_cache_file_tag_resource_codec_library@@QBAJXZ");

    return m_codecs.count();
};

