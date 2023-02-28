#if !defined(ODBCDRIVERDELEGATOR_13_06_2005_ARINIR_H)
#define ODBCDRIVERDELEGATOR_13_06_2005_ARINIR_H

#include <sstream>
#include <sqltypes.h>

#define DeclareString(s) static const char * str ## s = #s
typedef std::map<std::string, int> CHAR2FuncSwitchMAP;
typedef std::map<int, bool> INT2FuncSwitchMAP;

class Mutex
{
public:
	Mutex();
	~Mutex();
	void enter();
	void leave();
private:
	CRITICAL_SECTION CriticalSection;
};
class MutexGuard
{
public:
	MutexGuard(Mutex *mutex);
	~MutexGuard();
protected:
	MutexGuard();
	MutexGuard(const MutexGuard &);
	MutexGuard & operator = (const MutexGuard &);
	Mutex *mutex;
};

class ODBCTraceOptions
{
private:
	ODBCTraceOptions();
	static ODBCTraceOptions* unique_instance;
	static CHAR2FuncSwitchMAP fn2id;
	INT2FuncSwitchMAP options;
	void init(const char *fn, int fid);
public:
	static ODBCTraceOptions* getUniqueInstance();
	static int FN2ID(const char *n);

	bool logFunction(int functionid);
	bool logFunction(const char *function);
	void setLogFunction(const char *function, bool log);

	bool fileloggingactivated;
	std::string logfile;
	std::vector<std::string> keys;
	std::map<std::pair <int, int>, std::string> logs;
	std::map<std::pair <int, int>, std::clock_t> clocks;
};

#define ODBCTRACE_STACKSIZE 256
#define MAX_ARGUMENTS 20

enum ODBCTracer_ArgumentTypes
{
	TYP_UNKNOWN = 0,

	TYP_SQLPOINTER,
	TYP_SQLSMALLINT,
	TYP_SQLUSMALLINT,
	TYP_SQLINTEGER,
	TYP_SQLUINTEGER,

	TYP_SQLPOINTER_PTR,
	TYP_SQLCHAR_PTR,
	TYP_SQLWCHAR_PTR,
	TYP_SQLSMALLINT_PTR,
	TYP_SQLUSMALLINT_PTR,
	TYP_SQLINTEGER_PTR,
	TYP_SQLUINTEGER_PTR,

	TYP_SQLHDESC,
	TYP_SQLHSTMT,
	TYP_SQLHDBC,
	TYP_SQLHWND,
	TYP_SQLHENV,
	TYP_SQLHANDLE,

	TYP_SQLHDESC_PTR,
	TYP_SQLHSTMT_PTR,
	TYP_SQLHDBC_PTR,
	TYP_SQLHWND_PTR,
	TYP_SQLHENV_PTR,
	TYP_SQLHANDLE_PTR
};

struct ODBCTraceArgument
{
	std::string name;
	ODBCTracer_ArgumentTypes type;
	void *value;
};

struct ODBCTraceCall
{
	void insertArgument(const char *name, ODBCTracer_ArgumentTypes type, void *value); 

	std::string function_name;
	int function_id;
	int arguments_count;
	int retcode;
	bool unicode;
	ODBCTraceArgument arguments[MAX_ARGUMENTS];
};

struct ODBCTraceStack
{
	ODBCTraceStack();

	int push(ODBCTraceCall *call);
	ODBCTraceCall* pop(int index);

	Mutex lock;
	ODBCTraceCall* stack[ODBCTRACE_STACKSIZE];
};


void ODBCTrace(ODBCTraceCall *call);


#endif //#if !defined(ODBCDRIVERDELEGATOR_13_06_2005_ARINIR_H)