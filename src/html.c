//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#include <stdbool.h>
#include <string.h>

#include "pg_valid.h"

bool valid_escape(const char *str, size_t len) {
    int letters = 0;


    for (int i = 0; i < len; i++) {
        char c = str[i];

        if (is_letter_internal(c)) {
            letters++;
            continue;
        }

        if (c == ';') {
            break;
        }

        return false;
    }

    if (letters < 32) {
        return true;
    }

    return false;
}


bool is_html_escaped_cstr(const char *str) {
    size_t len = strlen(str);
    if (len == 0) {
        return true;
    }

    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (c == '<' || c == '>' || c == '\'' || c == '"') {
            return false;
        }

        if (c == '&') {
            if (valid_escape(str + i + 1, len)) {
                continue;
            }

            return false;
        }
    }

    return true;
}
