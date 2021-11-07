//
//
//

#include "pg_mkdir.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

Datum p_mkdir(PG_FUNCTION_ARGS) {
    int input_pos = 0;
    get_input_string;

    int l = strlen(input_cstr);
    if (l <= 0) {
        PG_RETURN_BOOL(false);
    }

    // just check .. presence, no filtering nescessary
    for (int i=0; i < l-1; i++) {
        if (input_cstr[i] == '.' && input_cstr[i+1] == '.') {
            PG_RETURN_BOOL(false);
        }
    }

    struct stat st = {0};

    if (stat(input_cstr, &st) == -1) {
        if (mkdir(input_cstr, 0700) == 0) {
            PG_RETURN_BOOL(true);
        }
    }

    PG_RETURN_BOOL(false);
}
