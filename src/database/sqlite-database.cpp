
#include <iostream>
#include "sqlite-database.hpp" 
Database::~Database(){}


Database::Database(){
    Node::Isolate isolate;
    Node::Context context;
    Addon * addon = new Addon(); 
    node::AddEnvironmentCleanupHook(isolate, Database::Cleanup, addon);
    Value external(addon);
    this->SetName("Database");
    this->SetConstructor(Database::Constructor , external);
    this->SetMethod(Database::Open , "Open" , external);
    this->SetMethod(Database::Close , "Close", external);
    this->SetMethod(Database::All , "All", external);
    this->SetMethod(Database::Exec , "Exec", external);
    this->SetMethod(Database::Run , "Run", external);
    this->SetMethod(Database::Get , "Get", external); 
    this->SetMethod(Database::Exists , "Exists", external); 
    this->SetMethod(Database::Iterate , "Iterate", external);
    this->SetMethod(Database::Each , "Each", external);
    this->SetMethod(Database::Function , "Function", external);
    this->SetMethod(Database::AggregateFunction , "AggregateFunction", external);
    this->SetMethod(Database::Events , "Events", external);
    this->SetMethod(Database::Extension , "Extension", external);
    this->SetMethod(Database::Serialize , "Serialize", external);
    this->SetMethod(Database::Backup , "Backup", external);
    this->SetMethod(Database::ConfigSafeMode , "ConfigSafeMode", external);
    this->SetMethod(Database::ConfigBusyTime , "ConfigBusyTime", external);
    this->SetMethod(Database::ConfigLimit , "ConfigLimit", external);
    this->SetMethod(Database::ConfigDatabase , "ConfigDatabase", external);
    this->SetField(Database::IsOpen , NULL , "_open" , external);
    this->SetField(Database::IsMemory , NULL , "_memory" , external);
    this->SetField(Database::IsSafeMode , NULL, "_safeMode" , external);
    this->SetField(Database::IsBusyTime , NULL , "_busyTime" , external);
    this->SetField(Database::IsThreadMode , NULL , "_threadMode" , external);
    this->SetField(Database::IsOpenMode , NULL , "_openMode" , external);
    this->SetField(Database::IsDbName , NULL , "_dbName" , external);
    this->SetField(Database::IsTransaction , NULL , "_transaction" , external);
    this->SetField(Database::IsEventMode , NULL , "_eventMode" , external);
}




Database::Database(Addon * addon){
    addon->database = this; 
    this->event_handler = NULL;
    this->safe=false;
    this->open=false;
    this->memory=false;
    this->transaction=false;
    this->busyTime = 30000;
    this->openMode = 6;
    this->functions_defined_name = new Value::Array();
}



void Database::Cleanup(void * ptr){
    Addon * addon = static_cast<Addon*>(ptr);
    if(addon->database->functions_defined_name) delete static_cast<Value::Array*>(addon->database->functions_defined_name);
    if(addon->database->event_handler != NULL)delete static_cast<DatabaseEvents*>(addon->database->event_handler);
    if(addon->database->open) sqlite3_close(addon->database->handler);
    if(addon->database != NULL ) delete static_cast<Database*>(addon->database);
    delete addon;
}









void Database::Constructor(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    if(!argumants.IsConstructCall()) return Node::Throw::Exception::Constructor("Database");
    Value::Function callback(argumants[0]);
    if(!callback.IsEmpty()) callback.Call(2 , Value::Null() , Value::Null());
    Addon * addon = static_cast<Addon*>(static_cast<v8::Local<v8::External>>(Value(argumants.Data()))->Value());
    Database * db = new Database(addon);
    db->Wrap(argumants.This());
    return argumants.GetReturnValue().Set(argumants.This());
}






void Database::Backup(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::String dest_filename(argumants[0]);
    if(dest_filename.IsEmpty()) return Node::Throw::Exception::Argumants("[1]", dest_filename);

    Value::String attached_name(argumants[1]);
    if(attached_name.IsEmpty()) return Node::Throw::Exception::Argumants("[2]", attached_name);

    Value::Function callback(argumants[2]);
    if(callback.IsEmpty()) return Node::Throw::Exception::Argumants("[3]", callback);

    if( !db->open ){
        db->err_code = SQLITE_NOMEM;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_CLOSED_ERROR);
        return argumants.GetReturnValue().Set( 
            callback.Call(
                argumants.This(),
                2 , 
                error, 
                Value::Null()
            ).Cast()
        );
    }

    int err_code;
    sqlite3_int64 length;
    unsigned int flags = SQLITE_DESERIALIZE_FREEONCLOSE | SQLITE_DESERIALIZE_RESIZEABLE;
    unsigned char* data = sqlite3_serialize(db->handler, static_cast<const char*>("main"), &length, 0);
    sqlite3 * db_context;
    err_code = sqlite3_open_v2(":memory:", &db_context, 6 , NULL);
    if(Database::CheckError(err_code)){}
    err_code = sqlite3_deserialize(db_context , "main", data, length, length, flags);
    if(Database::CheckError(err_code)){
        // error 
        db->err_code = sqlite3_errcode(db_context);
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db_context));
        sqlite3_close(db_context);
        return argumants.GetReturnValue().Set(
            static_cast<v8::Local<v8::Value>>(
                callback.Call(
                    argumants.This(),
                    2 ,
                    error ,
                    Value::Null()
                )
            )
        );
    }

    sqlite3 * dest_handle;
    err_code = sqlite3_open_v2(dest_filename, &dest_handle, (SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE) , NULL);
    if(Database::CheckError( err_code)){
        // error
        sqlite3_close(db_context); 
        db->err_code = err_code;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errstr(err_code));
        return argumants.GetReturnValue().Set(
            static_cast<v8::Local<v8::Value>>(
                callback.Call(
                    argumants.This(),
                    2 ,
                    error ,
                    Value::Null()
                )
            )
        );
    }
    sqlite3_extended_result_codes(dest_handle, 1);
    sqlite3_backup * backup_handle = sqlite3_backup_init(dest_handle, "main", db_context , attached_name);
    if (backup_handle == NULL) {
        // error
        db->err_code = sqlite3_errcode(db_context);
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db_context));
        sqlite3_close(dest_handle);
        sqlite3_close(db_context);
        return argumants.GetReturnValue().Set(
            static_cast<v8::Local<v8::Value>>(
                callback.Call(
                    argumants.This(),
                    2 ,
                    error ,
                    Value::Null()
                )
            )
        );
    }
    
    int status=0;
    int counter = 1;
    do {
        status =sqlite3_backup_step(backup_handle , 1);
        int total_pages=sqlite3_backup_pagecount(backup_handle);
        int remaining_pages=sqlite3_backup_remaining(backup_handle);
        float progress = float(float(total_pages-remaining_pages) / float(total_pages) * float(100));
        callback.Call(
            4 ,
            Value::Null() ,
            Value::Number(progress).Cast(),
            Value::Number(total_pages).AutoCast() ,
            Value::Number(remaining_pages).AutoCast()
        );
        
    } while(status==SQLITE_OK||status==SQLITE_BUSY||status==SQLITE_LOCKED);
    sqlite3_backup_finish(backup_handle);
    sqlite3_close(dest_handle);
    sqlite3_close(db_context);
}


