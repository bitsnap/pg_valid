MODULE_big = pg_valid
EXTENSION = pg_valid

CONFIG := release

DATA := sql/pg_valid--1.0.sql
REGRESS = regression

SQL_CONCAT := $(shell cat sql/src/*.sql > sql/pg_valid--1.0.sql)

c_files := $(wildcard src/pg/*.c src/*.c)
OBJS := $(patsubst %.c,%.o,$(c_files))

ifndef PG_CONFIG
	PG_CONFIG := pg_config
endif
PGXS := $(shell $(PG_CONFIG) --pgxs)

SHLIB_LINK := -licuuc

# # C flags
override CFLAGS := -Wall -Wpointer-arith \
                   -Werror=vla -Wendif-labels \
                   -Wmissing-format-attribute -Wimplicit-fallthrough=3 \
                   -Wformat-security -fno-strict-aliasing -fwrapv -fexcess-precision=standard \
                   -Wno-format-truncation -Wno-stringop-truncation -fPIC -std=gnu99

ifeq ($(CONFIG),debug)
	PG_CFLAGS += -g -Og
else
	PG_CFLAGS += -O3 -m64 -mfpmath=sse -ftree-vectorize -msse2 -march=native
endif

include $(PGXS)
