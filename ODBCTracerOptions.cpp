
#include "stdafx.h"
#include "odbctracer.h"
#include "sql.h"
#include "sqlext.h"

#define TraceFuncOption(s, id) init(#s, id)

void ODBCTraceOptions::init(const char *fn, int fid)
{
	//First fill the functionname 2 functionid hashtable...
	fn2id.insert(CHAR2FuncSwitchMAP::value_type(fn, fid));
	//vector containing all functionnames
	keys.insert(keys.end(), fn);
	//initialize all functions for logging
	setLogFunction(fn, true); 
}

ODBCTraceOptions::ODBCTraceOptions() : fileloggingactivated(true)
{
	TraceFuncOption(TraceSQLPrepare, SQL_API_SQLPREPARE);
	TraceFuncOption(TraceSQLFreeStmt, SQL_API_SQLFREESTMT);

	/*TraceFuncOption(TraceSQLDataSources, SQL_API_SQLDATASOURCES);
	TraceFuncOption(TraceSQLAllocHandleStd, SQL_API_SQLALLOCHANDLESTD);
	TraceFuncOption(TraceSQLTables, SQL_API_SQLTABLES);
	TraceFuncOption(TraceSQLColumns, SQL_API_SQLCOLUMNS);
	TraceFuncOption(TraceSQLStatistics, SQL_API_SQLSTATISTICS);
	TraceFuncOption(TraceSQLTablePrivileges, SQL_API_SQLTABLEPRIVILEGES);
	TraceFuncOption(TraceSQLColumnPrivileges, SQL_API_SQLCOLUMNPRIVILEGES);
	TraceFuncOption(TraceSQLSpecialColumns, SQL_API_SQLSPECIALCOLUMNS);
	TraceFuncOption(TraceSQLPrimaryKeys, SQL_API_SQLPRIMARYKEYS);
	TraceFuncOption(TraceSQLForeignKeys, SQL_API_SQLFOREIGNKEYS);
	TraceFuncOption(TraceSQLProcedures, SQL_API_SQLPROCEDURES);
	TraceFuncOption(TraceSQLProcedureColumns, SQL_API_SQLPROCEDURECOLUMNS);
	TraceFuncOption(TraceSQLConnect, SQL_API_SQLCONNECT);
	TraceFuncOption(TraceSQLDriverConnect, SQL_API_SQLDRIVERCONNECT);
	TraceFuncOption(TraceSQLBrowseConnect, SQL_API_SQLBROWSECONNECT);
	TraceFuncOption(TraceSQLDisconnect, SQL_API_SQLDISCONNECT);
	TraceFuncOption(TraceSQLEndTran, SQL_API_SQLENDTRAN);
	TraceFuncOption(TraceSQLTransact, SQL_API_SQLTRANSACT);
	TraceFuncOption(TraceSQLNumResultCols, SQL_API_SQLNUMRESULTCOLS);
	TraceFuncOption(TraceSQLDescribeCol, SQL_API_SQLDESCRIBECOL);
	TraceFuncOption(TraceSQLColAttribute, SQL_API_SQLCOLATTRIBUTE);
	TraceFuncOption(TraceSQLColAttributes, SQL_API_SQLCOLATTRIBUTES);
	TraceFuncOption(TraceSQLBindCol, SQL_API_SQLBINDCOL);
	TraceFuncOption(TraceSQLFetch, SQL_API_SQLFETCH);
	TraceFuncOption(TraceSQLGetData, SQL_API_SQLGETDATA);
	TraceFuncOption(TraceSQLMoreResults, SQL_API_SQLMORERESULTS);
	TraceFuncOption(TraceSQLRowCount, SQL_API_SQLROWCOUNT);
	TraceFuncOption(TraceSQLExtendedFetch, SQL_API_SQLEXTENDEDFETCH);
	TraceFuncOption(TraceSQLFetchScroll, SQL_API_SQLFETCHSCROLL);
	TraceFuncOption(TraceSQLSetConnectOption, SQL_API_SQLSETCONNECTOPTION);
	TraceFuncOption(TraceSQLGetConnectOption, SQL_API_SQLGETCONNECTOPTION);
	TraceFuncOption(TraceSQLSetStmtOption, SQL_API_SQLSETSTMTOPTION);
	TraceFuncOption(TraceSQLGetStmtOption, SQL_API_SQLGETSTMTOPTION);
	TraceFuncOption(TraceSQLSetEnvAttr, SQL_API_SQLSETENVATTR);
	TraceFuncOption(TraceSQLGetEnvAttr, SQL_API_SQLGETENVATTR);
	TraceFuncOption(TraceSQLSetConnectAttr, SQL_API_SQLSETCONNECTATTR);
	TraceFuncOption(TraceSQLGetConnectAttr, SQL_API_SQLGETCONNECTATTR);
	TraceFuncOption(TraceSQLSetStmtAttr, SQL_API_SQLSETSTMTATTR);
	TraceFuncOption(TraceSQLGetStmtAttr, SQL_API_SQLGETSTMTATTR);
	TraceFuncOption(TraceSQLBindParameter, SQL_API_SQLBINDPARAMETER);
	TraceFuncOption(TraceSQLDescribeParam, SQL_API_SQLDESCRIBEPARAM);
	TraceFuncOption(TraceSQLParamOptions, SQL_API_SQLPARAMOPTIONS);
	TraceFuncOption(TraceSQLNumParams, SQL_API_SQLNUMPARAMS);
	TraceFuncOption(TraceSQLSetScrollOptions, SQL_API_SQLSETSCROLLOPTIONS);
	TraceFuncOption(TraceSQLExecute, SQL_API_SQLEXECUTE);
	TraceFuncOption(TraceSQLExecDirect, SQL_API_SQLEXECDIRECT);
	TraceFuncOption(TraceSQLNativeSql, SQL_API_SQLNATIVESQL);
	TraceFuncOption(TraceSQLParamData, SQL_API_SQLPARAMDATA);
	TraceFuncOption(TraceSQLPutData, SQL_API_SQLPUTDATA);
	TraceFuncOption(TraceSQLCancel, SQL_API_SQLCANCEL);
	TraceFuncOption(TraceSQLAllocEnv, SQL_API_SQLALLOCENV);
	TraceFuncOption(TraceSQLFreeEnv, SQL_API_SQLFREEENV);
	TraceFuncOption(TraceSQLAllocConnect, SQL_API_SQLALLOCCONNECT);
	TraceFuncOption(TraceSQLFreeConnect, SQL_API_SQLFREECONNECT);
	TraceFuncOption(TraceSQLAllocStmt, SQL_API_SQLALLOCSTMT);
	TraceFuncOption(TraceSQLAllocHandle, SQL_API_SQLALLOCHANDLE);
	TraceFuncOption(TraceSQLFreeHandle, SQL_API_SQLFREEHANDLE);
	TraceFuncOption(TraceSQLSetCursorName, SQL_API_SQLSETCURSORNAME);
	TraceFuncOption(TraceSQLGetCursorName, SQL_API_SQLGETCURSORNAME);
	TraceFuncOption(TraceSQLSetPos, SQL_API_SQLSETPOS);
	TraceFuncOption(TraceSQLBulkOperations, SQL_API_SQLBULKOPERATIONS);
	TraceFuncOption(TraceSQLCloseCursor, SQL_API_SQLCLOSECURSOR);
	TraceFuncOption(TraceSQLGetInfo, SQL_API_SQLGETINFO);
	TraceFuncOption(TraceSQLGetTypeInfo, SQL_API_SQLGETTYPEINFO);
	TraceFuncOption(TraceSQLGetFunctions, SQL_API_SQLGETFUNCTIONS);
	TraceFuncOption(TraceSQLGetDiagField, SQL_API_SQLGETDIAGFIELD);
	TraceFuncOption(TraceSQLGetDiagRec, SQL_API_SQLGETDIAGREC);
	TraceFuncOption(TraceSQLError, SQL_API_SQLERROR);
	TraceFuncOption(TraceSQLCopyDesc, SQL_API_SQLCOPYDESC);*/

}

bool ODBCTraceOptions::logFunction(int functionid)
{
	INT2FuncSwitchMAP::iterator it = options.find(functionid);
	if (it != options.end())
		return (*it).second;

	return false;
}

bool ODBCTraceOptions::logFunction(const char *function)
{
	return logFunction(ODBCTraceOptions::FN2ID(function));
}

CHAR2FuncSwitchMAP ODBCTraceOptions::fn2id;
void ODBCTraceOptions::setLogFunction(const char *function, bool log)
{
	std::pair<INT2FuncSwitchMAP::iterator, bool> ret = options.insert(INT2FuncSwitchMAP::value_type(ODBCTraceOptions::FN2ID(function), log));
	if (!ret.second)
		(*ret.first).second = log;

}

int ODBCTraceOptions::FN2ID(const char *n)
{
	CHAR2FuncSwitchMAP::iterator it = fn2id.find(n);
	if (it != fn2id.end())
		return (*it).second;
	return -1;
}