void Database::Serialize(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::String name(argumants[0]);
    if(name.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , name);

    Value::Function callback(argumants[1]);
    if(callback.IsEmpty()) return Node::Throw::Exception::Argumants("[2]" , callback);
    
    if( !db->open ){
        db->err_code = SQLITE_NOMEM;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_CLOSED_ERROR);
        return argumants.GetReturnValue().Set( 
            callback.Call(
                argumants.This(),
                2 , 
                error, 
                Value::Null()
            ).Cast()
        );
    }


    
    sqlite3_int64 length = -1;
    unsigned char* data = sqlite3_serialize(db->handler, static_cast<const char*>(name), &length, 0);

    if (!data && length) {
        Value::Object error;
        error.Set("code" , sqlite3_errcode(db->handler));
        error.Set("message" , sqlite3_errmsg(db->handler));
        return argumants.GetReturnValue().Set( 
            callback.Call(
                argumants.This(),
                2 , 
                error, 
                Value::Null()
            ).Cast()
        );
    }


    argumants.GetReturnValue().Set(
        callback.Call(
            argumants.This(),
            2,
            Value::Null(),
            node::Buffer::New(
            Node::Isolate(),
            reinterpret_cast<char*>(data),
                length ,
                Database::FreeBufferSerialize,
                NULL
            ).ToLocalChecked()
        ).Cast()
    );
   
}


void Database::FreeBufferSerialize(char * data , void *hint){
    sqlite3_free(data);

}


void Database:: Open(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());
    
    Value::String filename(argumants[0]);
    if(filename.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , filename);
    if(filename.length == 0 ) filename = ":memory:";

    Value::Object option(argumants[1]);
    if(option.IsEmpty()) return Node::Throw::Exception::Argumants("[2]" , option);

    Value::Function callback(argumants[2]);
    if(callback.IsEmpty()) return Node::Throw::Exception::Argumants("[3]" , callback);

    if(db->open){
        db->err_code = 1;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , "the database before opened /:)");
        return argumants.GetReturnValue().Set( 
            callback.Call(
                argumants.This(),
                2 , 
                error, 
                Value::Null()
            ).Cast()
        );
    }


    db->openMode = option.Get("openMode").ToNumber().CppValue();
    db->busyTime = option.Get("busyTime").ToNumber().CppValue();
    db->eventMode = option.Get("eventMode").ToBoolean().CppValue();
    db->safeInts = option.Get("safeInts").ToBoolean().CppValue();
    db->safeDouble = option.Get("safeDouble").ToBoolean().CppValue();
    db->err_code = sqlite3_initialize(); 
    
    if( Database::CheckError(db->err_code)){
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        return argumants.GetReturnValue().Set( 
            callback.Call(
                argumants.This(),
                2 , 
                error, 
                Value::Null()
            ).Cast()
        );
    }

    db -> err_code = sqlite3_open_v2(
        filename,
        &db->handler,
        db->openMode,
        NULL
    );
    
    db->memory = filename == ":memory:" && Database::CheckDone(db->err_code);
    db->open   = Database::CheckDone( db->err_code);
    db->dbName = filename;

    if( Database::CheckError(db->err_code)){
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        return argumants.GetReturnValue().Set( 
            callback.Call(
                argumants.This(),
                2 , 
                error, 
                Value::Null()
            ).Cast()
        );
    }

    db->safe = true;
    sqlite3_extended_result_codes(db->handler, 1);
    sqlite3_db_config(db->handler, SQLITE_DBCONFIG_DEFENSIVE, static_cast<int>(db->safe), NULL);
    sqlite3_busy_timeout(db->handler,static_cast<int>(db->busyTime));
    sqlite3_db_config(db->handler, SQLITE_DBCONFIG_ENABLE_LOAD_EXTENSION, 1, NULL);
    db->thread = sqlite3_threadsafe();


    Value buffer(option.Get("buffer"));
    if(node::Buffer::HasInstance(static_cast<v8::Local<v8::Value>>(buffer))){
        db->err_code = Database::Deserialize(db , static_cast<v8::Local<v8::Object>>(buffer));
        if(Database::CheckError( db->err_code)){ 
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        return argumants.GetReturnValue().Set( 
            callback.Call(
                argumants.This(),
                2 , 
                error, 
                Value::Null()
            ).Cast()
        );
        }
    }

    argumants.GetReturnValue().Set(
        callback.Call(
            argumants.This(),
            2,
            Value::Null(),
            Value::Null()
        ).Cast()
    );
}







void Database::Exec(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;

    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::String sql(argumants[0]);
    if(sql.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , sql);

    Value::Function callback(argumants[1]);
    if(callback.IsEmpty()) return Node::Throw::Exception::Argumants("[2]" , callback);

    if( !db->open ){
        db->err_code = SQLITE_NOMEM;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_CLOSED_ERROR);
        return argumants.GetReturnValue().Set( 
            callback.Call(
                argumants.This(),
                2 , 
                error, 
                Value::Null()
            ).Cast()
        );
    }

    char * err_m = NULL;
    
    db->err_code = sqlite3_exec( db->handler ,  sql , NULL ,NULL , &err_m);

    if(Database::CheckError(db->err_code)){
        sqlite3_free(err_m);
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , err_m);
        return argumants.GetReturnValue().Set( 
            callback.Call(
                argumants.This(),
                2 , 
                error, 
                Value::Null()
            ).Cast()
        ); 
    }
    
    sqlite3_free(err_m);
    return argumants.GetReturnValue().Set(
        callback.Call(
            argumants.This(),
            2 ,
            Value::Null(),
            Value::Null()
        ).Cast()
    );
}














int Database::Deserialize (Database * db, v8::Local<v8::Object> buffer){
    size_t length = node::Buffer::Length(buffer);
    unsigned char* data = (unsigned char*)sqlite3_malloc64(length);
    unsigned int flags = SQLITE_DESERIALIZE_FREEONCLOSE | SQLITE_DESERIALIZE_RESIZEABLE;
    if (db->openMode == SQLITE_OPEN_READONLY) {
        flags |= SQLITE_DESERIALIZE_READONLY;
    }
    if (length) {
        if (!data) {
            return SQLITE_NOMEM;
        }
        memcpy(data, node::Buffer::Data(buffer), length);
    }
    return sqlite3_deserialize(db->handler, "main", data, length, length, flags);
}






