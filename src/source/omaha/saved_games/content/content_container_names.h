#pragma once
#ifndef __CONTENT_CONTAINER_NAMES_H__
#define __CONTENT_CONTAINER_NAMES_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

long const k_content_container_name_type_prefix_length_without_null = 1;
long const k_content_container_name_length_without_null = 42;
long const k_content_container_name_encoded_portion_length = 42;

/* ---------- definitions */

/* ---------- prototypes */

void content_build_container_name_from_raw_container_name(c_static_string<43> * out_container_name, char const * const raw_container_name);
void content_build_raw_container_name_from_container_name(char * const out_raw_container_name, c_static_string<43> const * container_name);
void content_extract_type_prefix_from_container_name(c_static_string<43> * out_type_prefix, c_static_string<43> const * container_name);
void content_extract_encoded_portion_from_container_name(s_static_string<42> * out_encoded_portion, c_static_string<43> const * container_name);
void content_build_container_name_from_type_prefix_and_encoded_portion(c_static_string<43> * out_container_name, c_static_string<43> const * type_prefix_string, s_static_string<42> const * encoded_portion);

/* ---------- globals */

/* ---------- public code */

#endif // __CONTENT_CONTAINER_NAMES_H__

