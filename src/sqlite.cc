

#include <iostream>
#include "node.h"
#include "sqlite3/sqlite3.h"
#include "node-lib/node-value.hpp"
#include "database/sqlite-database.hpp"





void error_codes_sets(Value::Object error_codes){
    error_codes.Set( "OK", SQLITE_OK);
    error_codes.Set( "ERROR", SQLITE_ERROR);
    error_codes.Set( "INTERNAL", SQLITE_INTERNAL);
    error_codes.Set( "PERM", SQLITE_PERM);
    error_codes.Set( "ABORT", SQLITE_ABORT);
    error_codes.Set( "BUSY", SQLITE_BUSY);
    error_codes.Set( "LOCKED", SQLITE_LOCKED);
    error_codes.Set( "NOMEM", SQLITE_NOMEM);
    error_codes.Set( "READONLY", SQLITE_READONLY);
    error_codes.Set( "INTERRUPT", SQLITE_INTERRUPT);
    error_codes.Set( "IOERR", SQLITE_IOERR);
    error_codes.Set( "CORRUPT", SQLITE_CORRUPT);
    error_codes.Set( "NOTFOUND", SQLITE_NOTFOUND);
    error_codes.Set( "FULL", SQLITE_FULL);
    error_codes.Set( "CANTOPEN", SQLITE_CANTOPEN);
    error_codes.Set( "PROTOCOL", SQLITE_PROTOCOL);
    error_codes.Set( "EMPTY", SQLITE_EMPTY);
    error_codes.Set( "SCHEMA", SQLITE_SCHEMA);
    error_codes.Set( "TOOBIG", SQLITE_TOOBIG);
    error_codes.Set( "CONSTRAINT", SQLITE_CONSTRAINT);
    error_codes.Set( "MISMATCH", SQLITE_MISMATCH);
    error_codes.Set( "MISUSE", SQLITE_MISUSE);
    error_codes.Set( "NOLFS", SQLITE_NOLFS);
    error_codes.Set( "AUTH", SQLITE_AUTH);
    error_codes.Set( "FORMAT", SQLITE_FORMAT);
    error_codes.Set( "RANGE", SQLITE_RANGE);
    error_codes.Set( "NOTADB", SQLITE_NOTADB);
    error_codes.Set( "NOTICE", SQLITE_NOTICE);
    error_codes.Set( "WARNING", SQLITE_WARNING);
    error_codes.Set( "ROW", SQLITE_ROW);
    error_codes.Set( "DONE", SQLITE_DONE);
    error_codes.Set( "IOERR_READ", SQLITE_IOERR_READ);
    error_codes.Set( "IOERR_SHORT_READ", SQLITE_IOERR_SHORT_READ);
    error_codes.Set( "IOERR_WRITE", SQLITE_IOERR_WRITE);
    error_codes.Set( "IOERR_FSYNC", SQLITE_IOERR_FSYNC);
    error_codes.Set( "IOERR_DIR_FSYNC", SQLITE_IOERR_DIR_FSYNC);
    error_codes.Set( "IOERR_TRUNCATE", SQLITE_IOERR_TRUNCATE);
    error_codes.Set( "IOERR_FSTAT", SQLITE_IOERR_FSTAT);
    error_codes.Set( "IOERR_UNLOCK", SQLITE_IOERR_UNLOCK);
    error_codes.Set( "IOERR_RDLOCK", SQLITE_IOERR_RDLOCK);
    error_codes.Set( "IOERR_DELETE", SQLITE_IOERR_DELETE);
    error_codes.Set( "IOERR_BLOCKED", SQLITE_IOERR_BLOCKED);
    error_codes.Set( "IOERR_NOMEM", SQLITE_IOERR_NOMEM);
    error_codes.Set( "IOERR_ACCESS", SQLITE_IOERR_ACCESS);
    error_codes.Set( "IOERR_CHECKRESERVEDLOCK", SQLITE_IOERR_CHECKRESERVEDLOCK);
    error_codes.Set( "IOERR_LOCK", SQLITE_IOERR_LOCK);
    error_codes.Set( "IOERR_CLOSE", SQLITE_IOERR_CLOSE);
    error_codes.Set( "IOERR_DIR_CLOSE", SQLITE_IOERR_DIR_CLOSE);
    error_codes.Set( "IOERR_SHMOPEN", SQLITE_IOERR_SHMOPEN);
    error_codes.Set( "IOERR_SHMSIZE", SQLITE_IOERR_SHMSIZE);
    error_codes.Set( "IOERR_SHMLOCK", SQLITE_IOERR_SHMLOCK);
    error_codes.Set( "IOERR_SHMMAP", SQLITE_IOERR_SHMMAP);
    error_codes.Set( "IOERR_SEEK", SQLITE_IOERR_SEEK);
    error_codes.Set( "IOERR_DELETE_NOENT", SQLITE_IOERR_DELETE_NOENT);
    error_codes.Set( "IOERR_MMAP", SQLITE_IOERR_MMAP);
    error_codes.Set( "IOERR_GETTEMPPATH", SQLITE_IOERR_GETTEMPPATH);
    error_codes.Set( "IOERR_CONVPATH", SQLITE_IOERR_CONVPATH);
    error_codes.Set( "IOERR_VNODE", SQLITE_IOERR_VNODE);
    error_codes.Set( "IOERR_AUTH", SQLITE_IOERR_AUTH);
    error_codes.Set( "LOCKED_SHAREDCACHE", SQLITE_LOCKED_SHAREDCACHE);
    error_codes.Set( "BUSY_RECOVERY", SQLITE_BUSY_RECOVERY);
    error_codes.Set( "BUSY_SNAPSHOT", SQLITE_BUSY_SNAPSHOT);
    error_codes.Set( "CANTOPEN_NOTEMPDIR", SQLITE_CANTOPEN_NOTEMPDIR);
    error_codes.Set( "CANTOPEN_ISDIR", SQLITE_CANTOPEN_ISDIR);
    error_codes.Set( "CANTOPEN_FULLPATH", SQLITE_CANTOPEN_FULLPATH);
    error_codes.Set( "CANTOPEN_CONVPATH", SQLITE_CANTOPEN_CONVPATH);
    error_codes.Set( "CORRUPT_VTAB", SQLITE_CORRUPT_VTAB);
    error_codes.Set( "READONLY_RECOVERY", SQLITE_READONLY_RECOVERY);
    error_codes.Set( "READONLY_CANTLOCK", SQLITE_READONLY_CANTLOCK);
    error_codes.Set( "READONLY_ROLLBACK", SQLITE_READONLY_ROLLBACK);
    error_codes.Set( "READONLY_DBMOVED", SQLITE_READONLY_DBMOVED);
    error_codes.Set( "ABORT_ROLLBACK", SQLITE_ABORT_ROLLBACK);
    error_codes.Set( "CONSTRAINT_CHECK", SQLITE_CONSTRAINT_CHECK);
    error_codes.Set( "CONSTRAINT_COMMITHOOK", SQLITE_CONSTRAINT_COMMITHOOK);
    error_codes.Set( "CONSTRAINT_FOREIGNKEY", SQLITE_CONSTRAINT_FOREIGNKEY);
    error_codes.Set( "CONSTRAINT_FUNCTION", SQLITE_CONSTRAINT_FUNCTION);
    error_codes.Set( "CONSTRAINT_NOTNULL", SQLITE_CONSTRAINT_NOTNULL);
    error_codes.Set( "CONSTRAINT_PRIMARYKEY", SQLITE_CONSTRAINT_PRIMARYKEY);
    error_codes.Set( "CONSTRAINT_TRIGGER", SQLITE_CONSTRAINT_TRIGGER);
    error_codes.Set( "CONSTRAINT_UNIQUE", SQLITE_CONSTRAINT_UNIQUE);
    error_codes.Set( "CONSTRAINT_VTAB", SQLITE_CONSTRAINT_VTAB);
    error_codes.Set( "CONSTRAINT_ROWID", SQLITE_CONSTRAINT_ROWID);
    error_codes.Set( "NOTICE_RECOVER_WAL", SQLITE_NOTICE_RECOVER_WAL);
    error_codes.Set( "NOTICE_RECOVER_ROLLBACK", SQLITE_NOTICE_RECOVER_ROLLBACK);
    error_codes.Set( "WARNING_AUTOINDEX", SQLITE_WARNING_AUTOINDEX);
    error_codes.Set( "AUTH_USER", SQLITE_AUTH_USER);
    error_codes.Set( "OK_LOAD_PERMANENTLY", SQLITE_OK_LOAD_PERMANENTLY);

}



























