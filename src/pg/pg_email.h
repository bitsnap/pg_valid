#ifndef PG_EMAIL_H
#define PG_EMAIL_H

#include <postgres.h>
#include <port.h>
#include <utils/builtins.h>

#include "../pg_valid.h"

Datum is_email(PG_FUNCTION_ARGS);

#endif