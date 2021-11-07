#ifndef PG_HTML_H
#define PG_HTML_H

#include <postgres.h>
#include <port.h>
#include <utils/builtins.h>

#include "../pg_valid.h"

Datum is_html_escaped(PG_FUNCTION_ARGS);

#endif