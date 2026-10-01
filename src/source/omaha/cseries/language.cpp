#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cseries\\language.cpp"
/* ---------- headers */

#include "omaha\cseries\language.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\interface\user_interface_window_manager.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\sound_manager.h"
#include "omaha\text\font_loading.h"
#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static e_language g_current_language = _language_invalid;
static e_locale g_current_locale = _locale_invalid;
static e_region g_current_region = _region_invalid;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// enum e_language get_current_language(void);
// enum e_language get_language_from_display_name_slow(char const *);
// void set_current_language(enum e_language);
// void set_current_language_from_display_name_slow(char const *);
// bool does_current_language_have_supported_fonts(void);
// char const * get_language_suffix(enum e_language, bool);
// char const * get_current_language_suffix(bool);
// char const * get_language_display_name(enum e_language);
// char const * get_language_iso_639_1_name(enum e_language);
// void get_localized_data_directory_name(enum e_language, char *, long);
// enum e_locale get_current_locale(void);
// long get_xbox_locale_from_e_locale(enum e_locale);
// enum e_locale get_e_locale_from_xbox_locale(long);
// enum e_region get_current_region(void);
// enum e_region get_e_region_from_xbox_region(long);
// enum e_language get_e_language_from_xbox_language(unsigned long);

e_language get_current_language(void)
{
    mangled_ppc("?get_current_language@@YA?AW4e_language@@XZ");

    if (g_current_language == _language_invalid)
    {
        g_current_language = get_e_language_from_xbox_language(XGetLanguage());
    }

    return g_current_language;
};

e_language get_language_from_display_name_slow(char const * display_name)
{
    mangled_ppc("?get_language_from_display_name_slow@@YA?AW4e_language@@PBD@Z");

    e_language result = _language_invalid;
    for (e_language language = k_first_language; language < k_language_count; ++language)
    {
        if (csstricmp(display_name, get_language_display_name(language)) == 0)
        {
            result = language;
            break;
        }
    }

    return result;
};

void set_current_language(e_language language)
{
    mangled_ppc("?set_current_language@@YAXW4e_language@@@Z");

    assert_tag_debug_untracked_jul_11_2011(64, language!=_language_invalid);

    if (language != g_current_language)
    {
        sound_manager_prepare_for_language_change();
        g_current_language = language;
        font_reload();
        window_manager_reset_screens();
        sound_manager_handle_language_change();
    }
};

void set_current_language_from_display_name_slow(char const * display_name)
{
    mangled_ppc("?set_current_language_from_display_name_slow@@YAXPBD@Z");

    e_language language = get_language_from_display_name_slow(display_name);
    if (language != _language_invalid)
    {
        set_current_language(language);
    }
    else
    {
        event_wrapped(_event_error, "invalid language '%s'", display_name);
    }
};

bool does_current_language_have_supported_fonts(void)
{
    mangled_ppc("?does_current_language_have_supported_fonts@@YA_NXZ");

    bool result = false;
    switch (XGetLanguage())
    {
    case XC_LANGUAGE_ENGLISH:
    case XC_LANGUAGE_JAPANESE:
    case XC_LANGUAGE_GERMAN:
    case XC_LANGUAGE_FRENCH:
    case XC_LANGUAGE_SPANISH:
    case XC_LANGUAGE_ITALIAN:
    case XC_LANGUAGE_KOREAN:
    case XC_LANGUAGE_TCHINESE:
    case XC_LANGUAGE_PORTUGUESE:
    case XC_LANGUAGE_SCHINESE:
        result = true;
        break;
    }

    return result;
};

// only diffs: unrelocated jump table / string addresses in the target (objdiff artifact)
char const * get_language_suffix(e_language language, bool english_is_empty)
{
    mangled_ppc("?get_language_suffix@@YAPBDW4e_language@@_N@Z");

    char const * result = NULL;
    switch (language)
    {
    case _language_english:
        result = english_is_empty ? "" : "en";
        break;
    case _language_japanese:
        result = "jpn";
        break;
    case _language_german:
        result = "de";
        break;
    case _language_french:
        result = "fr";
        break;
    case _language_spanish:
        result = "sp";
        break;
    case _language_mexican_spanish:
        result = "mx";
        break;
    case _language_italian:
        result = "it";
        break;
    case _language_korean:
        result = "kor";
        break;
    case _language_traditional_chinese:
        result = "cht";
        break;
    case _language_simplified_chinese:
        result = "chs";
        break;
    case _language_portuguese:
        result = "pt";
        break;
    case _language_polish:
        result = "pl";
        break;
    default:
        dassert_tag_debug_untracked_jul_11_2011(150, false, "unreachable");
        break;
    }

    return result;
};