void Database::Run(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::String sql(argumants[0]);
    if(sql.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , sql);

    Value param(argumants[1]);
    if(!param.IsArray() && !param.IsObject()) return Node::Throw::Exception::Argumants("[2]" , Value::TypeDef("Array || Object"));

    Value::Function callback(argumants[2]);
    if(callback.IsEmpty()) return Node::Throw::Exception::Argumants("[3]" , callback);

    if(!db->open ){
        db->err_code = SQLITE_NOMEM;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_CLOSED_ERROR);
        return argumants.GetReturnValue().Set( 
            callback.Call(
                argumants.This(),
                2 , 
                error, 
                Value::Null()
            ).Cast()
        );
    }

    sqlite3_stmt * stmt;
    db->err_code = sqlite3_prepare_v2(
        db->handler,
        sql,
        -1,
        &stmt,
        NULL
    );

    
    if(Database::CheckError( db->err_code)){
        sqlite3_finalize(stmt);
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        return argumants.GetReturnValue().Set( 
            callback.Call(
                argumants.This(),
                2 , 
                error, 
                Value::Null()
            ).Cast()
        );
    }

    if(sqlite3_stmt_readonly(stmt) == 1){
        sqlite3_finalize(stmt);
        db->err_code = 1;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_METHOD_USED_RESULT);
        return argumants.GetReturnValue().Set( 
            callback.Call(
                argumants.This(),
                2 ,
                error, 
                Value::Null()
            ).Cast() 
        );
    }

    Database::BindParam(db, param, stmt ,false);

    if(Database::CheckError( db->err_code)){
        sqlite3_finalize(stmt);
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        return argumants.GetReturnValue().Set( 
            callback.Call(
                argumants.This(),
                2 ,
                error,
                Value::Null()
            ).Cast()
        );
    }

    sqlite3_mutex_enter(sqlite3_db_mutex( db->handler));
    db->err_code = sqlite3_step(stmt);
    sqlite3_mutex_leave(sqlite3_db_mutex( db->handler));
    if(!Database::CheckDone(db->err_code)) sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    Value::Object error;
    error.Set("code" , db->err_code);
    error.Set("message" , sqlite3_errmsg( db->handler));  
    Value result = Value::Null();
    if(Database::CheckError( db->err_code )){
        result = error;
    }

    return argumants.GetReturnValue().Set(
        static_cast<v8::Local<v8::Value>>(
            callback.Call(
                argumants.This(),
                2,
                result.Cast(),
                Value::Null()
            )
        )
    );
}












void Database::Exists(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::String sql(argumants[0]);
    if(sql.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , sql);

    Value param(argumants[1]);
    if(!param.IsArray() && !param.IsObject()) return Node::Throw::Exception::Argumants(
        "[2]" ,
        Value::TypeDef("Array || Object")
    );

    if( !db->open ){
        db->err_code = SQLITE_NOMEM;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_CLOSED_ERROR);
        Value::Array arr;
        arr.Push(error);
        arr.Push(Value::Null());
        return argumants.GetReturnValue().Set(arr.Cast());
    }
    
    sqlite3_stmt * stmt;
    db->err_code = sqlite3_prepare_v2(
        db->handler,
        sql,
        -1,
        &stmt,
        NULL
    );

    if(Database::CheckError( db->err_code)){
        sqlite3_finalize(stmt);
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        Value::Array arr;
        arr.Push(error);
        arr.Push(Value::Null());
        return argumants.GetReturnValue().Set(arr.Cast());
    }

    if(sqlite3_stmt_readonly(stmt) == 0){
        sqlite3_finalize(stmt);
        db->err_code =1;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_METHOD_USED_NOT_RESULT);
        Value::Array arr;
        arr.Push(error);
        arr.Push(Value::Null());
        return argumants.GetReturnValue().Set(arr.Cast());
    }

    Database::BindParam(db, param, stmt , true);

    if(Database::CheckError(db->err_code)){
        sqlite3_finalize(stmt);
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        Value::Array arr;
        arr.Push(error);
        arr.Push(Value::Null());
        return argumants.GetReturnValue().Set(arr.Cast());
    }
    sqlite3_mutex_enter(sqlite3_db_mutex( db->handler));
    db->err_code = sqlite3_step(stmt);
    if( db -> err_code == SQLITE_ROW ){
        sqlite3_mutex_leave(sqlite3_db_mutex( db->handler ));
        sqlite3_reset(stmt);
        sqlite3_finalize(stmt);
        Value::Array arr;
        arr.Push(Value::Null());
        arr.Push(Value::Boolean(true).Cast());
        return argumants.GetReturnValue().Set(arr.Cast());
    }

    sqlite3_mutex_leave(sqlite3_db_mutex( db->handler ));
    if(!Database::CheckDone(db->err_code)) sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    if(Database::CheckError( db->err_code)){
        Value::Array arr;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        arr.Push(error);
        arr.Push(Value::Null());
        return argumants.GetReturnValue().Set(arr.Cast());
    }

    Value::Array arr;
    arr.Push(Value::Null());
    arr.Push(Value::Boolean(false).Cast());
    return argumants.GetReturnValue().Set(arr.Cast());

}













void Database::Get(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::String sql(argumants[0]);
    if(sql.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , sql);

    Value param(argumants[1]);
    if(!param.IsArray() && !param.IsObject()) return Node::Throw::Exception::Argumants(
        "[2]" ,
        Value::TypeDef("Array || Object")
    );

    Value::Function callback(argumants[2]);
    if(callback.IsEmpty()) return Node::Throw::Exception::Argumants("[3]" , callback);

    if( !db->open ){
        db->err_code = SQLITE_NOMEM;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_CLOSED_ERROR);
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2,
                error ,
                Value::Null()
            ).Cast()
        );
    }
    
    sqlite3_stmt * stmt;
    db->err_code = sqlite3_prepare_v2(
        db->handler,
        sql,
        -1,
        &stmt,
        NULL
    );

    if(Database::CheckError( db->err_code)){
        sqlite3_finalize(stmt);
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2,
                error ,
                Value::Null()
            ).Cast()
        );
    }
    if(sqlite3_stmt_readonly(stmt) == 0){
        sqlite3_finalize(stmt);
        db->err_code =1;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_METHOD_USED_NOT_RESULT);
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2,
                error ,
                Value::Null()
            ).Cast()
        );
    }
    Database::BindParam(db, param, stmt ,true);

    if(Database::CheckError(db->err_code)){
        sqlite3_finalize(stmt);
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2,
                error ,
                Value::Null()
            ).Cast()
        );
    }
    sqlite3_mutex_enter(sqlite3_db_mutex( db->handler));
    db->err_code = sqlite3_step(stmt);
    if( db -> err_code == SQLITE_ROW ){
        sqlite3_mutex_leave(sqlite3_db_mutex( db->handler ));
        Value::Object columns = Database::SqliteStepValueJS(db , param ,stmt , true);
        sqlite3_reset(stmt);
        sqlite3_finalize(stmt);
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2 ,
                Value::Null(),
                columns
            ).Cast()
        );
    }

    sqlite3_mutex_leave(sqlite3_db_mutex( db->handler ));
    if(!Database::CheckDone(db->err_code)) sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    if(Database::CheckError( db->err_code)){
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2,
                error ,
                Value::Null()
            ).Cast()
        );
    }

    return argumants.GetReturnValue().Set(
        callback.Call(
            argumants.This(),
            2 ,
            Value::Null() ,
            Value::Null()
        ).Cast()
    );
}
















