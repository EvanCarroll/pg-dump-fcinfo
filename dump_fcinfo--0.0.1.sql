CREATE FUNCTION dump_fcinfo()
RETURNS TABLE(
	SFRM_ValuePerCall          bool,
	SFRM_Materialize           bool,
	SFRM_Materialize_Random    bool,
	SFRM_Materialize_Preferred bool,	
	-- https://doxygen.postgresql.org/structTupleDescData.html
	FmgrInfo_fn_nargs          int, /* arguments in */
	TupleDescData_natts        int, /* columns out */
	TupleDescData_strict       bool /* columns out */
)
AS 'MODULE_PATHNAME', 'dump_fcinfo'
LANGUAGE C STRICT VOLATILE;