char const * get_current_language_suffix(bool english_is_empty)
{
    mangled_ppc("?get_current_language_suffix@@YAPBD_N@Z");

    e_language current_language = get_current_language();
    char const * result = get_language_suffix(current_language, english_is_empty);

    return result;
};

// only diffs: unrelocated jump table / string addresses in the target (objdiff artifact)
char const * get_language_display_name(e_language language)
{
    mangled_ppc("?get_language_display_name@@YAPBDW4e_language@@@Z");

    char const * result = "";
    switch (language)
    {
    case _language_english:
        result = "english";
        break;
    case _language_japanese:
        result = "japanese";
        break;
    case _language_german:
        result = "german";
        break;
    case _language_french:
        result = "french";
        break;
    case _language_spanish:
        result = "spanish";
        break;
    case _language_mexican_spanish:
        result = "mexican";
        break;
    case _language_italian:
        result = "italian";
        break;
    case _language_korean:
        result = "korean";
        break;
    case _language_traditional_chinese:
        result = "chinese-traditional";
        break;
    case _language_simplified_chinese:
        result = "chinese-simplified";
        break;
    case _language_portuguese:
        result = "portuguese";
        break;
    case _language_polish:
        result = "polish";
        break;
    }

    return result;
};

// only diffs: unrelocated jump table / string addresses in the target (objdiff artifact)
char const * get_language_iso_639_1_name(e_language language)
{
    mangled_ppc("?get_language_iso_639_1_name@@YAPBDW4e_language@@@Z");

    char const * result = "";
    switch (language)
    {
    case _language_english:
        result = "en-US";
        break;
    case _language_japanese:
        result = "jp-JP";
        break;
    case _language_german:
        result = "de-DE";
        break;
    case _language_french:
        result = "fr-FR";
        break;
    case _language_spanish:
        result = "es-ES";
        break;
    case _language_mexican_spanish:
        result = "es-MX";
        break;
    case _language_italian:
        result = "it-IT";
        break;
    case _language_korean:
        result = "ko-KR";
        break;
    case _language_traditional_chinese:
        result = "zh-TW";
        break;
    case _language_simplified_chinese:
        result = "zh-CN";
        break;
    case _language_portuguese:
        result = "pt-PT";
        break;
    case _language_polish:
        result = "pl-PL";
        break;
    }

    return result;
};

void get_localized_data_directory_name(e_language language, char * buffer, long count)
{
    mangled_ppc("?get_localized_data_directory_name@@YAXW4e_language@@PADJ@Z");

    assert_tag_debug_untracked_jul_11_2011(218, buffer!=NULL);
    assert_tag_debug_untracked_jul_11_2011(219, count>0);

    char const * suffix = get_language_suffix(language, true);
    buffer[0] = 0;
    csstrnzcat(buffer, "data", count);
    if (suffix[0] != 0)
    {
        csstrnzcat(buffer, "_", count);
        csstrnzcat(buffer, suffix, count);
    }
};

e_locale get_current_locale(void)
{
    mangled_ppc("?get_current_locale@@YA?AW4e_locale@@XZ");

    if (g_current_locale == _locale_invalid)
    {
        g_current_locale = get_e_locale_from_xbox_locale(XGetLocale());
    }

    return g_current_locale;
};

