Datum dump_fcinfo(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(dump_fcinfo);

#include "nodes/execnodes.h"

Datum
dump_fcinfo(PG_FUNCTION_ARGS)
{
  
	ReturnSetInfo   *rsinfo       = (ReturnSetInfo *) fcinfo->resultinfo;
	rsinfo->returnMode = SFRM_Materialize;

	MemoryContext   per_query_ctx = rsinfo->econtext->ecxt_per_query_memory;
	MemoryContext   oldcontext    = MemoryContextSwitchTo(per_query_ctx);

	Tuplestorestate *tupstore     = tuplestore_begin_heap(false, false, work_mem);
	rsinfo->setResult = tupstore;
	
	TupleDesc	      tupdesc = rsinfo->expectedDesc;
	//rsinfo->setDesc = rsinfo->expectedDesc;

	Datum values[] = {
		BoolGetDatum(false),
		BoolGetDatum(false),
		BoolGetDatum(false),
		BoolGetDatum(false),
		Int32GetDatum(0),
		Int32GetDatum(0),
		BoolGetDatum(false),
		Int32GetDatum(0)
	};
	bool nulls[sizeof(values)] = {0};

	if ( rsinfo->allowedModes & SFRM_ValuePerCall ) {
		values[0] = BoolGetDatum(1);
	}
	if ( rsinfo->allowedModes & SFRM_Materialize ) {
		values[1] = BoolGetDatum(1);
	}
	if ( rsinfo->allowedModes & SFRM_Materialize_Random ) {
		values[2] = BoolGetDatum(1);
	}
	if ( rsinfo->allowedModes & SFRM_Materialize_Preferred ) {
		values[3] = BoolGetDatum(1);
	}

	values[4] = DatumGetInt32(fcinfo->flinfo->fn_nargs);
	values[5] = DatumGetInt32(tupdesc->natts);
	
	values[6] = DatumGetInt32(fcinfo->flinfo->fn_strict);

	tuplestore_putvalues(tupstore, tupdesc, values, nulls);

	tuplestore_donestoring(tupstore);
	MemoryContextSwitchTo(oldcontext);
	return (Datum) 0;

}
