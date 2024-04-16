

#ifndef ___________________________________
#define ___________________________________

#include "node.h"
#include "node_buffer.h"
#include "node_object_wrap.h"
#include "../sqlite3/sqlite3.h"
#include "../node-lib/node-value.hpp" 
#define MAX_INT_NODE_SAFE 9007199254740991
#define MAX_INT_SIGNED_NODE_SAFE -9007199254740991
#define MAX_INT_32 0x7fffffff
#define MAX_SIGNED_INT_32 -0x7fffffff

#define DATABASE_CLOSED_ERROR "The database is not open or has already been closed."
#define DATABASE_METHOD_USED_NOT_RESULT "This statement does not return data. Use run() or exec() instead."
#define DATABASE_METHOD_USED_RESULT "This statement does not return data. Use get() or all() or each() or iterate() instead."
class Database;
class DatabaseEvents;
class DatabaseFunction;
typedef struct Addon Addon;
template <class T> using CopyablePersistent = v8::Persistent<T, v8::CopyablePersistentTraits<T>>;;


typedef struct Addon {
    Database * database;
    static void Cleanup(void*data);
} Addon;









class Database : public Value::Class , node::ObjectWrap {
    private:
    bool open = false;
    bool memory = false;
    bool safe = false;
    bool transaction = false;
    bool eventMode = false;
    bool safeInts = true;
    bool safeDouble = true;
    int busyTime;
    int thread;
    int openMode;
    std::string dbName;
    int err_code;
    public:
    sqlite3 * handler;
    DatabaseEvents * event_handler;
    Value::Array * functions_defined_name;
    Database();
    Database(Addon * addon);
    ~Database();
    static void Constructor(Value::Argumants argumants);
    static void Open(Value::Argumants argumants);
    static void Exec(Value::Argumants argumants);
    static void All(Value::Argumants argumants);
    static void Each(Value::Argumants argumants);
    static void Iterate(Value::Argumants argumants);
    static void Get(Value::Argumants argumants); 
    static void Run(Value::Argumants argumants);
    static void Function(Value::Argumants argumants);
    static void AggregateFunction(Value::Argumants argumants);
    static void Extension(Value::Argumants argumants);
    static void Exists(Value::Argumants argumants); 
    static void Close(Value::Argumants argumants);
    static void Events(Value::Argumants argumants);
    static void Serialize(Value::Argumants argumants);
    static void Backup(Value::Argumants argumants);
    static void ConfigSafeMode(Value::Argumants argumants);
    static void ConfigBusyTime(Value::Argumants argumants);
    static void ConfigLimit(Value::Argumants argumants);
    static void ConfigDatabase(Value::Argumants argumants);
    static void IsOpen(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void IsMemory(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void IsSafeMode(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void IsBusyTime(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void IsThreadMode(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void IsOpenMode(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void IsDbName(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void IsTransaction(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info);
    static void IsEventMode(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info);

    static void Cleanup(void *ptr);
    static bool CheckError(int err_code);
    static bool CheckDone(int err_code);
    static Value::Object CreateObjectError(Database * db , const char * err_msg = NULL);
    static void BindParam(Database * db ,  Value param , sqlite3_stmt * stmt , bool queryMode = true);
    static Value::Object SqliteStepValueJS(Database * db , Value param ,sqlite3_stmt * stmt , bool queryMode = true);
    static void FreeBufferSerialize(char *data, void *hint);
    static int Deserialize(Database * db, v8::Local<v8::Object> buffer);
    static void SqliteRsultValueJS(sqlite3_context * ,int , v8::Local<v8::Function>,v8::Local<v8::Value>*);
};





class DatabaseFunction {
    private:
    CopyablePersistent<v8::Function> callback;
    v8::Isolate * isolate;
    bool safeInt;
    public:
    DatabaseFunction(v8::Local<v8::Function> fn , v8::Isolate * isolate , bool safe = true);
    ~DatabaseFunction();
    static void Destroy (void * self);
    static void Function(sqlite3_context * sqlite_context, int argc, sqlite3_value ** argv);
};

class CustomAggregateFunction {
    private:
    CopyablePersistent<v8::Function> callback_step;
    CopyablePersistent<v8::Function> callback_end;
    CopyablePersistent<v8::Array> array;
    v8::Isolate * isolate;
    public:
    CustomAggregateFunction(
        v8::Local<v8::Function> step ,
        v8::Local<v8::Function> end , 
        v8::Local<v8::Array> array,
        v8::Isolate * isolate
    );
    CustomAggregateFunction(
        v8::Local<v8::Function> step ,
        v8::Local<v8::Function> end ,
        v8::Isolate * isolate
    );
    ~CustomAggregateFunction();
    static void Destroy (void * self);
    static void Function(sqlite3_context * sqlite_context, int argc, sqlite3_value ** argv); 
    static void XFinal(sqlite3_context *invocation);
    static void XValue(sqlite3_context *invocation);
    static void XInverse(sqlite3_context *, int, sqlite3_value **);
};


class DatabaseEvents {
    private:
    CopyablePersistent<v8::Function> callback;
    CopyablePersistent<v8::Object> context;
    v8::Isolate * isolate;
    public:
    DatabaseEvents(v8::Local<v8::Function> callbak, v8::Local<v8::Object> context , v8::Isolate * isolate );
    ~DatabaseEvents();
    static int EventFunc(void * data,int code,const char*,const char*,const char *,const char*);
};

#endif

