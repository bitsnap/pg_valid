//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#include "pg_valid.h"
#include "assert.h"

void test_skip_ws() {
    ASSERT(skip_ws_cstr("a", false, false) == 0, "failed skipping");
    ASSERT(skip_ws_cstr("  a ", false, false) == 2, "'  a '");
    ASSERT(skip_ws_cstr("  a", false, false) == 2, "'  a'");
    ASSERT(skip_ws_cstr("   ab ", false, false) == 3, "'   ab '");

    ASSERT(skip_ws_cstr("a ", true, false) == 1, "'a ");
    ASSERT(skip_ws_cstr(" a  ", true, false) == 2, "' a  ");
}

void test_not_blank() {
    ASSERT(not_blank_cstr("") == 0, "''");
    ASSERT(not_blank_cstr("\t\n\r  ") == 0, "'\\t\\n\\r  '");
    ASSERT(not_blank_cstr("\t\n\r  a"), "'\\t\\n\\r  a'");
    ASSERT(not_blank_cstr("a\t\n\r  "), "'a\\t\\n\\r  '");
    ASSERT(not_blank_cstr("a "), "'a '");
    ASSERT(not_blank_cstr(" ab"), "' ab'");
    ASSERT(not_blank_cstr(" ab "), "' ab '");
}

void ws_test() {
    SUITE;
    test_skip_ws();
    test_not_blank();
}