void Database::Iterate(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::String sql(argumants[0]);
    if(sql.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , sql);

    Value param(argumants[1]);
    if(!param.IsArray() && !param.IsObject()) return Node::Throw::Exception::Argumants("[2]" , Value::TypeDef("Array || Object"));
    if( !db->open ){
        db->err_code = 1;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , "the database is not open or has already been closed");
        Value::Array arr;
        arr.Push(error);
        arr.Push(Value::Null());
        return argumants.GetReturnValue().Set(arr.Cast());
    }

    sqlite3_stmt * stmt;
    db->err_code = sqlite3_prepare_v2(
        db->handler,
        sql,
        -1,
        &stmt,
        NULL
    );
    
    if(Database::CheckError( db->err_code)){
        sqlite3_finalize(stmt);
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        Value::Array arr;
        arr.Push(error);
        arr.Push(Value::Null());
        return argumants.GetReturnValue().Set(arr.Cast());
    }


    if(sqlite3_stmt_readonly(stmt) == 0){
        sqlite3_finalize(stmt);
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_METHOD_USED_NOT_RESULT);
        Value::Array arr;
        arr.Push(error);
        arr.Push(Value::Null());
        return argumants.GetReturnValue().Set(arr.Cast());
    }

    Database::BindParam(db, param, stmt ,true);

    if(Database::CheckError( db->err_code)){
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg( db->handler)); 
        sqlite3_finalize(stmt);
        Value::Array arr;
        arr.Push(error);
        arr.Push(Value::Null());
        return argumants.GetReturnValue().Set(arr.Cast());
    }

    Value::Array arr;
    arr.Push(Value::Null());
    arr.Push(Value::Function([](Value::Argumants argumants){
        sqlite3_stmt * stmt = static_cast<sqlite3_stmt*>(static_cast<v8::Local<v8::External>>(Value(argumants.Data()))->Value());
        int err_code = sqlite3_step(stmt);
        if(err_code == SQLITE_ROW){
            Value::Object result = Database::SqliteStepValueJS(NULL , Value() , stmt , true);
            Value::Array arr;
            arr.Push(Value::Null());
            arr.Push(result);
            return argumants.GetReturnValue().Set(arr.Cast());
        }
        if(!Database::CheckDone(err_code)) sqlite3_reset(stmt);
        sqlite3_finalize(stmt);
        Value::Array arr;
        if(Database::CheckError(err_code)){
            Value::Object error;
            error.Set("code" , err_code);
            error.Set("message" , sqlite3_errstr(err_code));
            arr.Push(error);
            arr.Push(Value::Null());
        }
        else {
            arr.Push(Value::Null());
            arr.Push(Value::Null());
        }
        stmt = NULL;
        argumants.GetReturnValue().Set(arr.Cast());
    },"step", Value(stmt)));
    return argumants.GetReturnValue().Set(arr.Cast());
}










void Database::Each(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::String sql(argumants[0]);
    if(sql.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , sql);

    Value param(argumants[1]);
    if(!param.IsArray() && !param.IsObject()) return Node::Throw::Exception::Argumants("[2]" , Value::TypeDef("Array || Object"));

    Value::Function callback(argumants[2]);
    if(callback.IsEmpty()) return Node::Throw::Exception::Argumants("[3]" , callback);

    if( !db->open ){
        db->err_code = 1;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , "the database is not open or has already been closed");
        return argumants.GetReturnValue().Set(
            static_cast<v8::Local<v8::Value>>(
                callback.Call(
                    argumants.This(),
                    2 ,
                    error,
                    Value::Null()
                )
            )
        );
    }

    sqlite3_stmt * stmt;
    db->err_code = sqlite3_prepare_v2(
        db->handler,
        sql,
        -1,
        &stmt,
        NULL
    );
    
    if(Database::CheckError( db->err_code)){
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg( db->handler)); 
        sqlite3_finalize(stmt);
        return argumants.GetReturnValue().Set(
            static_cast<v8::Local<v8::Value>>(
                callback.Call(
                    argumants.This(),
                    2 ,
                    error,
                    Value::Null()
                )
            )
        );
    }
    
    if(sqlite3_stmt_readonly(stmt) == 0){
        sqlite3_finalize(stmt);
        db->err_code = 1;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_METHOD_USED_NOT_RESULT);
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2,
                error ,
                Value::Null()
            ).Cast()
        );
    }

    Database::BindParam(db, param, stmt , true);

    if(Database::CheckError( db->err_code)){
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg( db->handler)); 
        sqlite3_finalize(stmt);
        return argumants.GetReturnValue().Set(
            static_cast<v8::Local<v8::Value>>(
                callback.Call(
                    argumants.This(),
                    2 ,
                    error ,
                    Value::Null()
                )
            )
        );
    }

    long long int index=0;
    sqlite3_mutex_enter(sqlite3_db_mutex(db->handler));
    while ((db->err_code=sqlite3_step(stmt)) == SQLITE_ROW){
        sqlite3_mutex_leave(sqlite3_db_mutex(db->handler));
        int col_length = sqlite3_column_count(stmt);
        Value::Object columns = Database::SqliteStepValueJS(db , param ,stmt , true);
        Value::Boolean next(
            callback.Call(
                argumants.This(),
                3,
                Value::Null(),
                columns,
                Value::Number(index).Cast()
            )
        );
        index++;
        if(static_cast<bool>(next)==false&&!next.IsEmpty()) break;
    }

    sqlite3_mutex_leave(sqlite3_db_mutex( db->handler));
    if(!Database::CheckDone(db->err_code)) sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    if(Database::CheckError(db->err_code)){
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg( db->handler )); 
        return argumants.GetReturnValue().Set(
            static_cast<v8::Local<v8::Value>>(
                callback.Call(
                    argumants.This(),
                    2,
                    error ,
                    Value::Null()
                )
            )
        );
    }
    
    if(Database::CheckDone(db->err_code) && index == 0) { 
        return argumants.GetReturnValue().Set(
            static_cast<v8::Local<v8::Value>>(
                callback.Call(
                    argumants.This(),
                    2,
                    Value::Null(),
                    Value::Null()
                )
            )
        );
    }
}























