//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#include "pg_html.h"

Datum is_html_escaped(PG_FUNCTION_ARGS) {
    int input_pos = 0;
    get_input_string;

    PG_RETURN_BOOL(is_html_escaped_cstr(input_cstr));
}
