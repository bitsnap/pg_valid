//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#ifndef PG_WS_H
#define PG_WS_H

#include <postgres.h>
#include <port.h>
#include <utils/builtins.h>

#include "../pg_valid.h"

Datum not_blank(PG_FUNCTION_ARGS);
Datum trim_ws_extra(PG_FUNCTION_ARGS);

#endif