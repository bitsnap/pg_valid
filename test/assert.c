//
// Copyright (c) 2008-2021 Yuriy Yarosh
//

#include <stdio.h>

void assert(char *file, const char *func, int result, char *msg) {
    if (result == 0) {
        fprintf(stderr, "%s - %s: %s\n", file, func, msg);
    }
}

void suite(char *file, const char *func) {
    fprintf(stderr, "%s\n", func);
}
