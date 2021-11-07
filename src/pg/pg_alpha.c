#include "pg_alpha.h"

Datum is_num_extra(PG_FUNCTION_ARGS) {
    int input_pos = 0;
    get_input_string;

    int extra_pos = 1;
    input_extra;

    PG_RETURN_BOOL(is_num_extra_cstr(input_cstr, input_extra_cstr));
}

Datum is_alpha_extra(PG_FUNCTION_ARGS) {
    int input_pos = 0;
    get_input_string;

    int extra_pos = 1;
    input_extra;

    PG_RETURN_BOOL(is_alpha_extra_cstr(input_cstr, input_extra_cstr));
}

Datum is_alnum_extra(PG_FUNCTION_ARGS) {
    int input_pos = 0;
    get_input_string;

    int extra_pos = 1;
    input_extra;

    PG_RETURN_BOOL(is_alnum_extra_cstr(input_cstr, input_extra_cstr));
}