// only diffs: unrelocated jump table / string addresses in the target (objdiff artifact)
long get_xbox_locale_from_e_locale(e_locale locale)
{
    mangled_ppc("?get_xbox_locale_from_e_locale@@YAJW4e_locale@@@Z");

    long xbox_locale = 0;
    switch (locale)
    {
    case _locale_australia:
        xbox_locale = XC_LOCALE_AUSTRALIA;
        break;
    case _locale_austria:
        xbox_locale = XC_LOCALE_AUSTRIA;
        break;
    case _locale_belgium:
        xbox_locale = XC_LOCALE_BELGIUM;
        break;
    case _locale_brazil:
        xbox_locale = XC_LOCALE_BRAZIL;
        break;
    case _locale_canada:
        xbox_locale = XC_LOCALE_CANADA;
        break;
    case _locale_chile:
        xbox_locale = XC_LOCALE_CHILE;
        break;
    case _locale_china:
        xbox_locale = XC_LOCALE_CHINA;
        break;
    case _locale_columbia:
        xbox_locale = XC_LOCALE_COLOMBIA;
        break;
    case _locale_czechoslovakia:
        xbox_locale = XC_LOCALE_CZECH_REPUBLIC;
        break;
    case _locale_denmark:
        xbox_locale = XC_LOCALE_DENMARK;
        break;
    case _locale_finland:
        xbox_locale = XC_LOCALE_FINLAND;
        break;
    case _locale_france:
        xbox_locale = XC_LOCALE_FRANCE;
        break;
    case _locale_germany:
        xbox_locale = XC_LOCALE_GERMANY;
        break;
    case _locale_greece:
        xbox_locale = XC_LOCALE_GREECE;
        break;
    case _locale_hong_kong:
        xbox_locale = XC_LOCALE_HONG_KONG;
        break;
    case _locale_hungary:
        xbox_locale = XC_LOCALE_HUNGARY;
        break;
    case _locale_india:
        xbox_locale = XC_LOCALE_INDIA;
        break;
    case _locale_ireland:
        xbox_locale = XC_LOCALE_IRELAND;
        break;
    case _locale_italy:
        xbox_locale = XC_LOCALE_ITALY;
        break;
    case _locale_japan:
        xbox_locale = XC_LOCALE_JAPAN;
        break;
    case _locale_korea:
        xbox_locale = XC_LOCALE_KOREA;
        break;
    case _locale_mexico:
        xbox_locale = XC_LOCALE_MEXICO;
        break;
    case _locale_netherlands:
        xbox_locale = XC_LOCALE_NETHERLANDS;
        break;
    case _locale_new_zealand:
        xbox_locale = XC_LOCALE_NEW_ZEALAND;
        break;
    case _locale_norway:
        xbox_locale = XC_LOCALE_NORWAY;
        break;
    case _locale_poland:
        xbox_locale = XC_LOCALE_POLAND;
        break;
    case _locale_portugal:
        xbox_locale = XC_LOCALE_PORTUGAL;
        break;
    case _locale_singapore:
        xbox_locale = XC_LOCALE_SINGAPORE;
        break;
    case _locale_slovakia:
        xbox_locale = XC_LOCALE_SLOVAK_REPUBLIC;
        break;
    case _locale_south_africa:
        xbox_locale = XC_LOCALE_SOUTH_AFRICA;
        break;
    case _locale_spain:
        xbox_locale = XC_LOCALE_SPAIN;
        break;
    case _locale_sweden:
        xbox_locale = XC_LOCALE_SWEDEN;
        break;
    case _locale_switzerland:
        xbox_locale = XC_LOCALE_SWITZERLAND;
        break;
    case _locale_taiwan:
        xbox_locale = XC_LOCALE_TAIWAN;
        break;
    case _locale_great_britain:
        xbox_locale = XC_LOCALE_GREAT_BRITAIN;
        break;
    case _locale_united_states:
        xbox_locale = XC_LOCALE_UNITED_STATES;
        break;
    }

    return xbox_locale;
};

// only diffs: unrelocated jump table / string addresses in the target (objdiff artifact)
e_locale get_e_locale_from_xbox_locale(long xbox_locale)
{
    mangled_ppc("?get_e_locale_from_xbox_locale@@YA?AW4e_locale@@J@Z");

    e_locale locale = k_locale_default;
    switch (xbox_locale)
    {
    case XC_LOCALE_AUSTRALIA:
        locale = _locale_australia;
        break;
    case XC_LOCALE_AUSTRIA:
        locale = _locale_austria;
        break;
    case XC_LOCALE_BELGIUM:
        locale = _locale_belgium;
        break;
    case XC_LOCALE_BRAZIL:
        locale = _locale_brazil;
        break;
    case XC_LOCALE_CANADA:
        locale = _locale_canada;
        break;
    case XC_LOCALE_CHILE:
        locale = _locale_chile;
        break;
    case XC_LOCALE_CHINA:
        locale = _locale_china;
        break;
    case XC_LOCALE_COLOMBIA:
        locale = _locale_columbia;
        break;
    case XC_LOCALE_CZECH_REPUBLIC:
        locale = _locale_czechoslovakia;
        break;
    case XC_LOCALE_DENMARK:
        locale = _locale_denmark;
        break;
    case XC_LOCALE_FINLAND:
        locale = _locale_finland;
        break;
    case XC_LOCALE_FRANCE:
        locale = _locale_france;
        break;
    case XC_LOCALE_GERMANY:
        locale = _locale_germany;
        break;
    case XC_LOCALE_GREECE:
        locale = _locale_greece;
        break;
    case XC_LOCALE_HONG_KONG:
        locale = _locale_hong_kong;
        break;
    case XC_LOCALE_HUNGARY:
        locale = _locale_hungary;
        break;
    case XC_LOCALE_INDIA:
        locale = _locale_india;
        break;
    case XC_LOCALE_IRELAND:
        locale = _locale_ireland;
        break;
    case XC_LOCALE_ITALY:
        locale = _locale_italy;
        break;
    case XC_LOCALE_JAPAN:
        locale = _locale_japan;
        break;
    case XC_LOCALE_KOREA:
        locale = _locale_korea;
        break;
    case XC_LOCALE_MEXICO:
        locale = _locale_mexico;
        break;
    case XC_LOCALE_NETHERLANDS:
        locale = _locale_netherlands;
        break;
    case XC_LOCALE_NEW_ZEALAND:
        locale = _locale_new_zealand;
        break;
    case XC_LOCALE_NORWAY:
        locale = _locale_norway;
        break;
    case XC_LOCALE_POLAND:
        locale = _locale_poland;
        break;
    case XC_LOCALE_PORTUGAL:
        locale = _locale_portugal;
        break;
    case XC_LOCALE_SINGAPORE:
        locale = _locale_singapore;
        break;
    case XC_LOCALE_SLOVAK_REPUBLIC:
        locale = _locale_slovakia;
        break;
    case XC_LOCALE_SOUTH_AFRICA:
        locale = _locale_south_africa;
        break;
    case XC_LOCALE_SPAIN:
        locale = _locale_spain;
        break;
    case XC_LOCALE_SWEDEN:
        locale = _locale_sweden;
        break;
    case XC_LOCALE_SWITZERLAND:
        locale = _locale_switzerland;
        break;
    case XC_LOCALE_TAIWAN:
        locale = _locale_taiwan;
        break;
    case XC_LOCALE_GREAT_BRITAIN:
        locale = _locale_great_britain;
        break;
    case XC_LOCALE_UNITED_STATES:
        locale = _locale_united_states;
        break;
    }

    return locale;
};

