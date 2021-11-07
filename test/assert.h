//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#ifndef ASSERT_H
#define ASSERT_H

#include <string.h>

#define SRC (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

void assert(char *file, const char *func, int result, char *msg);

#define ASSERT(res, msg) assert(SRC, __FUNCTION__, res, msg)

void suite(char *file, const char *func);

#define SUITE suite(SRC, __FUNCTION__)

void alpha_test();

void alpha_case_test();

void email_test();

void html_test();

void num_test();

void ws_test();

#endif
