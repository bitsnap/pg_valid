//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#ifndef PG_ALPHA_CASE_H
#define PG_ALPHA_CASE_H

#include <postgres.h>
#include <port.h>
#include <utils/builtins.h>

#include "../pg_valid.h"

Datum is_lowercase(PG_FUNCTION_ARGS);

Datum is_uppercase(PG_FUNCTION_ARGS);

#endif
