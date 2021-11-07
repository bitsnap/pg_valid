#include "pg_email.h"

Datum is_email(PG_FUNCTION_ARGS) {
    int input_pos = 0;
    get_input_string;

    PG_RETURN_BOOL(is_email_cstr(input_cstr));
}
