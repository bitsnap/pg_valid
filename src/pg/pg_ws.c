//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#include "pg_ws.h"

Datum not_blank(PG_FUNCTION_ARGS) {
    int input_pos = 0;
    get_input_string;

    PG_RETURN_BOOL(not_blank_cstr(input_cstr));
}

const char *empty_string = "";

Datum trim_ws_extra(PG_FUNCTION_ARGS) {
    bool trim_newlines_and_tabs = PG_GETARG_BOOL(1);

    int input_pos = 0;
    get_input_string;

    size_t skip_prefix = skip_ws_cstr(input_cstr, false, trim_newlines_and_tabs);
    if (skip_prefix == -1) {
        PG_RETURN_CSTRING(empty_string);
    }

    size_t skip_suffix = skip_ws_cstr(input_cstr, true, trim_newlines_and_tabs);

    size_t result_size = input_size;

    if (skip_prefix > 0) {
        result_size = result_size - skip_prefix;
    }

    if (skip_suffix > 0) {
        result_size = result_size - (input_size - skip_suffix);
    }

    if (result_size != input_size) {
        char *result_string = (char *) palloc(result_size + 1);
        memcpy(result_string, input_cstr + skip_prefix, result_size);

        result_string[result_size] = '\0';

        pfree(input_cstr);

        PG_RETURN_CSTRING(result_string);
    }

    PG_RETURN_CSTRING(input_cstr);
}