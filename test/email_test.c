//
//
//

#include "pg_valid.h"
#include "assert.h"

void email_test() {
    SUITE;
    ASSERT(is_email_cstr("") == 0, "''");
    ASSERT(is_email_cstr("abc@net.com"), "abc@net.com");
    ASSERT(is_email_cstr("abc@ne.co"), "abc@ne.co");
    ASSERT(is_email_cstr("abc@ne.ko.co"), "abc@ne.co.co");
    ASSERT(is_email_cstr("ab-c@ne.ko"), "ab-c@ne.co.co");
    ASSERT(is_email_cstr("ab-.c@ne.ko.c") == 0, "ab-.c@ne.ko.c");
    ASSERT(is_email_cstr("abc@ne.ko.c") == 0, "abc@ne.co.c");
    ASSERT(is_email_cstr("abc") == 0, "abc");
    ASSERT(is_email_cstr("abc@") == 0, "abc@");
    ASSERT(is_email_cstr("abc@c") == 0, "abc@c");
    ASSERT(is_email_cstr("-abc@ne.ko") == 0, "-abc@ne.ko");
    ASSERT(is_email_cstr("abc-@ne.ko") == 0, "abc-@ne.ko");
    ASSERT(is_email_cstr("abc.@ne.ko") == 0, "abc--@ne.ko");
    ASSERT(is_email_cstr("ab--c@ne.ko") == 0, "abc-@ne.ko");
}