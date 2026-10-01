#pragma once
#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

/* ---------- headers */

/* ---------- constants */

enum e_language
{
    k_first_language = 0,
    _language_english = k_first_language,
    _language_japanese,
    _language_german,
    _language_french,
    _language_spanish,
    _language_mexican_spanish,
    _language_italian,
    _language_korean,
    _language_traditional_chinese,
    _language_simplified_chinese,
    _language_portuguese,
    _language_polish,

    k_language_count,
    _language_invalid = -1,
    k_language_default = _language_english
};

enum e_locale
{
    k_first_locale = 0,
    _locale_australia = k_first_locale,
    _locale_austria,
    _locale_belgium,
    _locale_brazil,
    _locale_canada,
    _locale_chile,
    _locale_china,
    _locale_columbia,
    _locale_czechoslovakia,
    _locale_denmark,
    _locale_finland,
    _locale_france,
    _locale_germany,
    _locale_greece,
    _locale_hong_kong,
    _locale_hungary,
    _locale_india,
    _locale_ireland,
    _locale_italy,
    _locale_japan,
    _locale_korea,
    _locale_mexico,
    _locale_netherlands,
    _locale_new_zealand,
    _locale_norway,
    _locale_poland,
    _locale_portugal,
    _locale_singapore,
    _locale_slovakia,
    _locale_south_africa,
    _locale_spain,
    _locale_sweden,
    _locale_switzerland,
    _locale_taiwan,
    _locale_great_britain,
    _locale_united_states,

    k_locale_count,
    _locale_invalid = -1,
    k_locale_default = _locale_united_states
};

enum e_region
{
    k_first_region = 0,
    _region_north_america = k_first_region,
    _region_asia_all,
    _region_asia_japan,
    _region_asia_china,
    _region_asia_remainder,
    _region_europe_all,
    _region_europe_australia_new_zealand,
    _region_europe_remainder,
    _region_planet_earth_remainder,
    _region_devkit,
    _region_manufacturing,

    k_region_count,
    _region_invalid = -1,
    k_region_default = _region_north_america
};

/* ---------- definitions */

/* ---------- prototypes */

e_language get_current_language(void);
e_language get_language_from_display_name_slow(char const * display_name);
void set_current_language(e_language language);
void set_current_language_from_display_name_slow(char const * display_name);
bool does_current_language_have_supported_fonts(void);
char const * get_language_suffix(e_language language, bool english_is_empty);
char const * get_current_language_suffix(bool english_is_empty);
char const * get_language_display_name(e_language language);
char const * get_language_iso_639_1_name(e_language language);
void get_localized_data_directory_name(e_language language, char * buffer, long count);
e_locale get_current_locale(void);
long get_xbox_locale_from_e_locale(e_locale locale);
e_locale get_e_locale_from_xbox_locale(long xbox_locale);
e_region get_current_region(void);
e_region get_e_region_from_xbox_region(long xbox_region);
e_language get_e_language_from_xbox_language(unsigned long xbox_language);

/* ---------- globals */

/* ---------- public code */

// inline in the target (text_group.obj)
inline e_language & operator++(e_language & language)
{
    language = static_cast<e_language>(language + 1);

    return language;
};

#endif // __LANGUAGE_H__