void Database::All(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    v8::HandleScope scope(isolate);

    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::String sql(argumants[0]);
    if(sql.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , sql);

    Value param(argumants[1]);
    if(!param.IsArray() && !param.IsObject()) return Node::Throw::Exception::Argumants("[2]" , Value::TypeDef("Array || Object"));

    Value::Function callback(argumants[2]);
    if(callback.IsEmpty()) return Node::Throw::Exception::Argumants("[3]" , callback);

    if( !db->open ){
        db->err_code = SQLITE_NOMEM;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_CLOSED_ERROR);
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2 ,
                error ,
                Value::Null()
            ).Cast()
        );
    }

    sqlite3_stmt * stmt;
    db->err_code = sqlite3_prepare_v2(
        db->handler,
        sql,
        -1,
        &stmt,
        NULL
    );

    if(Database::CheckError( db->err_code)){
        sqlite3_finalize(stmt);
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg( db->handler)); 
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2,
                error ,
                Value::Null()
            ).Cast()
        );
    }
    
    if(sqlite3_stmt_readonly(stmt) == 0){
        sqlite3_finalize(stmt);
        db->err_code = 1;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_METHOD_USED_NOT_RESULT);
        return argumants.GetReturnValue().Set( 
            callback.Call(
                argumants.This(),
                2 , 
                error , 
                Value::Null()
            ).Cast() 
        );
    }

    Database::BindParam( db , param , stmt , true );
    
    if(Database::CheckError(db->err_code)){
        sqlite3_finalize(stmt);
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2,
                error ,
                Value::Null()
            ).Cast()
        );
    } 
    
    Value::Array arr;
    sqlite3_mutex_enter(sqlite3_db_mutex(db->handler));
    while ((db->err_code=sqlite3_step(stmt)) == SQLITE_ROW){
        sqlite3_mutex_leave(sqlite3_db_mutex(db->handler));
        Value::Object columns = Database::SqliteStepValueJS(db , param , stmt , true);
        arr.Push(static_cast<v8::Local<v8::Object>>(columns));
    }
    if(!Database::CheckDone(db->err_code)) sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    if(Database::CheckError(db->err_code)){
        sqlite3_mutex_leave(sqlite3_db_mutex(db->handler));
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2,
                error ,
                Value::Null()
            ).Cast()
        );
    }

    if(arr.length==0) argumants.GetReturnValue().Set(
        callback.Call(
            argumants.This(),
            2,
            Value::Null(),
            Value::Null()
        ).Cast()
    );
    else argumants.GetReturnValue().Set(
        callback.Call(
            argumants.This(),
            2,
            Value::Null(),
            arr.Cast()
        ).Cast()
    );
}





void Database::Events(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    v8::HandleScope scope(isolate);

    Value::Function callback(argumants[0]);
    if(callback.IsEmpty()) return Node::Throw::Exception::Argumants("[1]", callback);

    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    if( !db->open ){
        db->err_code = SQLITE_NOMEM;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_CLOSED_ERROR);
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2,
                error ,
                Value::Null()
            ).Cast()
        );
    }

    db->event_handler = new DatabaseEvents(callback , argumants.This(), isolate);
    db->err_code = sqlite3_set_authorizer( db->handler , DatabaseEvents::EventFunc , db->event_handler);
    
}

void Database::ConfigSafeMode(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    v8::HandleScope scope(isolate);
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::Boolean safe_mode(argumants[0]);
    if(safe_mode.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , safe_mode);
    db->safe = safe_mode.CppValue();
    sqlite3_db_config(db->handler, SQLITE_DBCONFIG_DEFENSIVE, static_cast<int>(db->safe),NULL);
}


void Database::ConfigDatabase(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    v8::HandleScope scope(isolate);
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::Number::Int32 id(argumants[0]);
    if(id.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , id);
    
    Value::Boolean mode(argumants[1]);
    if(mode.IsEmpty()) return Node::Throw::Exception::Argumants("[2]" , mode);
    if(Database::CheckError(sqlite3_db_config(db->handler, id.CppValue() , static_cast<int>(mode.CppValue()),NULL))){
        Node::Throw::Exception::Error(sqlite3_errmsg(db->handler));
    }
}



void Database::ConfigBusyTime(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    v8::HandleScope scope(isolate);
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::Number::Int32 busy(argumants[0]);
    if(busy.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , busy);
    db->busyTime = busy.CppValue();
    sqlite3_busy_timeout(db->handler,static_cast<int>(db->busyTime));
}

void Database::ConfigLimit(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    v8::HandleScope scope(isolate);
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());
    
    Value::Number::Int32 id(argumants[0]);
    if(id.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , id);

    Value::Number::Int32 new_id(argumants[1]);
    if(new_id.IsEmpty()) return Node::Throw::Exception::Argumants("[2]" , new_id);

    if(sqlite3_limit(db->handler , id.CppValue() , new_id.CppValue()) == -1){
        Node::Throw::Exception::Error("id or new val for sqlite limit config not valid");
    }
}





void Database::Close(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::Function callback(argumants[0]);
    if(callback.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , callback);

    if( !db->open ){
        db->err_code = SQLITE_NOMEM;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_CLOSED_ERROR);
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2,
                error ,
                Value::Null()
            ).Cast()
        );
    }

    db->err_code = sqlite3_close(db->handler);

    if(Database::CheckDone(db->err_code)) db->open = false;
    if(Database::CheckError( db->err_code)){
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2,
                error ,
                Value::Null()
            ).Cast()
        );
    }
    
    sqlite3_shutdown();

    return argumants.GetReturnValue().Set(
        callback.Call(
            argumants.This(),
            2 , 
            Value::Null() , 
            Value::Null()
        ).Cast()
    );
}




void  Database::IsOpen(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node :: ObjectWrap::Unwrap<Database>(argumants.This());
    return argumants.GetReturnValue().Set(db->open);
}


void Database::IsMemory(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node :: ObjectWrap::Unwrap<Database>(argumants.This());
    return argumants.GetReturnValue().Set(db->memory);
}

void Database::IsSafeMode(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node :: ObjectWrap::Unwrap<Database>(argumants.This());
    return argumants.GetReturnValue().Set(db->safe);
}

void Database::IsBusyTime(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node :: ObjectWrap::Unwrap<Database>(argumants.This());
    return argumants.GetReturnValue().Set(db->busyTime);
}

void Database::IsThreadMode(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node :: ObjectWrap::Unwrap<Database>(argumants.This());
    db->thread = sqlite3_threadsafe();
    return argumants.GetReturnValue().Set(db->thread);
}


void Database::IsOpenMode(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node :: ObjectWrap::Unwrap<Database>(argumants.This()); 
    return argumants.GetReturnValue().Set(db->openMode);
}



void Database::IsDbName(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node :: ObjectWrap::Unwrap<Database>(argumants.This()); 
    return argumants.GetReturnValue().Set(Value::String(db->dbName.data()).AutoCast());
}