void c(Value::Argumants arg){}
void m1(Value::Argumants arg){}
void is(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info){
    info.GetReturnValue().Set(true);
}



void run(v8::Local<v8::Object> exports ,v8::Local<v8::Object> module){
    Node::Isolate isolate;
    Node::Context context;
    v8::HandleScope handle_scope(isolate); 
    Value::Object node_export(exports);

    Database ezito_sqlite;
    Value::Object SqliteErrors;
    error_codes_sets(SqliteErrors);
    ezito_sqlite.SetProperty("ERROR_CODES" , SqliteErrors);

    Value::Object open_mode; 
    open_mode.Set("READONLY" , SQLITE_OPEN_READONLY);
    open_mode.Set("READWRITE" , SQLITE_OPEN_READWRITE);
    open_mode.Set("EXISTS" , (SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));
    open_mode.Set("MEMORY" , SQLITE_OPEN_MEMORY);
    open_mode.Set("FULLMUTEX" , SQLITE_OPEN_FULLMUTEX);
    open_mode.Set("NOMUTEX" , SQLITE_OPEN_NOMUTEX);
    ezito_sqlite.SetProperty("OPEN_MODE" , open_mode);

    node_export.Set("Database" , ezito_sqlite);
}

NODE_MODULE(EzitoSqlite, run)