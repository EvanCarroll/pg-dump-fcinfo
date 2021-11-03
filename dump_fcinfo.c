#include "postgres.h"
#include "common/int.h"
#include "funcapi.h"

// needed for work_mem constant
#include "miscadmin.h"

PG_MODULE_MAGIC;

#include "./src/dump_fcinfo.c"
