//
//
//

#ifndef PG_VALID_H
#define PG_VALID_H

#include <stdbool.h>
#include <stddef.h>

inline bool is_ascii(const char c) {
    return (c & 128) == 0;
}

inline bool is_num_internal(const char c) {
    if (c == '\0') {
        return false;
    }

    return c >= '0' && c <= '9';
}

inline bool is_letter_internal(const char c) {
    if (c == '\0') {
        return false;
    }

    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

size_t skip_ws_cstr(const char *str, bool suffix, bool with_newline_tabs);

bool not_blank_cstr(const char *str);

bool is_lowercase_cstr(const char *str);

bool is_uppercase_cstr(const char *str);

bool is_alnum_cstr(const char *str);

bool is_alnum_extra_cstr(const char *str, const char *chars);

bool is_alpha_cstr(const char *str);

bool is_alpha_extra_cstr(const char *str, const char *chars);

bool is_num_cstr(const char *str);

bool is_num_extra_cstr(const char *str, const char *chars);

bool is_email_cstr(const char *str);

bool is_html_escaped_cstr(const char *str);

#ifndef get_input_string
#define get_input_string \
    char* input_cstr = NULL; \
    VarChar *input_string = PG_GETARG_VARCHAR_P(input_pos); \
    int input_size = VARSIZE(input_string)-VARHDRSZ; \
    input_cstr = (char *) palloc ( input_size + 1); \
    memcpy(input_cstr, VARDATA(input_string), input_size); \
    input_cstr[input_size] = '\0';
#endif
#endif