e_region get_current_region(void)
{
    mangled_ppc("?get_current_region@@YA?AW4e_region@@XZ");

    if (g_current_region == _region_invalid)
    {
        g_current_region = get_e_region_from_xbox_region(XGetGameRegion());
    }

    return g_current_region;
};

e_region get_e_region_from_xbox_region(long xbox_region)
{
    mangled_ppc("?get_e_region_from_xbox_region@@YA?AW4e_region@@J@Z");

    e_region region = k_region_default;
    switch (xbox_region)
    {
    case XC_GAME_REGION_NA_ALL:
        region = _region_north_america;
        break;
    case XC_GAME_REGION_ASIA_ALL:
        region = _region_asia_all;
        break;
    case XC_GAME_REGION_ASIA_JAPAN:
        region = _region_asia_japan;
        break;
    case XC_GAME_REGION_ASIA_CHINA:
        region = _region_asia_china;
        break;
    case XC_GAME_REGION_ASIA_REST:
        region = _region_asia_remainder;
        break;
    case XC_GAME_REGION_EUROPE_ALL:
        region = _region_europe_all;
        break;
    case XC_GAME_REGION_EUROPE_AUNZ:
        region = _region_europe_australia_new_zealand;
        break;
    case XC_GAME_REGION_EUROPE_REST:
        region = _region_europe_remainder;
        break;
    case XC_GAME_REGION_RESTOFWORLD_ALL:
        region = _region_planet_earth_remainder;
        break;
    case XC_GAME_REGION_DEVKIT_ALL:
        region = _region_devkit;
        break;
    case XC_GAME_REGION_MANUFACTURING:
        region = _region_manufacturing;
        break;
    }

    return region;
};

// only diffs: unrelocated jump table / string addresses in the target (objdiff artifact)
e_language get_e_language_from_xbox_language(unsigned long xbox_language)
{
    mangled_ppc("?get_e_language_from_xbox_language@@YA?AW4e_language@@K@Z");

    e_language language = _language_invalid;
    if (language == _language_invalid)
    {
        switch (xbox_language)
        {
        case XC_LANGUAGE_ENGLISH:
            language = _language_english;
            break;
        case XC_LANGUAGE_JAPANESE:
            language = _language_japanese;
            break;
        case XC_LANGUAGE_GERMAN:
            language = _language_german;
            break;
        case XC_LANGUAGE_FRENCH:
            language = _language_french;
            break;
        case XC_LANGUAGE_SPANISH:
            switch (get_current_locale())
            {
            case _locale_canada:
            case _locale_chile:
            case _locale_columbia:
            case _locale_mexico:
            case _locale_united_states:
                language = _language_mexican_spanish;
                break;
            default:
                language = _language_spanish;
                break;
            }
            break;
        case XC_LANGUAGE_ITALIAN:
            language = _language_italian;
            break;
        case XC_LANGUAGE_KOREAN:
            language = _language_korean;
            break;
        case XC_LANGUAGE_TCHINESE:
            language = _language_traditional_chinese;
            break;
        case XC_LANGUAGE_SCHINESE:
            language = _language_simplified_chinese;
            break;
        case XC_LANGUAGE_PORTUGUESE:
            language = _language_portuguese;
            break;
        default:
            language = _language_english;
            break;
        }
    }

    return language;
};