void Database::IsTransaction(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node :: ObjectWrap::Unwrap<Database>(argumants.This()); 
    return argumants.GetReturnValue().Set(
        Value::Boolean(
            db->open && !static_cast<bool>(
                sqlite3_get_autocommit(db->handler)
            )
        ).Cast()
    );
}


void Database::IsEventMode(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node :: ObjectWrap::Unwrap<Database>(argumants.This()); 
    return argumants.GetReturnValue().Set(
        Value::Boolean(
            db->open && db->eventMode
        ).Cast()
    );
}




bool Database::CheckError(int err_code){
     if(    err_code !=SQLITE_DONE 
        && err_code != SQLITE_OK 
        && err_code != SQLITE_ROW ) {
        return 1;
    }
    return 0;
}




bool Database::CheckDone(int err_code){
      if(err_code == SQLITE_DONE  || err_code == SQLITE_OK){
        return 1;
    }
    return 0;
}
 



void Database::BindParam(Database * db ,  Value param , sqlite3_stmt * stmt , bool queryMode ){
    Node::Isolate isolate;
    Node::Context context;

    if(param.IsObject()){
        Value::Object obj_param(param);
        if(obj_param->GetPropertyNames(context).IsEmpty()) return;
        Value::Array  obj_param_names(obj_param->GetPropertyNames(context));
        int perot_lengh = obj_param_names.length;

        for (int ii = 0; ii < perot_lengh; ii++){
            Value bin_name(obj_param_names->Get(context , ii));
            int index_bind = sqlite3_bind_parameter_index(stmt , bin_name.ToString().CppValue());

            if(index_bind > 0){
                Value new_bind(obj_param.Get(bin_name.ToString().CppValue()));
                
                if(new_bind.IsString()){
                    db->err_code = sqlite3_bind_text(
                        stmt ,
                        index_bind,
                        new_bind.ToString().CppValue(),
                        new_bind.ToString().length,
                        NULL
                    );
                }

                else if(new_bind.IsInt()){
                    db->err_code = sqlite3_bind_int64(
                        stmt ,
                        index_bind,
                        new_bind.ToNumber().ToInt64().CppValue()
                    );  
                }

                else if(new_bind.IsNumber()){
                    db->err_code = sqlite3_bind_double(
                        stmt ,
                        index_bind,
                        new_bind.ToNumber().CppValue()
                    );
                }

                else if(new_bind.IsBoolean()){
                    db->err_code = sqlite3_bind_int(
                        stmt ,
                        index_bind,
                        new_bind.ToBoolean().CppValue() == true ? 1 : 0 
                    );
                }
                
                else if (node::Buffer::HasInstance(new_bind.Cast())) {
                    const char * data = node::Buffer::Data(new_bind.Cast()); 
                    db->err_code = sqlite3_bind_blob(
                        stmt,
                        index_bind,
                        data ? data : "",
                        node::Buffer::Length(new_bind.Cast()),
                        SQLITE_TRANSIENT 
                    );
                }

                else if(new_bind.IsNull()){
                    db->err_code = sqlite3_bind_null(
                        stmt,
                        index_bind
                    );
                }

                else {
                    db->err_code = SQLITE_TOOBIG;
                }

                if(Database::CheckError(db->err_code)){
                    return;
                }   
            }
        }
    }


    if(param.IsArray()){
        Value::Array arr(param);

        for (int i = 0; i < arr.length; i++){
            Value item(arr->Get(context , i));

            if(item.IsString()){
                db->err_code = sqlite3_bind_text(
                    stmt ,
                    i + 1,
                    item.ToString().CppValue(),
                    item.ToString().length,
                    NULL
                );
            }
            
            else if(item.IsInt()){
                db->err_code = sqlite3_bind_int64(
                    stmt ,
                    i + 1,
                    item.ToNumber().ToInt64().CppValue()
                );
            }

            else if(item.IsNumber()){
                db->err_code = sqlite3_bind_double(
                    stmt ,
                    i + 1,
                    item.ToNumber().CppValue()
                );
            }

            else if(item.IsBoolean()){
                db->err_code = sqlite3_bind_int(
                    stmt ,
                    i + 1,
                    item.ToBoolean().CppValue()
                );
            }

            else if (node::Buffer::HasInstance(item.Cast())) {
                const char * data = node::Buffer::Data(item.Cast()); 
                db->err_code = sqlite3_bind_blob(
                    stmt,
                    i + 1,
                    data ? data : "",
                    node::Buffer::Length(item.Cast()),
                    SQLITE_TRANSIENT 
                );
            }

            
            else if(item.IsNull()){
                db->err_code =sqlite3_bind_null(
                    stmt,
                    i + 1
                );
            }

            else {
                db->err_code = SQLITE_TOOBIG;
            }

            if(Database::CheckError(db->err_code)){
                return;
            }          
        }
    }

}







Value::Object Database::SqliteStepValueJS(Database * db , Value param , sqlite3_stmt * stmt , bool queryMode){
    int col_length = sqlite3_column_count(stmt);
    Value::Object columns;

    for (int counter = 0; counter < col_length; counter++){
        int col_type = sqlite3_column_type(stmt , counter);
        
        switch (sqlite3_column_type(stmt , counter)){
            case SQLITE_TEXT:
                columns.Set(
                    sqlite3_column_name(stmt, counter),
                    reinterpret_cast<const char *>(sqlite3_column_text(stmt, counter))
                );
            break;
            case SQLITE_INTEGER:
                columns.Set(
                    sqlite3_column_name(stmt,counter) ,
                    Value::Number(sqlite3_column_int64(stmt,counter), db->safeInts).Cast()
                );
            break;
            case SQLITE_FLOAT:
                columns.Set(
                    sqlite3_column_name(stmt,counter) ,
                    Value::Number::Double(sqlite3_column_double(stmt , counter), db->safeDouble).Cast()
                );
            break;
            case SQLITE_NULL:
                columns.Set(sqlite3_column_name(stmt,counter), Value::Null());
            break;
            case SQLITE_BLOB:
                columns.Set(
                    sqlite3_column_name(stmt,counter),
                    Value(
                        node::Buffer::Copy(
                            Node::Isolate() ,
                            static_cast<const char *>(sqlite3_column_blob(stmt, counter)),
                            sqlite3_column_bytes(stmt,counter)
                        )
                    ).Cast()
                );
            break;
            default:
            break;
        }
    }
    return columns;
}











