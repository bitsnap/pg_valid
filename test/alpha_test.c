//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#include "pg_valid.h"
#include "assert.h"

void test_is_alpha() {
    ASSERT(is_alpha_cstr("") == 0, "empty");
    ASSERT(is_alpha_cstr("a1") == 0, "a1");
    ASSERT(is_alpha_cstr("a ") == 0, "'a '");
    ASSERT(is_alpha_cstr("1a") == 0, "1a");
    ASSERT(is_alpha_cstr("abc"), "abc");
}

void test_is_alpha_extra() {
    ASSERT(is_alpha_extra_cstr("", "") == 0, "empty");
    ASSERT(is_alpha_extra_cstr("a1", "") == 0, "a1");
    ASSERT(is_alpha_extra_cstr("a1", "1"), "a1");
    ASSERT(is_alpha_extra_cstr("a ", "") == 0, "'a ' n");
    ASSERT(is_alpha_extra_cstr("a ", " "), "'a ' p");
    ASSERT(is_alpha_extra_cstr(" a 1", " 1"), "' a 1'");
    ASSERT(is_alpha_extra_cstr("1a", "") == 0, "1a");
}

void test_is_alpha_unicode() {
    ASSERT(is_alpha_cstr("") == 0, "empty");
    ASSERT(is_alpha_cstr("Ï1") == 0, "a1");
    ASSERT(is_alpha_cstr("Ï ") == 0, "'a '");
    ASSERT(is_alpha_cstr("1Ï") == 0, "1a");
    ASSERT(is_alpha_cstr("Ïbc"), "abc"); // Ï
}

void test_is_alpha_unicode_extra() {
    ASSERT(is_alpha_extra_cstr("", "") == 0, "empty");
    ASSERT(is_alpha_extra_cstr("Ï1", "") == 0, "a1");
    ASSERT(is_alpha_extra_cstr("Ï ", "") == 0, "'a '");
    ASSERT(is_alpha_extra_cstr("1Ï", "") == 0, "1a");
    ASSERT(is_alpha_extra_cstr("Ïbc", ""), "abc"); // Ï
    ASSERT(is_alpha_extra_cstr("Ïb-c.c", "-."), "abc"); // Ï
    ASSERT(is_alpha_extra_cstr("Ïb-c.c•", "-.•"), "abc");
    ASSERT(is_alpha_extra_cstr("что-то там•", "- ") == 0, "что-то там•");
    ASSERT(is_alpha_extra_cstr("что-то там•", "- •"), "что-то там•");
}

void test_is_num() {
    ASSERT(is_num_cstr("") == 0, "empty");
    ASSERT(is_num_cstr("1234"), "1234");
    ASSERT(is_num_cstr("1234 ") == 0, "'1234 '");
    ASSERT(is_num_cstr(" 1234") == 0, "' 1234'");
    ASSERT(is_num_cstr(" 1 ") == 0, "' 1 '");
}

void test_is_num_extra() {
    ASSERT(is_num_extra_cstr("", "") == 0, "empty");
    ASSERT(is_num_extra_cstr("1234a", "a"), "1234");
    ASSERT(is_num_extra_cstr("1234", ""), "1234");
    ASSERT(is_num_extra_cstr("1234", " "), "1234");
    ASSERT(is_num_extra_cstr("", " ") == 0, "1234");
}

void test_is_num_unicode_extra() {
    ASSERT(is_num_extra_cstr("", "") == 0, "empty");
    ASSERT(is_num_extra_cstr("1234a", "") == 0, "1234");
    ASSERT(is_num_extra_cstr("1234a", "a"), "1234");
    ASSERT(is_num_extra_cstr("1234", ""), "1234");
    ASSERT(is_num_extra_cstr("1234 ", " "), "1234");
    ASSERT(is_num_extra_cstr("12 34", " "), "1234");
    ASSERT(is_num_extra_cstr("", " ") == 0, "1234");
    ASSERT(is_num_extra_cstr("12ب34", "بذ"), "1234");
    ASSERT(is_num_extra_cstr("ذ12ب34", "بذ"), "1234");
}

void test_is_alnum() {
    ASSERT(is_alnum_cstr("") == 0, "empty");
    ASSERT(is_alnum_cstr("1234"), "1234");
    ASSERT(is_alnum_cstr("1234 ") == 0, "'1234 '");
    ASSERT(is_alnum_cstr(" 1234") == 0, "' 1234'");
    ASSERT(is_alnum_cstr(" 1 ") == 0, "' 1 '");
    ASSERT(is_alnum_cstr("a ") == 0, "'a '");
    ASSERT(is_alnum_cstr("a1"), "a1");
    ASSERT(is_alnum_cstr("1a"), "1a");
    ASSERT(is_alnum_cstr("abc"), "abc");
}

void test_is_alnum_extra() {
    ASSERT(is_alnum_extra_cstr("", "") == 0, "empty");
    ASSERT(is_alnum_extra_cstr("1234-a", "-"), "1234");
    ASSERT(is_alnum_extra_cstr("1234 ", "") == 0, "'1234 '");
}


void test_is_alnum_unicode_extra() {
    ASSERT(is_alnum_extra_cstr("", "") == 0, "empty");
    ASSERT(is_alnum_extra_cstr("1234", ""), "1234");
    ASSERT(is_alnum_extra_cstr("Ï1234 ", "") == 0, "'1234 '");
    ASSERT(is_alnum_extra_cstr(" Ï1234", "") == 0, "' 1234'");
    ASSERT(is_alnum_extra_cstr(" 1 ", "") == 0, "' 1 '");
    ASSERT(is_alnum_extra_cstr("Ï ", "") == 0, "'a '");
    ASSERT(is_alnum_extra_cstr("Ïa1", ""), "a1");
    ASSERT(is_alnum_extra_cstr("1Ï", ""), "1a");
    ASSERT(is_alnum_extra_cstr("Ïbc123•", "•"), "abc123");
    ASSERT(is_alnum_extra_cstr("Ïbc123•", "-•"), "abc123");
    ASSERT(is_alnum_extra_cstr("Ïbc123•", "") == 0, "abc123");
}

void alpha_test() {
    SUITE;

    test_is_alpha();
    test_is_alpha_extra();
    test_is_alpha_unicode();
    test_is_alpha_unicode_extra();

    test_is_num();
    test_is_num_extra();
    test_is_num_unicode_extra();

    test_is_alnum();
    test_is_alnum_extra();
    test_is_alnum_unicode_extra();
}