//
//
//

#include "pg_valid.h"
#include "assert.h"

void test_is_uppercase() {
    ASSERT(is_uppercase_cstr("abc") == 0, "abc");
    ASSERT(is_uppercase_cstr("Abc") == 0, "Abc");
    ASSERT(is_uppercase_cstr("abC") == 0, "abC");
    ASSERT(is_uppercase_cstr("") == 0, "''");
    ASSERT(is_uppercase_cstr("aA") == 0, "aA");
    ASSERT(is_uppercase_cstr("A"), "A");
    ASSERT(is_uppercase_cstr("ABC"), "ABC");

    ASSERT(is_uppercase_cstr("Г"), "Г");
    ASSERT(is_uppercase_cstr("Ïac") == 0, "Ï");
}

void test_is_lowercase() {
    ASSERT(is_lowercase_cstr("ABC") == 0, "ABC");
    ASSERT(is_lowercase_cstr("aBC") == 0, "aBC");
    ASSERT(is_lowercase_cstr("ABc") == 0, "ABc");
    ASSERT(is_lowercase_cstr("") == 0, "''");
    ASSERT(is_lowercase_cstr("Aa") == 0, "Aa");
    ASSERT(is_lowercase_cstr("a"), "a");
    ASSERT(is_lowercase_cstr("abc"), "abc");

    ASSERT(is_lowercase_cstr("їbc"), "їbc");
    ASSERT(is_lowercase_cstr("їБЦ") == 0, "їБЦ");
}

void alpha_case_test() {
    SUITE;
    test_is_lowercase();
    test_is_uppercase();
}