//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#include <stdbool.h>
#include <string.h>

#include <unicode/uchar.h>
#include <unicode/utypes.h>
#include <unicode/ucnv.h>

#include "pg_valid.h"

bool unicode_check_extra_chars(const UChar32 c, const char *chars) {
    if (*chars == '\0') {
        return false;
    }

    UErrorCode err = U_ZERO_ERROR;
    UConverter *conv = ucnv_open("UTF-8", &err);
    if (!U_SUCCESS(err)) {
        return false;
    }

    const char *end = chars + strlen(chars);
    const char *curr = chars;
    while (err != U_INDEX_OUTOFBOUNDS_ERROR) {
        UChar32 extra = ucnv_getNextUChar(conv, (const char **) &curr, end, &err);
        if (!U_SUCCESS(err)) {
            break;
        }

        if (c == extra) {
            ucnv_close(conv);
            return true;
        }
    }

    ucnv_close(conv);
    return false;
}

bool alnum_unicode_internal(const char *str, bool withAlpha, bool withNum, const char *chars) {
    if (*str == '\0') {
        return false;
    }

    UErrorCode err = U_ZERO_ERROR;
    UConverter *conv = ucnv_open("UTF-8", &err);
    if (!U_SUCCESS(err)) {
        return false;
    }

    const char *end = str + strlen(str);

    int i = 0;

    const char *curr = str;
    while (err != U_INDEX_OUTOFBOUNDS_ERROR) {
        UChar32 c = ucnv_getNextUChar(conv, (const char **) &curr, end, &err);
        if (!U_SUCCESS(err)) {
            break;
        }

        i++;

        if (withAlpha && withNum) {
            if (!u_isalpha(c) && !u_isdigit(c)) {
                if (unicode_check_extra_chars(c, chars)) {
                    continue;
                }

                ucnv_close(conv);
                return false;
            }

            continue;
        }

        if (withAlpha && !u_isalpha(c)) {
            if (unicode_check_extra_chars(c, chars)) {
                continue;
            }

            ucnv_close(conv);
            return false;
        }

        if (withNum && !u_isdigit(c)) {
            if (unicode_check_extra_chars(c, chars)) {
                continue;
            }

            ucnv_close(conv);
            return false;
        }
    }

    ucnv_close(conv);
    return true;
}


bool check_extra_chars(const char c, const char *chars) {
    if (chars[0] != '\0') {
        for (int j = 0; chars[j] != '\0'; j++) {
            if (c == chars[j]) {
                return true;
            }
        }
    }

    return false;
}

bool is_alnum_internal(const char *str, bool withAlpha, bool withNum, const char *chars) {
    if (*str == '\0') {
        return false;
    }

    size_t len = strlen(str);
    int i = 0;
    for (; i < len; i++) {
        if (!is_ascii(str[i])) {
            return alnum_unicode_internal(str, withAlpha, withNum, chars);
        }

        if (withAlpha && withNum) {
            if (!is_letter_internal(str[i]) && !is_num_internal(str[i])) {
                if (check_extra_chars(str[i], chars)) {
                    continue;
                }

                return false;
            }

            continue;
        }

        if (withAlpha && !is_letter_internal(str[i])) {
            if (check_extra_chars(str[i], chars)) {
                continue;
            }

            return false;
        }

        if (withNum && !is_num_internal(str[i])) {
            if (check_extra_chars(str[i], chars)) {
                continue;
            }

            return false;
        }
    }

    return true;
}

bool is_alnum_cstr(const char *str) {
    return is_alnum_internal(str, true, true, "");
}

bool is_alnum_extra_cstr(const char *str, const char *chars) {
    return is_alnum_internal(str, true, true, chars);
}

bool is_alpha_cstr(const char *str) {
    return is_alnum_internal(str, true, false, "");
}

bool is_alpha_extra_cstr(const char *str, const char *chars) {
    return is_alnum_internal(str, true, false, chars);
}

bool is_num_cstr(const char *str) {
    return is_alnum_internal(str, false, true, "");
}

bool is_num_extra_cstr(const char *str, const char *chars) {
    return is_alnum_internal(str, false, true, chars);
}
