//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#include <stdbool.h>
#include <string.h>

#include "pg_valid.h"

inline static bool is_extra_prefix_char_internal(const char *str, size_t pos, size_t prefix_len) {
    char c = str[pos];
    if (c != '_' && c != '.' && c != '-') {
        return false;
    }

    // invalid simplify warning by clang tidy
    if ((c == '_' || c == '.' || c == '-') && (pos == 0 || pos == prefix_len - 1)) {
        return false;
    }

    if (pos + 1 > prefix_len) {
        return false;
    }

    char next = str[pos + 1];
    if (!is_num_internal(next) && !is_letter_internal(next)) {
        return false;
    }

    return true;
}

bool email_domain_is_valid(const char *str) {
    if (str[0] == '\0' || str[0] == '-') {
        return false;
    }

    size_t len = strlen(str);
    if (str[len] == '-') {

        return false;
    }

    int dots = 0;
    for (size_t i = 0; i < len; i++) {
        if (is_num_internal(str[i]) ||
            is_letter_internal(str[i])) {
            continue;
        }

        if (str[i] == '-' && str[i + 1] != '-' && str[i - 1] != '-') {
            continue;
        }

        if (str[i] == '.') {
            dots++;
            continue;
        }

        return false;
    }

    // at least two symbols per dot and two at the end, naive check

    if (dots == 0) {
        return false;
    }

    if (len < (dots * 2 + dots + 2)) {
        return false;
    }

    return true;
}

bool email_prefix_is_valid(const char *str, size_t prefix_len) {

    for (size_t i = 0; i < prefix_len; i++) {
        if (!is_num_internal(str[i]) &&
            !is_letter_internal(str[i]) &&
            !is_extra_prefix_char_internal(str, i, prefix_len)) {

            return false;
        }
    }

    return true;
}

size_t email_prefix_len(const char *str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '@') {
            if (str[i + 1] == '\0') {
                return -1;
            }

            return i;
        }
    }

    return -1;
}

// NOTE: doesn't support xn-- domains

bool is_email_cstr(const char *str) {
    size_t prefix_len = email_prefix_len(str);
    if (prefix_len < 0) {
        return false;
    }

    if (str[prefix_len + 1] == '\0') {
        return false;
    }


    if (!email_prefix_is_valid(str, prefix_len)) {
        return false;
    }

    if (!email_domain_is_valid(str + prefix_len + 1)) {
        return false;
    }

    return true;
}
