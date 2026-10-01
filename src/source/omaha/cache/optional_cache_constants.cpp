/* ---------- headers */

#include "omaha\cache\optional_cache_constants.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<unsigned long, 3>::k_element_count; // "?k_element_count@?$s_static_array@K$02@@2JB"

// void optional_cache_calculate_priority_sizes(class s_static_array<struct s_optional_cache_user_memory_configuration, 6> const *, struct s_optional_cache_priority_sizes *);
// public: void s_static_array<unsigned long, 3>::set_all(unsigned long const &);
// public: struct s_optional_cache_user_memory_configuration const & s_static_array<struct s_optional_cache_user_memory_configuration, 6>::operator[]<long>(long) const;
// public: unsigned long & s_static_array<unsigned long, 3>::operator[]<enum e_optional_cache_user_priority>(enum e_optional_cache_user_priority);
// public: static bool s_static_array<unsigned long, 3>::valid<enum e_optional_cache_user_priority>(enum e_optional_cache_user_priority);

void optional_cache_calculate_priority_sizes(s_static_array<s_optional_cache_user_memory_configuration, k_number_of_optional_cache_users> const * memory_configurations, s_optional_cache_priority_sizes * out_priority_sizes)
{
    mangled_ppc("?optional_cache_calculate_priority_sizes@@YAXPBV?$s_static_array@Us_optional_cache_user_memory_configuration@@$05@@PAUs_optional_cache_priority_sizes@@@Z");

    s_static_array<unsigned long, k_number_of_optional_cache_user_priorities> maximum_sizes;
    s_static_array<unsigned long, k_number_of_optional_cache_user_priorities> minimum_sizes;

    minimum_sizes.set_all(0);
    maximum_sizes.set_all(0);

    for (long memory_configuration_index = 0; memory_configuration_index < k_number_of_optional_cache_users; memory_configuration_index++)
    {
        s_optional_cache_user_memory_configuration const * user_configuration = &(*memory_configurations)[memory_configuration_index];

        minimum_sizes[user_configuration->maximum_priority] = MAX(minimum_sizes[user_configuration->maximum_priority], user_configuration->maximum_size);
        maximum_sizes[user_configuration->maximum_priority] += user_configuration->maximum_size;
    }

    out_priority_sizes->minimum_no_fail_size = MAX(minimum_sizes[_optional_cache_user_cant_fail_blocking], minimum_sizes[_optional_cache_user_cant_fail_nonblocking]);
    out_priority_sizes->desired_no_fail_size = maximum_sizes[_optional_cache_user_cant_fail_blocking] + maximum_sizes[_optional_cache_user_cant_fail_nonblocking];
    out_priority_sizes->minimum_can_fail_size = minimum_sizes[_optional_cache_user_can_fail];
    out_priority_sizes->desired_can_fail_size = maximum_sizes[_optional_cache_user_can_fail];
};

