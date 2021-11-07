#include "pg_alpha_case.h"

Datum is_lowercase(PG_FUNCTION_ARGS) {
    int input_pos = 0;
    get_input_string;

    PG_RETURN_BOOL(is_lowercase_cstr(input_cstr));
}

Datum is_uppercase(PG_FUNCTION_ARGS) {
    int input_pos = 0;
    get_input_string;

    PG_RETURN_BOOL(is_uppercase_cstr(input_cstr));
}
