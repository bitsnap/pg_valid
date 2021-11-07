//
//
//

#include <postgres.h>
#include <port.h>
#include <utils/builtins.h>

#include "pg/pg_alpha.h"
#include "pg/pg_email.h"
#include "pg/pg_html.h"
#include "pg/pg_ws.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(trim_ws_extra);
PG_FUNCTION_INFO_V1(not_blank);

PG_FUNCTION_INFO_V1(is_html_escaped);
PG_FUNCTION_INFO_V1(is_email);

PG_FUNCTION_INFO_V1(is_lowercase);
PG_FUNCTION_INFO_V1(is_uppercase);

PG_FUNCTION_INFO_V1(is_num_extra);
PG_FUNCTION_INFO_V1(is_alpha_extra);
PG_FUNCTION_INFO_V1(is_alnum_extra);

PG_FUNCTION_INFO_V1(p_mkdir);
