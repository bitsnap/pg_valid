//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#include <stdbool.h>
#include <string.h>

inline static bool is_ws(const char *c, bool with_newline_tabs) {
    if (!with_newline_tabs) {
        return *c == ' ';
    }

    return *c == ' ' || *c == '\n' || *c == '\t' || *c == '\r';
}

size_t skip_ws_cstr(const char *str, bool suffix, bool with_newline_tabs) {
    if (*str == '\0') {
        return 0;
    }

    size_t i = 0;

    if (!suffix) {
        for (; str[i] != '\0' && is_ws(str + i, with_newline_tabs); i++);
        if (str[i] == '\0') {
            return -1;
        }

        return i;
    }

    i = strlen(str) - 1;
    for (; i != 0 && is_ws(str + i, with_newline_tabs); i--);
    if (is_ws(str + i, with_newline_tabs)) {
        return -1;
    }

    return i + 1;
}

bool not_blank_cstr(const char *str) {
    size_t pos = skip_ws_cstr(str, false, true);
    if (pos == -1) {
        return false;
    }

    return str[pos] != '\0';
}
