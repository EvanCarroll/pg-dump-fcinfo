EXTENSION = dump_fcinfo
MODULE_big = dump_fcinfo
DATA = dump_fcinfo--0.0.1.sql
OBJS = dump_fcinfo.o 
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
$(OBJS): CFLAGS += $(PERMIT_DECLARATION_AFTER_STATEMENT)