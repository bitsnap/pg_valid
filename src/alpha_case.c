//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#include <stdbool.h>
#include <string.h>

#include <unicode/uchar.h>
#include <unicode/utypes.h>
#include <unicode/ucnv.h>

#include "pg_valid.h"

inline bool is_lowercase_internal(const char c) {
    return c >= 'a' && c <= 'z';
}

inline bool is_uppercase_internal(const char c) {
    return c >= 'A' && c <= 'Z';
}

#ifndef alphacase_unicode_cmp_snippet
#define alphacase_unicode_cmp_snippet(fun) \
    UErrorCode err = U_ZERO_ERROR; \
    UConverter *conv = ucnv_open("UTF-8", &err); \
    if (!U_SUCCESS(err)) { \
        return false; \
    } \
    const char *end = str + strlen(str); \
    const char *curr = str; \
    while (err != U_INDEX_OUTOFBOUNDS_ERROR) { \
        UChar32 c = ucnv_getNextUChar(conv, (const char **) &curr, end, &err); \
        if (!U_SUCCESS(err)) { \
            break; \
        } \
        if (!u_isU##fun(c)) { \
            ucnv_close(conv); \
            return false; \
        } \
    } \
    ucnv_close(conv);
#endif

bool is_lowercase_unicode_internal(const char *str) {
    alphacase_unicode_cmp_snippet(Lowercase)
    return true;
}

bool is_uppercase_unicode_internal(const char *str) {
    alphacase_unicode_cmp_snippet(Uppercase)
    return true;
}

#ifndef alphacase_cmp_snippet
#define alphacase_cmp_snippet(fun) \
    size_t len = strlen(str); \
    int i = 0; \
    for (; i < len; i++) { \
        if (!is_ascii(str[i])) { \
            return is_##fun##_unicode_internal(str); \
        } \
        if (is_num_internal(str[i])) { \
            continue; \
        } \
        if (!is_##fun##_internal(str[i])) { \
            return false; \
        } \
    }
#endif

bool is_lowercase_cstr(const char *str) {
    if (*str == '\0') {
        return false;
    }

    alphacase_cmp_snippet(lowercase);

    return true;
}

bool is_uppercase_cstr(const char *str) {
    if (*str == '\0') {
        return false;
    }

    alphacase_cmp_snippet(uppercase);

    return true;
}