void Database::AggregateFunction(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::String name(argumants[0]);
    if(name.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , name);

    Value::Array array(argumants[1]);
    if(array.IsEmpty()) return Node::Throw::Exception::Argumants("[2]" , array);

    Value::Function callback_step(argumants[2]);
    if(callback_step.IsEmpty()) return Node::Throw::Exception::Argumants("[3]" , callback_step);

    Value::Function callback_end(argumants[3]);
    if(callback_end.IsEmpty()) return Node::Throw::Exception::Argumants("[4]" , callback_end);


    if( !db->open ){
        db->err_code = SQLITE_NOMEM;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_CLOSED_ERROR);
        return argumants.GetReturnValue().Set( 
            callback_step.Call(
                argumants.This(),
                2 , 
                error, 
                Value::Null()
            ).Cast()
        );
    }



    db->err_code =  sqlite3_create_window_function(
        db->handler ,
        name,
        -1 ,
        (SQLITE_UTF8 | SQLITE_ANY),
        new CustomAggregateFunction(callback_step , callback_end , array , isolate),
        CustomAggregateFunction::Function,
        CustomAggregateFunction::XFinal,
        NULL,//CustomAggregateFunction::XValue,
        NULL, //CustomAggregateFunction::XInverse,
        CustomAggregateFunction::Destroy
    );

    if(Database::CheckError( db->err_code)){ 
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler));
        return argumants.GetReturnValue().Set(
            callback_step.Call(
                argumants.This(),
                2 ,
                error,
                Value::Null()
            ).Cast()
        );
    }
}


void Database::Function(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());

    Value::String name(argumants[0]);
    if(name.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , name);

    Value::Object option(argumants[1]);
    if(option.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , option);

    Value::Function callback(argumants[2]);
    if(callback.IsEmpty()) return Node::Throw::Exception::Argumants("[2]" , callback);


    if( !db->open ){
        db->err_code = 1;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_CLOSED_ERROR);
        return argumants.GetReturnValue().Set(
            callback.Call(2 , error , Value::Null()).Cast()
        );
    }
    int mask = SQLITE_UTF8;
    if (option.Get("deterministic").ToBoolean().CppValue()) mask |= SQLITE_DETERMINISTIC;
    if (option.Get("directOnly").ToBoolean().CppValue()) mask |= SQLITE_DIRECTONLY;
    db->err_code = sqlite3_create_function_v2(
        db->handler ,
        name,
        option.Get("argCount").ToInt().CppValue(),
        mask ,
        new DatabaseFunction(callback , isolate , option.Get("safeInt").ToBoolean().CppValue()),
        DatabaseFunction::Function,
        NULL,
        NULL,
        DatabaseFunction::Destroy
    );
    

    if(Database::CheckError(db->err_code)){
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , sqlite3_errmsg(db->handler)); 
        return argumants.GetReturnValue().Set(
            callback.Call(
                2 ,
                error,
                Value::Null()
            ).Cast()
        );
    }
}













void Database::Extension(Value::Argumants argumants){
    Node::Isolate isolate;
    Node::Context context;
    Database* db = node::ObjectWrap::Unwrap<Database>(argumants.This());
    
    Value::String filename(argumants[0]);
    if(filename.IsEmpty()) return Node::Throw::Exception::Argumants("[1]" , filename);
    
    Value::String entry_point(argumants[1]);
    if(entry_point.IsEmpty()) return Node::Throw::Exception::Argumants("[2]" , entry_point);

    Value::Function callback(argumants[2]);
    if(callback.IsEmpty()) return Node::Throw::Exception::Argumants("[3]" , callback);



    if( !db->open ){
        db->err_code = SQLITE_NOMEM;
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , DATABASE_CLOSED_ERROR);
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2 ,
                error ,
                Value::Null()
            ).Cast()
        );
    }

    sqlite3_enable_load_extension( db->handler, 1);
    char * err = NULL;
    db->err_code = sqlite3_load_extension(db->handler, filename ,entry_point , &err);
    sqlite3_enable_load_extension(db->handler, 0);


    if(Database::CheckError( db->err_code)){
        Value::Object error;
        error.Set("code" , db->err_code);
        error.Set("message" , err == NULL ? sqlite3_errmsg( db->handler ) : err);
        sqlite3_free(err);
        return argumants.GetReturnValue().Set(
            callback.Call(
                argumants.This(),
                2,
                error,
                Value::Null()
            ).Cast()
        );
    }



    return argumants.GetReturnValue().Set(
        callback.Call(
            argumants.This(),
            2,
            Value::Null(),
            Value::Null()
        ).Cast()
    );

}



void Database::SqliteRsultValueJS (
    sqlite3_context * sqlite_context , 
    int argc ,
    v8::Local<v8::Function> callback ,
    v8::Local<v8::Value> * args){

    Value result(callback->Call(Node::Context(), callback, argc, args));
    if(result.IsEmpty()) return;

    /** check return error object */
    if(result->IsObject() && !node::Buffer::HasInstance(result.Cast())){
        Value::Object error = result.ToObject(); 
        if(error.Get("message").IsString()){
            return sqlite3_result_error (
                sqlite_context,
                error.Get("message").ToString().CppValue(),
                -1
            );
        }
        if(error.Get("message").IsInt()){
            return sqlite3_result_error(
                sqlite_context,
                sqlite3_errstr(error.Get("message").ToNumber().CppValue()),
                -1
            );
        }
    }

    if (result.IsInt()){
        return sqlite3_result_int64(
            sqlite_context , 
            static_cast<Value::Number>(result).CppValue()
        ); 
    }
    
    else if ( result.IsNumber()) {
        return sqlite3_result_double(
            sqlite_context ,
            static_cast<Value::Number>(result).CppValue()
        ) ;
    }
    
    else if (result->IsString()) {
        const char * utf8 = static_cast<const char *>(result.ToString());
        return sqlite3_result_text(
            sqlite_context ,
            utf8 ,
            std::strlen(utf8),
            SQLITE_TRANSIENT
        ); 
    }

    else if (node::Buffer::HasInstance(static_cast<v8::Local<v8::Value>>(result))) {
        const char * data = node::Buffer::Data(static_cast<v8::Local<v8::Value>>(result));
        return sqlite3_result_blob (
            sqlite_context ,
            data ? data : "",
            node::Buffer::Length(static_cast<v8::Local<v8::Value>>(result)),
            SQLITE_TRANSIENT
        );
    }

    else if ( result -> IsNull() ) {
        return sqlite3_result_null ( sqlite_context );
    }
}



























DatabaseFunction::DatabaseFunction(
    v8::Local <v8::Function> fn ,
    v8::Isolate * isolate,
    bool safeInt ):callback(isolate,fn) , isolate(isolate) , safeInt(safeInt){}
