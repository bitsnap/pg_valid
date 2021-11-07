//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#ifndef PG_ALPHA_H
#define PG_ALPHA_H

#include <postgres.h>
#include <port.h>
#include <utils/builtins.h>

#include "../pg_valid.h"

Datum is_num_extra(PG_FUNCTION_ARGS);

Datum is_alpha_extra(PG_FUNCTION_ARGS);

Datum is_alnum_extra(PG_FUNCTION_ARGS);

#ifndef input_extra
#define input_extra \
    VarChar *input_extra_static_string = PG_GETARG_VARCHAR_P(extra_pos); \
    int input_extra_size = VARSIZE(input_extra_static_string) - VARHDRSZ; \
    char *input_extra_cstr = (char *) palloc(input_size + 1); \
    memcpy(input_extra_cstr, VARDATA(input_extra_static_string), input_extra_size); \
    input_extra_cstr[input_size] = '\0';
#endif
#endif
