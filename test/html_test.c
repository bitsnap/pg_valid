//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#include "pg_valid.h"
#include "assert.h"

void html_test() {
    SUITE;
    ASSERT(is_html_escaped_cstr(""), "''");
    ASSERT(is_html_escaped_cstr("x"), "'x'");
    ASSERT(is_html_escaped_cstr("<>") == 0, "<>");
    ASSERT(is_html_escaped_cstr("'") == 0, "'");
    ASSERT(is_html_escaped_cstr("\"a") == 0, "\"a");

    ASSERT(is_html_escaped_cstr("&") == 0, "&");
    ASSERT(is_html_escaped_cstr("a&") == 0, "a&");
    ASSERT(is_html_escaped_cstr("a&a") == 0, "a&a");
    ASSERT(is_html_escaped_cstr("&gt") == 0, "&gt");
    ASSERT(is_html_escaped_cstr("&gt-;") == 0, "&gt-;");
    ASSERT(is_html_escaped_cstr("&gt;"), "&gt;");
}