DatabaseFunction::~DatabaseFunction(){}
void DatabaseFunction::Destroy(void * self){
    delete static_cast<DatabaseFunction*>(self);
}
void DatabaseFunction::Function(sqlite3_context * sqlite_context, int argc, sqlite3_value ** argv){
    DatabaseFunction * self = static_cast<DatabaseFunction*>(sqlite3_user_data(sqlite_context));
    v8::HandleScope scope(self->isolate);
    Value::Function callback(self->callback.Get(self->isolate));
    v8::Local<v8::Value> * args = new v8::Local<v8::Value>[argc+1]();
    args[0] = Value::Null();
    for (int i = 0; i < argc; i++){
        switch (sqlite3_value_type(argv[i])){
            case SQLITE_INTEGER: 
                if(Value::Number::IsInt64(sqlite3_value_int64(argv[i]), self->safeInt)){
                    args[i + 1] = Value::Number::Int64(sqlite3_value_int64(argv[i]));
                }
                else if(Value::Number::IsInt32(sqlite3_value_int64(argv[i]))){
                    args[i + 1] = Value::Number::Int32(sqlite3_value_int64(argv[i]));
                }
            break;
            case SQLITE_TEXT:
               args[i + 1] = Value::String(sqlite3_value_text(argv[i]));
            break;
            case SQLITE_FLOAT:
               args[i + 1] = Value::Number::Double(sqlite3_value_double(argv[i]));
            break;
            case SQLITE_BLOB:
                args[i + 1] = Value::Object(
                    node::Buffer::Copy(
                        self->isolate ,
                        static_cast<const char*>(sqlite3_value_blob(argv[i])),
                        sqlite3_value_bytes(argv[i])
                    )
                );
            break;
            default:
                args[i+1] = Value::Null();
            break;
        };
    }
    argc++;
    Database::SqliteRsultValueJS(sqlite_context, argc , callback , args);
    delete [] args;
}






















DatabaseEvents::DatabaseEvents(v8::Local<v8::Function> callback, v8::Local<v8::Object> context , v8::Isolate * isolate) : 
    callback(isolate,callback), context(isolate , context ),isolate(isolate){};
DatabaseEvents::~DatabaseEvents(){};
int DatabaseEvents::EventFunc(void * data,int code,const char* tname,const char*,const char *,const char*){
    DatabaseEvents * db_events = static_cast<DatabaseEvents *>(data);
    v8::HandleScope scope(db_events->isolate);
    Value::Function callback(db_events->callback.Get(db_events->isolate));
    Value::Object context  = db_events->context.Get(db_events->isolate);
    Value::Function setTimeout(Node::Context()->Global()->Get(Node::Context(),Value("setTimeout")));
    switch (code){
        case SQLITE_CREATE_TABLE:
            setTimeout.Call(context , 4 , callback , Value(1) , Value::Null() , Value("CREATE_TABLE") , Value(tname));
        break; 
        case SQLITE_INSERT:
            setTimeout.Call(context , 4 , callback , Value(1), Value::Null()  , Value("INSERT"));
        break;
        case SQLITE_SELECT: 
            setTimeout.Call(context , 4 , callback  , Value(1), Value::Null() , Value("SELECT"));
        break;
        case SQLITE_UPDATE: 
            setTimeout.Call(context , 4 , callback , Value(1) , Value::Null() , Value("UPDATE"));
        break;
        case SQLITE_DELETE:
            setTimeout.Call(context , 4 , callback , Value(1) , Value::Null() , Value("DELETE"));
        break;
        case SQLITE_ALTER_TABLE:
            setTimeout.Call(context , 4 , callback, Value(1) , Value::Null() , Value("ALTER_TABLE"));
        break; 
        case SQLITE_ERROR:
            setTimeout.Call(context , 4 , callback , Value(1) , Value::Null() , Value("ERROR"));
        break; 
        case SQLITE_CONFIG_COVERING_INDEX_SCAN:
        break;
    }
    return 0;
}






















CustomAggregateFunction::CustomAggregateFunction(
    v8::Local<v8::Function> step ,
    v8::Local<v8::Function> end ,
    v8::Local<v8::Array> array,
    v8::Isolate * isolate) :
    isolate(isolate),
    callback_step(isolate,step),
    callback_end(isolate,end),array(isolate ,array){}
CustomAggregateFunction::CustomAggregateFunction(
    v8::Local<v8::Function> step ,
    v8::Local<v8::Function> end , 
    v8::Isolate * isolate) :
    isolate(isolate),
    callback_step(isolate,step),
    callback_end(isolate,end){}
CustomAggregateFunction::~CustomAggregateFunction(){
    
}
void CustomAggregateFunction::Destroy (void * self){
    delete static_cast<CustomAggregateFunction *>(self);
}

void CustomAggregateFunction::Function(sqlite3_context * sqlite_context, int argc, sqlite3_value ** argv){
    CustomAggregateFunction * cf = static_cast<CustomAggregateFunction*>(sqlite3_user_data(sqlite_context));
    v8::HandleScope scope(cf->isolate);
    Value::Function callback(cf->callback_step.Get(cf->isolate));
    int args_plus = 2;
    int args_length = argc + args_plus;
    v8::Local<v8::Value> * args = new v8::Local<v8::Value>[args_length];
    args[0] = Value::Null();
    if(cf->array.Get(cf->isolate).IsEmpty()){
        args[1] = Value::Null();
    }
    else {
        args[1] = cf->array.Get(cf->isolate);
    }
    for (int i = 0; i < argc; i++)
    switch (sqlite3_value_type(argv[i])) {
        case SQLITE_INTEGER: 
            if(Value::Number::IsInt64(sqlite3_value_int64(argv[i]))){
                args[i + 1] = Value::Number::Int64(sqlite3_value_int64(argv[i]));
            }
            else {
                args[i + 1] = Value::Number::Int32(sqlite3_value_int64(argv[i]));
            }
        break;
        case SQLITE_TEXT:
            args[i + args_plus] = Value::String(sqlite3_value_text( argv[i]));
        break;
        case SQLITE_FLOAT:
            args[i + args_plus] = Value::Number(sqlite3_value_double( argv[i]));
        break;
        case SQLITE_BLOB:
            args[i + args_plus] = Value::Object(
                node::Buffer::Copy(
                    cf->isolate ,
                    static_cast<const char*>(sqlite3_value_blob(argv[i])),
                    sqlite3_value_bytes(argv[i])
                )
            );
        break;
        default :
            args[i + args_plus] = Value::Null();
        break;
    }
    
    Database::SqliteRsultValueJS( sqlite_context , args_length, callback , args);
    delete[] args;
}

void CustomAggregateFunction::XFinal(sqlite3_context * sqlite_context){
    CustomAggregateFunction * cf = static_cast<CustomAggregateFunction*>(sqlite3_user_data(sqlite_context));
    v8::HandleScope scope(cf->isolate);
    Value::Function callback(cf->callback_end.Get(cf->isolate));
    v8::Local<v8::Value> * args = new v8::Local<v8::Value>[1];
    if(!cf->array.Get(cf->isolate).IsEmpty()){
        args[0] = cf->array.Get(cf->isolate);
    }
    else {
        args[0] = Value::Null();
    }
    Database::SqliteRsultValueJS(sqlite_context , 1, callback , args);
    delete[] args;
}

void CustomAggregateFunction::XValue(sqlite3_context *sqlite_context){

}

void CustomAggregateFunction::XInverse(sqlite3_context *, int, sqlite3_value **){

}

