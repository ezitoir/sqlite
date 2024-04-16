

#include <cstring>
#include <iostream>
#include <string>

#include "node-value.hpp"






Value::~Value(){}
Value::Value(){
    this->val = v8::Local<v8::Value>();
}
Value::Value(void*data){
    this -> val = v8::External::New(Node::Isolate() , data);
}

Value::Value(const char * value){
    this -> val = Value::CreateValue( value); 
}

Value::Value(signed long int value){
    this -> val = Value::CreateValue( value); 
}

Value::Value(unsigned long int value):Value(){
    this -> val = Value::CreateValue( value); 
}


Value::Value(signed long long int value){
    this -> val = Value::CreateValue( value); 
}

Value::Value(unsigned long long int value){
    this -> val = Value::CreateValue( value); 
}

Value::Value(int value){
    this -> val = Value::CreateValue( value); 
}

Value::Value(double value){
    this -> val = Value::CreateValue( value); 
}
Value::Value(float value){
    this -> val = Value::CreateValue( value); 
}

Value::Value(bool value){
    this -> val = Value::CreateValue( value);
}

Value::Value(v8::Local<v8::Primitive> value){
    this -> val = value;
}

Value::Value(v8::FunctionCallback callback , const char * name , v8::Local<v8::Value> data = v8::Local<v8::Value>()){
    this -> val = Value::CreateValue(callback,name,data);
}
v8::Local<v8::Value> Value::AutoCast(){
    return this->val;
}
v8::Local<v8::Value> Value::Cast(){
    return this->val;
}



Value::Value(v8::Local<v8::Value> value) :val(value){};
Value::Value(v8::Local<v8::Object> value) :val(value.As<v8::Value>()){};
Value::Value(v8::Local<v8::Array> value) :val(value.As<v8::Value>()){};
Value::Value(v8::Local<v8::String> value) :val(value.As<v8::Value>()){};
Value::Value(v8::Local<v8::Int32> value) :val(value.As<v8::Value>()){};
Value::Value(v8::Local<v8::BigInt> value) :val(value.As<v8::Value>()){};
Value::Value(v8::Local<v8::Number> value) :val(value.As<v8::Value>()){};
Value::Value(v8::Local<v8::External> value) :val(value.As<v8::Value>()){};
Value::Value(v8::Local<v8::Boolean> value) :val(value.As<v8::Value>()){};
Value::Value(v8::Local<v8::Function> value) :val(value.As<v8::Value>()){};

Value::Value(v8::MaybeLocal<v8::Value> value){
    if( ! value.IsEmpty()){
        this -> val = value.ToLocalChecked();
    }
}


Value::Value(v8::MaybeLocal<v8::Array> value){
    if( ! value.IsEmpty()){
        this -> val = value.ToLocalChecked().As<v8::Value>();
    }
}

Value::Value(v8::MaybeLocal<v8::String> value){
    if( ! value.IsEmpty()){
        this -> val = value.ToLocalChecked().As<v8::Value>();
    }
}

Value::Value(v8::MaybeLocal<v8::Int32> value){
    if( ! value.IsEmpty()){
        this -> val = value.ToLocalChecked().As<v8::Value>();
    }
}

Value::Value(v8::MaybeLocal<v8::BigInt> value){
    if( ! value.IsEmpty()){
        this -> val = value.ToLocalChecked().As<v8::Value>();
    }
}

Value::Value(v8::MaybeLocal<v8::Boolean> value){
    if( ! value.IsEmpty()){
        this -> val = value.ToLocalChecked().As<v8::Value>();
    }
}


Value::Value(v8::MaybeLocal<v8::Object> value){
    if( ! value.IsEmpty()){
        this -> val = value.ToLocalChecked().As<v8::Value>();
    }
}

Value::Value(v8::MaybeLocal<v8::Number> value){
    if( ! value.IsEmpty()){
        this -> val = value.ToLocalChecked().As<v8::Value>();
    }
}

Value::Value(v8::MaybeLocal<v8::Function> value){
    if( ! value.IsEmpty()){
        this -> val = value.ToLocalChecked().As<v8::Value>();
    }
}

bool Value::IsBoolean (){
    return Value::ISBoolean( this->val);
}


bool Value::IsString (){
    return Value::ISString( this->val);
}

bool Value::IsInt (){
    return Value::ISInt( this->val);
}

bool Value::IsBigInt (){
    Value::Number a(this->val);
    return a.IsInt64();
}



bool Value::IsNumber (){
    Value::Number a(this->val);
    return !a.IsEmpty();
}




bool Value::IsUndefined (){
    if( !this -> val .IsEmpty()){
        return this -> val->IsUndefined();
    }
    return false;
}


bool Value::IsNull (){
    if( !this -> val .IsEmpty()){
        return this -> val->IsNull();
    }
    return false;
}

bool Value::IsFunction(){
    if( !this -> val .IsEmpty()){
        return this -> val->IsFunction();
    }
    return false;
}

bool Value::IsEmpty(){
    return this -> val.IsEmpty();
}

bool Value::IsArray(){
    return this -> val->IsArray();
}

bool Value::IsObject(){
    return this -> val->IsObject() && !this->val->IsArray();
}

bool Value::ISEmpty(v8::Local<v8::Value> value, bool * safe){
    return value.IsEmpty();
}
bool Value::ISString(v8::Local<v8::Value> value , bool * safe){
    return !value.IsEmpty() && value->IsString();
}
bool Value::ISBoolean(v8::Local<v8::Value> value , bool * safe){
    return !value.IsEmpty() &&  value->IsBoolean();
}
bool Value::ISFunction(v8::Local<v8::Value> value , bool * safe){
    return !value.IsEmpty() && value->IsFunction();
}
bool Value::ISInt(v8::Local<v8::Value> value , bool * safe){
    return !value.IsEmpty() && (value->IsInt32() || value->IsBigInt() || value->IsBigIntObject());
}
bool Value::ISBigInt(v8::Local<v8::Value> value , bool * safe){
    return !value.IsEmpty() && ( value->IsBigInt() || value->IsBigIntObject());    
}
bool Value::ISArray(v8::Local<v8::Value> value , bool * safe ){
    return !value.IsEmpty() && value->IsArray();
}
bool Value::ISNumber(v8::Local<v8::Value> value , bool * safe ){
return !value.IsEmpty() && (!value->IsInt32()&&!value->IsBigInt()&&value->IsBigIntObject()) && (value->IsNumber()||value->IsNumberObject());
}
bool Value::ISNull(v8::Local<v8::Value> value , bool * safe ){
    return !value.IsEmpty() && value->IsNull();
}
bool Value::ISUndefined(v8::Local<v8::Value> value , bool * safe){
    return !value.IsEmpty() && value->IsUndefined();
}
bool Value::ISObject(v8::Local<v8::Value> value , bool * safe){
    return !value.IsEmpty() && value->IsObject();
}


Value::operator v8::Local<v8::Value>(){ return this -> val; }
Value::operator v8::Local<v8::Array>(){ return this -> val.As<v8::Array>(); }
Value::operator v8::Local<v8::String>(){ return this -> val.As<v8::String>(); }
Value::operator v8::Local<v8::Number>(){ return this -> val.As<v8::Number>(); }
Value::operator v8::Local<v8::Object>(){ return this -> val.As<v8::Object>(); }
Value::operator v8::Local<v8::Function>(){ return this -> val.As<v8::Function>(); }
Value::operator v8::Local<v8::FunctionTemplate>(){ return this -> val.As<v8::FunctionTemplate>(); }
Value::operator v8::Local<v8::Boolean>(){ return this -> val.As<v8::Boolean>();}
Value::operator v8::Local<v8::External>(){ return this -> val.As<v8::External>(); }
Value::operator v8::Local<v8::Int32>(){ return this -> val.As<v8::Int32>(); }
Value::operator v8::Local<v8::Name>(){ return this -> val.As<v8::Name>(); }
 

Value::operator Value::String(){ return Value::String(this->val);};
Value::operator Value::Object(){ return Value::Object(this->val);};
Value::operator Value::Array(){ return Value::Array(this->val);};
Value::operator Value::Function(){ return Value::Function(this->val);};
Value::operator Value::Int(){ return Value::Int(this->val);};
Value::operator Value::BigInt(){ return Value::BigInt(this->val);};
Value::operator Value::Number(){ return Value::Number(this->val);};
Value::operator Value::Boolean(){ return Value::Boolean(this->val);};


Value::operator v8::Local<v8::Value>()const{ return this -> val; }
Value::operator v8::Local<v8::Array>()const{ return this -> val.As<v8::Array>(); }
Value::operator v8::Local<v8::String>() const{ return this -> val.As<v8::String>(); }
Value::operator v8::Local<v8::Number>()const{ return this -> val.As<v8::Number>(); }
Value::operator v8::Local<v8::Object>()const{ return this -> val.As<v8::Object>(); }
Value::operator v8::Local<v8::Function>()const{ return this -> val.As<v8::Function>(); }
Value::operator v8::Local<v8::FunctionTemplate>()const{ return this -> val.As<v8::FunctionTemplate>(); }
Value::operator v8::Local<v8::Boolean>()const{ return this -> val.As<v8::Boolean>(); }
Value::operator v8::Local<v8::Int32>()const{ return this -> val.As<v8::Int32>(); }
Value::operator v8::Local<v8::BigInt>()const{ return this -> val.As<v8::BigInt>(); }
Value::operator v8::Local<v8::External>()const{ return this -> val.As<v8::External>(); }
Value::operator v8::Local<v8::Name>()const{ return this -> val.As<v8::Name>(); } 



Value::operator Value::String() const{ return Value::String(this->val);};
Value::operator Value::Object() const{ return Value::Object(this->val);};
Value::operator Value::Array() const{ return Value::Array(this->val);};
Value::operator Value::Function() const{ return Value::Function(this->val);};
Value::operator Value::Int() const{ return Value::Int(this->val);};
Value::operator Value::BigInt() const{ return Value::BigInt(this->val);};
Value::operator Value::Number() const{ return Value::Number(this->val);};
Value::operator Value::Boolean() const{ return Value::Boolean(this->val);};


v8::Local<v8::Array> Value::ToV8Array(){
    return static_cast<v8::Local<v8::Array>>(*this);
}
v8::Local<v8::String> Value::ToV8String(){
    return static_cast<v8::Local<v8::String>>(*this);
}
v8::Local<v8::Object> Value::ToV8Object(){
    return static_cast<v8::Local<v8::Object>>(*this);
}
v8::Local<v8::Number> Value::ToV8Number(){
    return static_cast<v8::Local<v8::Number>>(*this);
}
v8::Local<v8::Int32> Value::ToV8Int(){
    return static_cast<v8::Local<v8::Int32>>(*this);
}
v8::Local<v8::Function> Value::ToV8Function(){
    return static_cast<v8::Local<v8::Function>>(*this);
}
v8::Local<v8::Boolean> Value::ToV8Boolean(){
    return static_cast<v8::Local<v8::Boolean>>(*this);
}



Value Value::operator=(v8::Local<v8::Value> value){
    this->val.Clear();
    this->val = value;
    return *this;
};
Value Value::operator=(v8::Local<v8::Array> value){
    this->val.Clear();
    this->val = value.As<v8::Value>();
    return *this;
}
Value Value::operator=(v8::Local<v8::String> value){
    this->val.Clear();
    this->val = value.As<v8::Value>();
    return *this;
};
Value Value::operator=(v8::Local<v8::Number> value){
    this->val.Clear();
    this->val = value.As<v8::Value>();
    return *this;
};
Value Value::operator=(v8::Local<v8::Object> value){
    this->val.Clear();
    this->val = value.As<v8::Value>();
    return *this;
};
Value Value::operator=(v8::Local<v8::Function> value){
    this->val.Clear();
    this->val = value.As<v8::Value>();
    return *this;
};


Value Value::operator=(v8::Local<v8::Name> value){
    this->val.Clear();
    this->val = value.As<v8::Value>();
    return *this;
};

Value Value::operator=(v8::Local<v8::Boolean> value){
    this->val.Clear();
    this->val = value.As<v8::Value>();
    return *this;
};

Value Value::operator=(v8::Local<v8::Int32> value){
    this->val.Clear();
    this->val = value.As<v8::Value>();
    return *this;
};


Value Value::operator=(Value::String value){
    this->val.Clear();
    this->val = value.Cast();
    return *this;
}

Value Value::operator=(Value::Function value){
    this->val = value.Cast();
    return *this;
}
Value Value::operator=(Value::Array value){
    this->val = value.Cast();
    return *this;
}
Value Value::operator=(Value::Object value){
    this->val = value.Cast();
    return *this;
}
Value Value::operator=(Value::Undefined value){
     this->val = value.Cast();
    return *this;
}
Value Value::operator=(Value::Null value){
    this->val = value.Cast();
    return *this;
}
Value Value::operator=(Value::Class value){
    this->val = value.Cast();
    return *this;
}

Value Value::operator=(const Value& value){
    this->val.Clear();
    this->val = value.val;
    return *this;
}

Value Value::operator=(const Value* value){
    this->val.Clear();
    this->val = value->val;
    return *this;
}



v8::Local<v8::Value> Value::operator->(){
    return this->val;
}

v8::Local<v8::Value> Value::CreateValue(const char* value){
    v8::Isolate* isolate = v8::Isolate::GetCurrent(); 
    return v8::String::NewFromUtf8( isolate ,value , v8::NewStringType::kInternalized).ToLocalChecked();
}

v8::Local<v8::Value> Value::CreateValue(int value){
    return v8::Int32::New( v8::Isolate::GetCurrent() , value);
}


v8::Local<v8::Value> Value::CreateValue(signed long int value){
    return v8::BigInt::New( v8::Isolate::GetCurrent() , value);
}

v8::Local<v8::Value> Value::CreateValue(unsigned long int value){
    return v8::BigInt::New( v8::Isolate::GetCurrent() , value);
}

v8::Local<v8::Value> Value::CreateValue(signed long long int value){
    return v8::BigInt::New( v8::Isolate::GetCurrent() , value);
}

v8::Local<v8::Value> Value::CreateValue(unsigned long long int value){
    return v8::BigInt::New( v8::Isolate::GetCurrent() , value);
}

v8::Local<v8::Value> Value::CreateValue(double value){
    return v8::Number::New( v8::Isolate::GetCurrent() , value);
}

v8::Local<v8::Value> Value::CreateValue(float value){
    return v8::Number::New( v8::Isolate::GetCurrent() ,double(value));
}
v8::Local<v8::Value> Value::CreateValue(bool value){
    return v8::Boolean::New( v8::Isolate::GetCurrent() , value);
}

v8::Local<v8::Value> Value::CreateValue(
    v8::FunctionCallback callback , 
    const char * name , 
    v8::Local<v8::Value> data = v8::Local<v8::Value>()){
        
    v8::Local<v8::FunctionTemplate> function_template = v8::FunctionTemplate::New(
        v8::Isolate::GetCurrent(),
        callback,
        data
    );
    
    v8::Local<v8::Function> function = function_template -> GetFunction(v8::Isolate::GetCurrent() -> GetCurrentContext() ).ToLocalChecked();
    if( name != 0 ) function -> SetName(Value::CreateValue(name).As<v8::String>());
    return function;
}




const char * Value::ToCppString(v8::Local<v8::String> val){
    return Value::ToCppString(val.As<v8::Value>());
}

const char * Value::ToCppString(v8::Local<v8::Value> val){
    char * result = (char *)std::malloc(sizeof(char *));
    result = NULL;
    if(!val.IsEmpty()){
        if( val->IsString()){
            v8::String::Utf8Value value( v8::Isolate::GetCurrent(), val);
            std::free(result);
            result = (char *)std::malloc(sizeof(char *) * std::strlen(*value));
            std::strcpy(result , *value);
            return result;
        }
    }
    return result;
}

int Value::ToCppInt(v8::Local<v8::Int32> val){
    return Value::ToCppInt(val.As<v8::Value>());
}
int Value::ToCppInt(v8::Local<v8::Value> val){
    bool lossless = false;
    signed long long int v =0;
    if(Value::ISInt(val)){
        if(val->IsInt32()){
            return val.As<v8::Int32>()->Value();
        }
        else if(val->IsBigInt()){
            v =  val.As<v8::BigInt>()->Int64Value(&lossless);
            if(lossless) return static_cast<int>(v);
        }
        else if(val->IsBigIntObject()){
            v =  val.As<v8::BigIntObject>()->ValueOf()->Int64Value(&lossless);
            if(lossless) return static_cast<int>(v);
        }
        else if(val->IsNumber()){
            return static_cast<int>(val.As<v8::Number>()->Value());
        }
        else if(val->IsNumberObject()){
            return static_cast<int>(val.As<v8::NumberObject>()->ValueOf());
        }
    }
    return 0;
}


signed long long int Value::ToCppBigInt(v8::Local<v8::BigInt> val){
    return Value::ToCppBigInt(val.As<v8::Value>());
}

signed long long int Value::ToCppBigInt(v8::Local<v8::Value> val){
    bool lossless = false;
    signed long long int v =0;
    if(!val.IsEmpty()){
        if(val->IsInt32()){
            return val.As<v8::Int32>()->Value();
        }
        else if(val->IsBigInt()){
            v =  val.As<v8::BigInt>()->Int64Value(&lossless);
            if(lossless) return v;
        }
        else if(val->IsBigIntObject()){
            v =  val.As<v8::BigIntObject>()->ValueOf()->Int64Value(&lossless);
            if(lossless) return v;
        }
        else if(val->IsNumber()){
            return static_cast<long long int>(val.As<v8::Number>()->Value());
        }
        else if(val->IsNumberObject()){
            return static_cast<long long int>(val.As<v8::NumberObject>()->ValueOf());
        }
    }
    return -1;
}



bool Value::ToCppBool(v8::Local<v8::Boolean> val){
    return Value::ToCppBool(val.As<v8::Value>());
}

bool Value::ToCppBool(v8::Local<v8::Value> val){
    if(!val.IsEmpty() && val->IsBoolean()){
        return val.As<v8::Boolean>()->Value();
    }
    return false;
}

double Value::ToCppDouble(v8::Local<v8::Number> val){
    return Value::ToCppDouble(val.As<v8::Value>());
}
double Value::ToCppDouble(v8::Local<v8::Value> val){
    if(!val.IsEmpty() && val->IsNumber() && !val->IsInt32()){
        return val.As<v8::Number>()->Value();
    }
    return 0;
}

 
const char * Value::ToCppString(v8::MaybeLocal<v8::Value> val){
    const char * result = "";
    if(!val.IsEmpty()){
        if(val.ToLocalChecked()->IsString()){
            return Value::ToCppString( val.ToLocalChecked());
        }
    }
    return result;
}
int Value::ToCppInt(v8::MaybeLocal<v8::Value> val) {
    if(!val.IsEmpty()){
        if(val.ToLocalChecked()->IsInt32()){
            return Value::ToCppInt( val.ToLocalChecked());
        }
    }
    return 0;
}
bool Value::ToCppBool(v8::MaybeLocal<v8::Value> val){
    if(!val.IsEmpty()){
        if(val.ToLocalChecked()->IsBoolean()){
            return Value::ToCppBool( val.ToLocalChecked());
        }
    }
    return false;
}
double Value::ToCppDouble(v8::MaybeLocal<v8::Value> val){
    if(!val.IsEmpty()){
        if(val.ToLocalChecked()->IsNumber()){
            return Value::ToCppDouble( val.ToLocalChecked());
        }
    }
    return false;   
}





v8::Local<v8::Value> Value::ToLocal(){return this -> val;}
Value::String   Value::ToString(){ return Value::String (this->val.As<v8::String>()); };
Value::Int      Value::ToInt(){ return Value::Int(this->val.As<v8::Int32>()); };
Value::BigInt   Value::ToBigInt(){ return Value::BigInt(this->val.As<v8::BigInt>()); };
Value::Number   Value::ToNumber(){ return Value::Number(this->val.As<v8::Number>()); };
Value::Boolean  Value::ToBoolean(){ return Value::Boolean (this->val.As<v8::Boolean>()); };
Value::Object   Value::ToObject(){ return Value::Object (this->val.As<v8::Object>()); };
Value::Array   Value::ToArray(){ return Value::Array (this->val.As<v8::Array>()); };
Value::Function Value::ToFunction(){ return Value::Function (this->val.As<v8::Function>()); };














Value::TypeDef::TypeDef(){}
Value::TypeDef::TypeDef(const char * val):str(val){};
Value::TypeDef::~TypeDef(){};
Value::TypeDef::operator char*(){ return (char *)this->str.data();}
Value::TypeDef::operator char*()const {return (char *)this->str.data();};
















// String
Value::String::String(){
    this->val = Value::CreateValue("").As<v8::String>();
    this->length = this->val->Length();
}
Value::String::String(const char * value) : val(Value::CreateValue(value).As<v8::String>()){
    this->length = this->val->Length();
}
Value::String::String(const unsigned char * value) : val(Value::CreateValue(reinterpret_cast<const char *>(value)).As<v8::String>()){
    this->length = this->val->Length();
}
Value::String::String(v8::Local<v8::String> value) : val(value){
    this->length = this->val->Length();
};
Value::String::String(v8::Local<v8::Value> value) : val(value.As<v8::String>()){
    this->length = this->val->Length();
};
Value::String::String(v8::MaybeLocal<v8::Value> value){ 
    this->length= 0;
    if(!value.IsEmpty()){
        if(value.ToLocalChecked()->IsString()){
            this->val = value.ToLocalChecked().As<v8::String>();
            this->length = this->val->Length();
        }
    }
};

bool Value::String::IsEmpty(){ return this->val.IsEmpty() || !this->val->IsString();}
v8::Local<v8::Value> Value::String::AutoCast(){ return this->val;};
v8::Local<v8::Value> Value::String::Cast(){ return this->val;};
Value::String::~String(){ this->val.Clear();}
const char * Value::String::CppValue(){return Value::ToCppString( this -> val);}
Value::String::operator Value(){ return Value(this->val);}
Value::String::operator Value() const { return Value(this->val);}
Value::String::operator v8::Local<v8::Value>(){return this->val.As<v8::Value>();}
Value::String::operator v8::Local<v8::Value>() const{return this->val.As<v8::Value>();}
Value::String::operator v8::Local<v8::String>(){return this->val;}
Value::String::operator v8::Local<v8::String>()const{return this->val;}
Value::String::operator char*(){return (char *)(this->CppValue());}
Value::String::operator char*()const{return (char *)(Value::ToCppString(this->val));}
Value::String Value::String::operator=(const char * value){
    this->val.Clear();
    this->val= Value::CreateValue(value).As<v8::String>();
    this->length = this->val->Length();
    return *this;
}
Value::String Value::String::operator=(const Value::String& value){
    this->val.Clear();
    this->val = value.val;
    return *this;
}

Value::String Value::String::operator=(const Value::String* value){
    this->val.Clear();
    this->val = value->val;
    return *this;
}

bool Value::String::operator==(const char * value) const{
    return std::strcmp(Value::ToCppString(this->val) , value) == 0;
}




 
 









 





 
 
 



// Null
Value::Null::Null():val(v8::Null(v8::Isolate::GetCurrent())){}
Value::Null::~Null(){}
int Value::Null::CppValue(){
    return 0;
}
v8::Local<v8::Value> Value::Null::AutoCast(){return this->val;}
v8::Local<v8::Value> Value::Null::Cast(){return this->val;}
bool Value::Null::IsEmpty(){return this->val.IsEmpty();}
Value::Null::operator Value(){ return Value(this->val);}
Value::Null::operator Value() const { return Value(this->val);}
Value::Null::operator v8::Local<v8::Primitive>(){
    return this->val;
}
Value::Null::operator v8::Local<v8::Primitive>() const {
    return this->val;
}
Value::Null::operator v8::Local<v8::Value>(){
    return this->val.As<v8::Value>();;
}
Value::Null::operator v8::Local<v8::Value>() const {
    return this->val.As<v8::Value>();
}

Value::Null Value::Null::operator=(const Null& value){
    this->val=value.val;
    return *this;
};

Value::Null Value::Null::operator=(const Null* value){
    this->val=value->val;
    return *this;
}



// Undefined
Value::Undefined::Undefined():val(v8::Undefined(v8::Isolate::GetCurrent())){}
Value::Undefined::~Undefined(){}
int Value::Undefined::CppValue(){
    return 0;
}
v8::Local<v8::Value> Value::Undefined::AutoCast(){return this->val;}
v8::Local<v8::Value> Value::Undefined::Cast(){return this->val;}
bool Value::Undefined::IsEmpty(){return this->val.IsEmpty();}
Value::Undefined::operator Value(){ return Value(this->val);}
Value::Undefined::operator Value() const { return Value(this->val);}
Value::Undefined::operator v8::Local<v8::Value>(){
    return this->val;
}
Value::Undefined::operator v8::Local<v8::Value>() const {
    return this->val;
}
Value::Undefined::operator int(){ return 0;};
Value::Undefined::operator int() const { return 0; };
Value::Undefined Value::Undefined::operator=(const Undefined& value){
    this->val=value.val;
    return *this;
};
Value::Undefined Value::Undefined::operator=(const Undefined* value){
    this->val=value->val;
    return *this;
}













// Boolean
Value::Boolean::Boolean(){};
Value::Boolean::Boolean(bool value) : val(Value(value)){};
Value::Boolean::Boolean(v8::Local<v8::Boolean> value) : val(value){};
Value::Boolean::Boolean(v8::Local<v8::Value> value) : val(value.As<v8::Boolean>()){};
Value::Boolean::~Boolean(){this->val.Clear();}
bool Value::Boolean::IsEmpty(){
    return this->val.IsEmpty() || !this->val->IsBoolean();
}
bool Value::Boolean::CppValue(){
    return Value::ToCppBool( this -> val.As<v8::Value>() );
}
v8::Local<v8::Value> Value::Boolean::AutoCast(){return this->val;}
v8::Local<v8::Value> Value::Boolean::Cast(){return this->val;}

Value::Boolean::operator Value(){ return Value(this->val);}
Value::Boolean::operator Value() const { return Value(this->val);}
Value::Boolean::operator v8::Local<v8::Value>(){return this->val ;}
Value::Boolean::operator v8::Local<v8::Value>() const{return this->val.As<v8::Value>();}
Value::Boolean::operator v8::Local<v8::Boolean>(){return this->val;}
Value::Boolean::operator v8::Local<v8::Boolean>() const{return this->val;}
Value::Boolean::operator bool()const{return Value::ToCppBool(this->val);}
Value::Boolean Value::Boolean::operator=(bool value){ 
    this->val.Clear();
    this->val= Value::CreateValue(value).As<v8::Boolean>();
    return *this;
}
Value::Boolean Value::Boolean::operator=(const Value::Boolean& value){
    this->val.Clear();
    this->val = value.val;
    return *this;
}
Value::Boolean Value::Boolean::operator=(const Value::Boolean* value){
    this->val.Clear();
    this->val = value->val;
    return *this;
}













Value::Array::Array(){
    Node::Isolate isoalte;
    Node::Context context;
    this->array_global = Node::Context()->Global();
    this->length=0;
    this->arr_object = v8::Object::New(v8::Isolate::GetCurrent());
    this->val = v8::Array::New(isoalte , 0);
}

Value::Array::Array(v8::Local<v8::Value> value){
    Node::Context context;
    Node::Isolate isolate;
    this->array_global = Node::Context()->Global();
    if(!value.IsEmpty()){
        if(value->IsArray()){
            this->val = value.As<v8::Array>();
            this->length = this->val->Length();
        }
        else if (value->IsObject()){
            Value::Object obj(value);
            Value arr(obj -> GetPropertyNames(context));
            if(arr.IsArray()){
                arr = static_cast<v8::Local<v8::Array>>(arr);
                this->length = arr.ToV8Array()->Length();
                this->val = v8::Array::New( isolate , this->length);
                for (int i = 0; i < this->length; i++){
                    Value item = obj->Get( context , i );
                    if(!item.IsEmpty()){
                        this->val->Set(context, i , item);
                    }
                }
            }
        }
    }
    
}

Value::Array::Array(v8::Local<v8::Array> value) : val(value){
    this->array_global = Node::Context()->Global();
    this->length = this->val->Length();
};
Value::Array::Array(v8::Local<v8::Object> value) : Array(value.As<v8::Value>()){
    this->array_global = Node::Context()->Global();
};
Value::Array::Array(v8::MaybeLocal<v8::Array> value) : Array(value.ToLocalChecked()){
    this->array_global = Node::Context()->Global();
};
Value::Array::Array(v8::MaybeLocal<v8::Value> value) : Array(value.ToLocalChecked()){
    this->array_global = Node::Context()->Global();
};
Value::Array::Array(v8::MaybeLocal<v8::Object> value) : Array(value.ToLocalChecked()){
    this->array_global = Node::Context()->Global();
};

void Value::Array::Push(v8::Local<v8::Value> value){
    Node::Isolate isoalte;
    Node::Context context;
    this->val->Set(
        context,
        this->length,
        value
    ).FromJust();
    this->length ++ ;
}

void Value::Array::Push( const char * value){ this->Push(Value::CreateValue(value));}
void Value::Array::Push( int value){ this->Push( Value::CreateValue(value));}
void Value::Array::Push( bool value){ this->Push( Value::CreateValue(value));}
void Value::Array::Push( double value){ this->Push( Value::CreateValue(value));}
Value::Array::~Array(){this->val.Clear();}
bool Value::Array::CppValue(){ return false;}
bool Value::Array::IsEmpty(){
    return this->val.IsEmpty() || !this->val->IsArray();
}
v8::Local<v8::Value> Value::Array::AutoCast(){
    return this->val;
}
v8::Local<v8::Value> Value::Array::Cast(){
    return this->val;
}
Value::Array::operator Value(){ return Value(this->val);}
Value::Array::operator Value() const { return Value(this->val);}
Value::Array::operator v8::Local<v8::Value>(){return this->val;}
Value::Array::operator v8::Local<v8::Value>() const{return this->val;}
Value::Array::operator v8::Local<v8::Array>(){return this->val;}
Value::Array::operator v8::Local<v8::Array>() const{return this->val;}
Value Value::Array::Get(int index){
    if(this->val->Get(Node::Context(),index).IsEmpty() || index > this->length) return v8::Local<v8::Value>();
    return this->val->Get(Node::Context(), index).ToLocalChecked();
}
Value Value::Array::operator[](int index){
    return this->Get(index);
}
Value Value::Array::operator[](int index) const {
    if(this->val->Get(Node::Context(),index).IsEmpty() || index > this->length) return v8::Local<v8::Value>();
    return this->val->Get(Node::Context(), index).ToLocalChecked();
}
Value::Array Value::Array::operator=(const Value::Array& value){
    this->length=value.length;
    this->arr_object.Clear();
    this->arr_object=value.arr_object;
    this->val.Clear();
    this->val= value.val;
    return *this;
}

Value::Array Value::Array::operator=(const Value::Array* value){
    this->length=value->length;
    this->arr_object.Clear();
    this->arr_object=value->arr_object;
    this->val.Clear();
    this->val= value->val;
    return *this;
} 















Value::Object::Object(): val(v8::Object::New(v8::Isolate::GetCurrent())){}; 
Value::Object::Object(v8::Local<v8::Object> value):val(value){};
Value::Object::Object(v8::Local<v8::Array> value):val(value.As<v8::Array>()){};
Value::Object::Object(v8::Local<v8::Value> value):val(value.As<v8::Object>()){};

Value::Object::Object(v8::MaybeLocal<v8::Object> value):val(value.ToLocalChecked()){};
Value::Object::Object(v8::MaybeLocal<v8::Array> value):val(value.ToLocalChecked().As<v8::Array>()){};
Value::Object::Object(v8::MaybeLocal<v8::Value> value):val(value.ToLocalChecked().As<v8::Object>()){};
v8::Local<v8::Value> Value::Object::AutoCast(){ return this->val;}
v8::Local<v8::Value> Value::Object::Cast(){ return this->val;}
Value::Object::~Object(){}
void Value::Object::CppValue(){};
bool Value::Object::IsEmpty(){return this->val.IsEmpty() || !this->val->IsObject();}
Value::Object::operator Value(){ return Value(this->val);}
Value::Object::operator Value() const { return Value(this->val);}
Value::Object::operator v8::Local<v8::Value> (){
    return this->val.As<v8::Value>();
}
Value::Object::operator v8::Local<v8::Value> () const{
    return this->val.As<v8::Value>();
}
Value::Object::operator v8::Local<v8::Object>(){
    return val;
}
Value::Object::operator v8::Local<v8::Object> () const{
    return this->val;
}
Value::Object Value::Object::operator=(const Object& value){
    this->val=value.val;
    return *this;
}
Value::Object Value::Object::operator=(const Object* value){
    this->val=value->val;
    return *this;
}

void Value::Object::Set(int index, int value){
    this->val->Set(
        v8::Isolate::GetCurrent()->GetCurrentContext(),
        index,
        Value(value)
    );
}
void Value::Object::Set(int index, double value){
    this->val->Set(
        v8::Isolate::GetCurrent()->GetCurrentContext(),
        index,
        Value(value)
    );
}
void Value::Object::Set(int index, const char*value){
    this->val->Set(
        v8::Isolate::GetCurrent()->GetCurrentContext(),
        index,
        Value(value)
    );
}
void Value::Object::Set(int index, bool value){
   this->val->Set(
        v8::Isolate::GetCurrent()->GetCurrentContext(),
        index,
        Value(value)
    );
}
void Value::Object::Set(int index, Object value){
    this->val->Set(
        v8::Isolate::GetCurrent()->GetCurrentContext(),
        index,
        value
    );
}
void Value::Object::Set(int index, v8::Local<v8::Value> value){
    this->val->Set(
        v8::Isolate::GetCurrent()->GetCurrentContext(),
        index,
        value
    );
}
void Value::Object::Set(const char* name, int value){
    this->val->Set(
        v8::Isolate::GetCurrent()->GetCurrentContext(),
        Value(name),
        Value(value)
    );
}
void Value::Object::Set(const char*name, double value){
    this->val->Set(
        v8::Isolate::GetCurrent()->GetCurrentContext(),
        Value(name),
        Value(value)
    );
}
void Value::Object::Set(const char* name, const char* value){
    this->val->Set(
        v8::Isolate::GetCurrent()->GetCurrentContext(),
        Value(name),
        Value(value)
    );
}
void Value::Object::Set(const char* name, bool value){
    this->val->Set(
        v8::Isolate::GetCurrent()->GetCurrentContext(),
        Value(name),
        Value(value)
    );
}
void Value::Object::Set(const char* name, Object value){
    this->val->Set(
        v8::Isolate::GetCurrent()->GetCurrentContext(),
        Value(name),
        value
    );
}
void Value::Object::Set(const char* name, v8::Local<v8::Value> value){
    this->val->Set(
        v8::Isolate::GetCurrent()->GetCurrentContext(),
        Value(name),
        value
    );
}


Value Value::Object::Get(const char* key){
    return Value( this->val->Get( Node::Context() , Value(key)));
};

Value Value::Object::Get(int index) {
    return Value( this->val->Get( Node::Context() , index));
};













Value::Function::Function(){};
Value::Function::Function(v8::Local<v8::FunctionTemplate> value){
    this->val = value->GetFunction(Node::Context()).ToLocalChecked();
}; 
 
Value::Function::Function(void*data){
    v8::MaybeLocal<v8::Function> fn = *(static_cast<v8::MaybeLocal<v8::Function> *>(data)); 
    if(! fn.IsEmpty()){
        if(fn.ToLocalChecked()->IsFunction()){ 
            this -> val = fn.ToLocalChecked().As<v8::Function>();
        }
    }
}

Value::Function::Function(v8::FunctionCallback callback, const char * name , v8::Local<v8::Value> data){
    this -> val = Value(callback , name ,data);
}

Value::Function::Function(v8::Local<v8::Function> value):val(value){};
Value::Function::Function(v8::MaybeLocal<v8::Function> value):Function(value.ToLocalChecked()){};
Value::Function::Function(v8::Local<v8::Value> value){
    if(!value.IsEmpty()){
        if(value->IsFunction()){
            this->val = value.As<v8::Function>();
        }
    }
};

Value::Function::Function(v8::MaybeLocal<v8::Value> value):Function(value.ToLocalChecked()){};
v8::Local<v8::Value> Value::Function::AutoCast(){ return this->val;}
v8::Local<v8::Value> Value::Function::Cast(){ return this->val;}
Value::Function::~Function(){}
void Value::Function::CppValue(){};
bool Value::Function::IsEmpty(){ return (this->val.IsEmpty() || !this->val->IsFunction());};
Value::Function::operator Value(){ return Value(this->val);}
Value::Function::operator Value() const { return Value(this->val);}
Value::Function::operator v8::Local<v8::Value>(){
    return this->val.As<v8::Value>();
}
Value::Function::operator v8::Local<v8::Value> () const{
    return this->val.As<v8::Value>();
}
Value::Function::operator v8::Local<v8::Function>(){
    return val;
}

 
Value::Function Value::Function::operator=(const Function& value){
    this->val=value.val;
    return *this;
}
Value::Function Value::Function::operator=(const Function* value){
    this->val=value->val;
    return *this;
}

Value Value::Function::Call(int count , ...){
    v8::Local<v8::Value> * argv = new v8::Local<v8::Value>[count]();
    va_list args; 
    va_start(args, count);
    for (int i = 0; i < count; i++){
        argv[i] = static_cast<v8::Local<v8::Value>>(va_arg(args, v8::Local<v8::Value>));
    }
    va_end(args);
        
    Value result = this -> val -> Call(
        v8::Isolate::GetCurrent() -> GetCurrentContext() ,
        this->val,
        count,
        count > 0 ? argv : NULL
    );
    delete[] argv;
    return result;
}

Value Value::Function::Call(v8::Local<v8::Value> context, int count , ...){
    v8::Local<v8::Value> * argv = new v8::Local<v8::Value>[count]();
    va_list args; 
    va_start(args, count);
    for (int i = 0; i < count; i++){
        argv[i] = static_cast<v8::Local<v8::Value>>(va_arg(args, v8::Local<v8::Value>));
    }
    va_end(args);
        
    Value result = this -> val -> Call(
        v8::Isolate::GetCurrent() -> GetCurrentContext() ,
        context,
        count,
        count > 0 ? argv : NULL
    );
    delete[] argv;
    return result;
}








Value::Class::Class(){
    Node::Isolate isolate;
    this->external_data=v8::Local<v8::Value>();
    this->class_context=v8::FunctionTemplate::New(isolate, [](Value::Argumants a){});
    this->class_context->InstanceTemplate()->SetInternalFieldCount(1);
    this->class_name = Value("");
};



Value::Class::Class(v8::FunctionCallback callback ,  const char * class_name){
    Node::Isolate isolate;
    this->external_data = v8::Local<v8::Value>();
    this->class_context = v8::FunctionTemplate::New(isolate, callback);
    this->class_context->InstanceTemplate()->SetInternalFieldCount(1);
    this->class_context->SetClassName(Value(class_name));
}

Value::Class::Class( v8::FunctionCallback callback ,  const char * class_name , v8::Local<v8::Value> data){
    Node::Isolate isolate;
    this->class_context = v8::FunctionTemplate::New(isolate, callback , data);
    this->class_context->InstanceTemplate()->SetInternalFieldCount(1);
    this->class_context->SetClassName(Value(class_name));
    this->external_data=data;
    this->class_name=Value(class_name);
}

Value::Class::Class(v8::FunctionCallback callback, const char * class_name , v8::Local<v8::FunctionTemplate> extends){
    Node::Isolate isolate;
    this->external_data = v8::Local<v8::Value>();
    v8::Local<v8::Value> data = v8::Local<v8::Value>();
    this->class_context = v8::FunctionTemplate::New(isolate, callback, data ,v8::Signature::New(isolate, extends));
    this->class_context->InstanceTemplate()->SetInternalFieldCount(1); 
    this->class_context->SetClassName(Value(class_name));
}

Value::Class::Class(v8::FunctionCallback callback, const char * class_name , v8::Local<v8::Function> extends){
    Node::Isolate isolate;
    v8::Local<v8::Value> data = v8::Local<v8::Value>();
    this->class_context = v8::FunctionTemplate::New(isolate, callback, data ,v8::Signature::New(isolate, extends.As<v8::FunctionTemplate>()));
    this->class_context->InstanceTemplate()->SetInternalFieldCount(1);
    this->class_context->SetClassName(Value(class_name));
}

Value::Class::Class(
    v8::FunctionCallback callback , 
    const char * class_name , 
    v8::Local<v8::FunctionTemplate> extends,
    v8::Local<v8::Value> data 
    ){
    
    Node::Isolate isolate;
    this->class_context = v8::FunctionTemplate::New(isolate, callback, data ,v8::Signature::New(isolate, extends));
    this->class_context->InstanceTemplate()->SetInternalFieldCount(1);
    this->class_context->SetClassName(Value(class_name));
    
}


void Value::Class::SetMethod(v8::FunctionCallback callback , const char * func_name , v8::Local<v8::Value> data){
    Node::Isolate isolate;
    this->class_context->PrototypeTemplate()->Set(
        Value(func_name),
        v8::FunctionTemplate::New(isolate,callback, data, v8::Signature::New(isolate, this->class_context))
    );
} 

void Value::Class::SetField(
    v8::AccessorGetterCallback getter_callback ,
    v8::AccessorSetterCallback setter_callbak,
    const char * field_name ,
    v8::Local<v8::Value> data){

    Node::Isolate isolate;
    this->class_context->InstanceTemplate()->SetAccessor(
        Value(field_name),
        getter_callback,
        setter_callbak,
        data,
        v8::AccessControl::DEFAULT,
        v8::PropertyAttribute::None
    );
}

void Value::Class::SetProperty(const char * pro_name , v8::Local<v8::Value> value){
    this->class_context->GetFunction(Node::Context()).ToLocalChecked()->Set(
        Node::Context(),
        Value(pro_name),
        value
    );
}

void Value::Class::SetConstructor(v8::FunctionCallback callback , v8::Local<v8::Value> data){
    if(data.IsEmpty()) return this->class_context->SetCallHandler(callback);
    this->class_context.Clear();
    this->class_context=v8::FunctionTemplate::New(Node::Isolate(), callback, data);
    this->class_context->InstanceTemplate()->SetInternalFieldCount(1);
    this->class_context->SetClassName(this->class_name);
}

void Value::Class::SetName(const char * class_name){
    this->class_name.Clear();
    this->class_name = Value(class_name);
    this->class_context->SetClassName(this->class_name);
}

Value::Class::~Class(){}

v8::Local<v8::Value> Value::Class::Cast(){ return this ->class_context->GetFunction(Node::Context()).ToLocalChecked();}
v8::Local<v8::Value> Value::Class::AutoCast(){ return this ->class_context->GetFunction(Node::Context()).ToLocalChecked();}
Value::Class::operator Value(){ return Value(this ->class_context->GetFunction(Node::Context()).ToLocalChecked());}
Value::Class::operator Value() const { return Value(this ->class_context->GetFunction(Node::Context()).ToLocalChecked());}
Value::Class::operator v8::Local<v8::Function>(){
    return this ->class_context->GetFunction(Node::Context()).ToLocalChecked();
}

Value::Class::operator v8::Local<v8::Function>() const{
    return this ->class_context->GetFunction(Node::Context()).ToLocalChecked();
}


Value::Class::operator v8::Local<v8::FunctionTemplate>(){
    return this ->class_context;
}

Value::Class::operator v8::Local<v8::FunctionTemplate>() const{
    return this ->class_context ;
}

Value::Class::operator v8::Local<v8::Value>(){
    return this ->class_context->GetFunction(Node::Context()).ToLocalChecked().As<v8::Value>();
}

Value::Class::operator v8::Local<v8::Value>() const{
    return this ->class_context->GetFunction(Node::Context()).ToLocalChecked().As<v8::Value>();
}


Value::Class Value::Class::operator=(const Class& string){
    this->class_context = string.class_context;
    return *this;
}
Value::Class Value::Class::operator=(const Class* string){
    this->class_context = string->class_context;
    return *this;
}

v8::Local<v8::FunctionTemplate> Value::Class::operator ->(){return this->class_context;}; 


























// Array
Value::DynamicArray::DynamicArray(){ this->length=0; this->val = v8::Object::New(Node::Isolate());}
Value::DynamicArray::DynamicArray(v8::Local<v8::Array> value){
    this->length=0;
    this->val = v8::Object::New(Node::Isolate());
    if(!value.IsEmpty()&&value->IsArray()){
        this->val.Clear();
        this->length = value->Length();
        for (int i = 0; i < this->length; i++){
            Value item(value->Get(Node::Context(),i));
            this->val->Set(
                Node::Context(),
                i,
                item 
            );
        }
    }
};

Value::DynamicArray::DynamicArray(v8::Local<v8::Object> value){
    this->length=0;
    this->val=v8::Object::New(Node::Isolate());
    if(!value.IsEmpty() && value->IsObject()){
        this->val.Clear();
        Value item_length(value->GetPropertyNames(Node::Context()));
        v8::Local<v8::Array> arr =  static_cast<v8::Local<v8::Array>>(item_length);
        this->length=arr->Length();
        this->val=value;
    }
};


Value::DynamicArray::DynamicArray(v8::Local<v8::Value> value){
    this->length=0;
    this->val=v8::Object::New(Node::Isolate());
    if(!value.IsEmpty()){
        if(value->IsArray()){
            this->val.Clear();
            v8::Local<v8::Array> arr = value.As<v8::Array>();
            this->length = arr->Length();
            for (int i = 0; i < this->length; i++){
                Value item(arr->Get(Node::Context(),i));
                this->val->Set(
                    Node::Context(),
                    i,
                    item 
                );
            }
        }

        if(value->IsObject()){
            this->val.Clear();
            v8::Local<v8::Object> obj = value.As<v8::Object>();
            Value item_length(obj);
            v8::Local<v8::Array> arr =  static_cast<v8::Local<v8::Array>>(item_length);
            this->length=arr->Length();
            this->val=obj;    
        }
    }
}




Value::DynamicArray::DynamicArray(v8::MaybeLocal<v8::Array> value):DynamicArray(value.ToLocalChecked()){};
Value::DynamicArray::DynamicArray(v8::MaybeLocal<v8::Object> value):DynamicArray(value.ToLocalChecked()){}
Value::DynamicArray::DynamicArray(v8::MaybeLocal<v8::Value> value):DynamicArray(value.ToLocalChecked()){}




void Value::DynamicArray::Push(v8::Local<v8::Value> value){
    Node::Isolate isolate;
    Node::Context context;
    this->val->Set(
        context,
        this->length,
        value
    );
    this->length++;
}

inline v8::Local<v8::Array> Value::DynamicArray::ObjectToArray( v8::Local<v8::Object> value , int length){
    v8::Local<v8::Array> array = v8::Array::New(v8::Isolate::GetCurrent() , length);
    for (int i = 0; i < length; i++){
        Value item =  value->Get(v8::Isolate::GetCurrent()->GetCurrentContext(), i);
        array->Set(v8::Isolate::GetCurrent()->GetCurrentContext(), i , item);
    }
    return array;
}

void Value::DynamicArray::Push( const char * value){ this->Push(Value::CreateValue(value));}
void Value::DynamicArray::Push( int value){ this -> Push( Value::CreateValue(value));}
void Value::DynamicArray::Push( bool value){ this -> Push( Value::CreateValue(value));}
void Value::DynamicArray::Push( double value){ this -> Push( Value::CreateValue(value));}
Value::DynamicArray::~DynamicArray(){this->val.Clear();}
bool Value::DynamicArray::CppValue(){ return false;}
Value::DynamicArray::operator v8::Local<v8::Value>(){return Value::DynamicArray::ObjectToArray(this->val,this->length);}
Value::DynamicArray::operator v8::Local<v8::Value>() const{Value::DynamicArray::ObjectToArray(this->val,this->length);}
Value::DynamicArray::operator v8::Local<v8::Array>(){return Value::DynamicArray::ObjectToArray(this->val,this->length);}
Value::DynamicArray::operator v8::Local<v8::Array>() const{return Value::DynamicArray::ObjectToArray(this->val,this->length);}
v8::Local<v8::Object> Value::DynamicArray::operator->(){return this->val;};
Value::DynamicArray Value::DynamicArray::operator=(const Value::DynamicArray& value){
    return *this;
}
Value::DynamicArray Value::DynamicArray::operator=(const Value::DynamicArray* value){
    return *this;
}














// Node

Node::Isolate::Isolate():val(v8::Isolate::GetCurrent()){};
Node::Isolate::~Isolate(){};
Node::Isolate::operator v8::Isolate*(){return this->val;};
Node::Isolate::operator v8::Isolate*()const{return this->val;};
v8::Isolate * Node::Isolate::operator ->(){return this->val;}


Node::Context::Context():val(v8::Isolate::GetCurrent()->GetCurrentContext()){};
Node::Context::~Context(){};
Node::Context::operator v8::Local<v8::Context>(){return this->val;};
Node::Context::operator v8::Local<v8::Context>()const {return this->val;};
v8::Context * Node::Context::operator ->(){return this->val.operator->();};



















Node::Throw::Throw(){}
Node::Throw::~Throw(){}

Node::Throw::Exception::Exception(){} 
Node::Throw::Exception::~Exception(){}

Node::Throw::Exception::TypeError::TypeError(const char * error){
    Node::Isolate isolate;
    isolate->ThrowException(
        v8::Exception::TypeError(
            Value(error)
        )
    );
} 
Node::Throw::Exception::TypeError::~TypeError(){} 






Node::Throw::Exception::RangeError::RangeError(const char * error){
    Node::Isolate isolate;
    isolate->ThrowException(
        v8::Exception::RangeError(
            Value(error)
        )
    );
} 

Node::Throw::Exception::RangeError::~RangeError(){} 


Node::Throw::Exception::Error::Error(const char * error){
    Node::Isolate isolate;
    isolate->ThrowException(
        v8::Exception::Error(
            Value(error)
        )
    );
} 

Node::Throw::Exception::Error::~Error(){} 




Node::Throw::Exception::ReferenceError::ReferenceError(const char * error){
    Node::Isolate isolate;
    isolate->ThrowException(
        v8::Exception::ReferenceError(
            Value(error)
        )
    );
} 

Node::Throw::Exception::ReferenceError::~ReferenceError(){} 





Node::Throw::Exception::SyntaxError::SyntaxError(const char * error){
    Node::Isolate isolate;
    isolate->ThrowException(
        v8::Exception::SyntaxError(
            Value(error)
        )
    );
} 

Node::Throw::Exception::SyntaxError::~SyntaxError(){} 




void Node::Throw::Exception::Argumants(const char * name , Value::TypeDef type){
    char * str = (char *)std::malloc(sizeof(char*) * 150);
    sprintf(str, "Argumant %s must be %s", name , static_cast<char *>(type));
    Node::Throw::Exception::TypeError(static_cast<const char *>(str));
    std::free(str);
};

void Node::Throw::Exception::Constructor(const char * name){
    char * str = (char *)std::malloc(sizeof(char*) * 200);
    sprintf(str, "Class constructor %s cannot be invoked without 'new'", name);
    Node::Throw::Exception::TypeError(static_cast<const char *>(str));
    std::free(str);
};





























Value::Number::Number(){
    this->Clear();
    this->type = NODE_NUMBER_TYPE;
}

Value::Number::Number(int value) :Number(){
    this->Clear();
    if(Value::Number::IsInt(value , false)){
        this->type = NODE_INT16_TYPE;
        this->val = Value::CreateValue(static_cast<int>(value));
        this->_v = value;
    }
}
Value::Number::Number(unsigned long int value , bool safeCheck) : Number(){
    this->Clear();
    if(Value::Number::IsInt16(value) || Value::Number::IsInt32(value)){ 
        this->_v = value;
        this->val = Value::CreateValue(static_cast<int>(value));
    }
    else if(Value::Number::IsInt64(value , safeCheck)){ 
        this->_v = value;
        this->val = Value::CreateValue(static_cast<long long int>(value));
    }
}
Value::Number::Number(long long int value , bool safeCheck):Number(){
    this->Clear();
    if(Value::Number::IsInt16(value) || Value::Number::IsInt32(value)){ 
        this->val = Value::CreateValue(static_cast<int>(value));
        this->_v = value;
    }
    else if(Value::Number::IsInt64(value , safeCheck)){ 
        this->val = Value::CreateValue(static_cast<long long int>(value));
        this->_v = value;
    }
}
Value::Number::Number(double value , bool safeCheck) : Number(){
    this->Clear();
    if(Value::Number::IsInt16(value) || Value::Number::IsInt32(value)){ 
        this->val = Value::CreateValue(static_cast<int>(value));
        this->_v = static_cast<double>(value);
    }
    else if(Value::Number::IsInt64(value , safeCheck)){
        this->type = NODE_INT64_TYPE;
        this->val = Value::CreateValue(static_cast<long long int>(value));
        this->_v = static_cast<double>(value);
    }
    else {
        bool safe = safeCheck ? Value::Number::IsSafe(value) : true;
        if(safe){
            this->val = Value::CreateValue(static_cast<double>(value));
            this->_v = static_cast<double>(value);
        }
    }
}

Value::Number::Number(v8::Local<v8::Value> value , bool safeCheck):Number(){
    if(!value.IsEmpty()){
        if(value->IsInt32()){
            this->val  = value;
            this->_v = value.As<v8::Int32>()->Value();
            this->type = NODE_INT32_TYPE;
        }
        else if(value->IsBigInt()){
            bool lossless = false;
            long long int v = value.As<v8::BigInt>()->Int64Value(&lossless);
            bool safe = safeCheck ? Value::Number::IsSafe(v) : true;
            if(lossless && safe){
                this->val = value;
                this->_v = v;
                this->type = NODE_INT64_TYPE;
            }
        }
        else if(value->IsBigIntObject()){
            bool lossless = false;
            long long int v = value.As<v8::BigIntObject>()->ToBigInt(Node::Context()).ToLocalChecked()->Int64Value(&lossless);
            bool safe = safeCheck ? Value::Number::IsSafe(v) : true;
            if(lossless){
                this->val = value;
                this->_v = v; 
            }
        }
        else if(value->IsNumber()){
            double v = value.As<v8::Number>()->Value();
            if(Value::Number::IsInt(v)){
                if(Value::Number::IsInt16(v) || Value::Number::IsInt32(v)){
                    this->val = Value::CreateValue(static_cast<int>(v));
                    this->_v = static_cast<int>(v); 
                }
                else if(Value::Number::IsInt64(v , safeCheck)){
                    this->val = Value::CreateValue(static_cast<long long int>(v));
                    this->_v = static_cast<long long int>(v); 
                }
            }
            else {
                bool safe = safeCheck ? Value::Number::IsSafe(v) : true;
                if(safe){
                    this->val = value;
                    this->_v = v; 
                }
            }
        }
        else if(value->IsNumberObject()){
            bool lossless = false;
            double v = value.As<v8::NumberObject>()->ValueOf();
            if(Value::Number::IsInt(v)){ 
                if(Value::Number::IsInt16(v) || Value::Number::IsInt32(v)){
                    this->val = Value::CreateValue(static_cast<int>(v));
                    this->_v = static_cast<int>(v); 
                }
                else if(Value::Number::IsInt64(v , safeCheck)){
                    this->val = Value::CreateValue(static_cast<long long int>(v));
                    this->_v = static_cast<long long int>(v); 
                }
            }
            else {
                bool safe = safeCheck ? Value::Number::IsSafe(v) : true;
                if(safe){
                    this->val = value;
                    this->_v = v; 
                }
            }
        }
    }
}
Value::Number::Number(v8::Local<v8::Number> value , bool safeCheck):Number(value.As<v8::Value>(),safeCheck){}
Value::Number::Number(v8::Local<v8::Int32> value):Number(value.As<v8::Value>()){}
Value::Number::Number(v8::Local<v8::BigInt> value , bool safeCheck):Number(value.As<v8::Value>() , safeCheck){}
Value::Number::Number(v8::MaybeLocal<v8::Value> value, bool safeCheck): Number(value.ToLocalChecked(),safeCheck){}

v8::Local<v8::Value> Value::Number::Cast(){return this->val;}
v8::Local<v8::Value> Value::Number::AutoCast(){return this->val;}
void Value::Number::Clear(){this->val.Clear();}
double Value::Number::CppValue(){return this->_v;}
bool Value::Number::IsEmpty(){return this->val.IsEmpty();}
bool Value::Number::IsInt( bool safeCheck){return Value::Number::IsInt(this->_v,safeCheck)&&(this->val->IsInt32()||this->val->IsBigInt());}
bool Value::Number::IsInt16(){return Value::Number::IsInt16(this->_v) && (this->val->IsInt32());}
bool Value::Number::IsInt32(){return Value::Number::IsInt32(this->_v) && (this->val->IsInt32());}
bool Value::Number::IsInt64(bool safeCheck){return Value::Number::IsInt64(this->_v , safeCheck);}
bool Value::Number::IsDouble(bool safeCheck){return !Value::Number::IsDouble(this->_v , safeCheck) && (this->val->IsNumber());}
bool Value::Number::IsInt(double value , bool safeCheck){
    bool f1 = (value - static_cast<long long int>(value)) == 0;
    bool safe = safeCheck ? Value::Number::IsSafe(static_cast<long long int>(value)) : true;
    return f1 && safe;
}
bool Value::Number::IsInt16(double value){
    bool f1  = static_cast<long long int>(value) <= MAX_INT_16;
    bool f2  = static_cast<long long int>(value) >= MAX_SIGNED_INT_16;
    bool f3 = (value - static_cast<long long int>( value )) == 0;
    return (f1 && f2) && f3;
}
bool Value::Number::IsInt32(double value){
    bool f1  = static_cast<long long int>(value) <= MAX_INT_32;
    bool f3  = static_cast<long long int>(value) >= MAX_INT_16;
    bool f2  = static_cast<long long int>(value) >= MAX_SIGNED_INT_32;
    bool f4  = static_cast<long long int>(value) <= MAX_SIGNED_INT_16;
    bool f5 = (value - static_cast<long long int>( value )) == 0;
    return ((f1 && f3) || (f2 && f4)) && f5;
}
bool Value::Number::IsInt64(double value , bool safeCheck){ 
    bool f1 = static_cast<long long int>(value) > MAX_INT_32; 
    bool f2 = static_cast<long long int>(value) < MAX_SIGNED_INT_32;
    bool f5 = (value - static_cast<long long int>( value )) == 0;
    bool safe = safeCheck ? ((static_cast<long long int>(value) <= MAX_INT_NODE_SAFE) && (static_cast<long long int>(value) >= MAX_INT_SIGNED_NODE_SAFE)) : true;
    return (f1 || f2) && f5 && safe;
}

bool Value::Number::IsInt16(long long int value){
    return Value::Number::IsInt16(static_cast<double>(value));
}
bool Value::Number::IsInt16(unsigned long int value){
    return Value::Number::IsInt16(static_cast<double>(value));
}
bool Value::Number::IsInt16(int value){
    return Value::Number::IsInt16(static_cast<double>(value));
}
bool Value::Number::IsInt32(long long int value){
    return Value::Number::IsInt32(static_cast<double>(value));
}
bool Value::Number::IsInt32(unsigned long int value){
    return Value::Number::IsInt32(static_cast<double>(value));
}
bool Value::Number::IsInt32(int value){
    return Value::Number::IsInt32(static_cast<double>(value));
} 
bool Value::Number::IsInt64(long long int value , bool safeCheck){
    return Value::Number::IsInt64(static_cast<double>(value) , safeCheck);
}
bool Value::Number::IsInt64(unsigned long int value ,bool safeCheck){
    return Value::Number::IsInt64(static_cast<double>(value), safeCheck);
}
bool Value::Number::IsInt64(int value , bool safeCheck){
    return Value::Number::IsInt64(static_cast<double>(value) , safeCheck);
} 
bool Value::Number::IsDouble(double value , bool safeCheck ){
    bool f1 = (value - static_cast<long long int>( value )) != 0;
    bool safe = safeCheck ? Value::Number::IsSafe(value) : true;
    return f1 && safe;
}
bool Value::Number::IsSafe(){return this->val.IsEmpty() == true;}
bool Value::Number::IsSafe(long long int value){
    return value <= MAX_INT_NODE_SAFE && value >= MAX_INT_SIGNED_NODE_SAFE;

}
bool Value::Number::IsSafe(double value){
    return static_cast<long long int>(value) <= MAX_DOUBLE_NODE_SAFE && static_cast<long long int>(value) >= MAX_SIGNED_DOUBLE_NODE_SAFE;
}
Value::Number::Int32 Value::Number::ToInt32(){return Value::Number::Int32(this->_v);}
Value::Number::Int64 Value::Number::ToInt64(){return Value::Number::Int64(this->_v);}
Value::Number::Double Value::Number::ToDouble(){return Value::Number::Double(this->_v);}
Value::Number::operator Value(){ return Value(this->val);}
Value::Number::operator Value() const { return Value(this->val);}
Value::Number::operator v8::Local<v8::Value>(){ return this->val;}
Value::Number::operator v8::Local<v8::Value> () const{ return this->val;};
Value::Number::operator v8::Local<v8::Int32>() {
    if(this->val.IsEmpty()) return v8::Local<v8::Int32>();
    if(this->val->IsInt32()) return this->val.As<v8::Int32>();
    if(this->val->IsNumber()) return Value::CreateValue(static_cast<int>( this->_v)).As<v8::Int32>();
    if(this->val->IsBigInt()) return Value::CreateValue(static_cast<int>( this->_v)).As<v8::Int32>();
    return v8::Local<v8::Int32>();
};
Value::Number::operator v8::Local<v8::Int32> () const{
    if(this->val.IsEmpty()) return v8::Local<v8::Int32>();
    if(this->val->IsInt32()) return this->val.As<v8::Int32>();
    if(this->val->IsNumber()) return Value::CreateValue(static_cast<int>( this->_v)).As<v8::Int32>();
    if(this->val->IsBigInt()) return Value::CreateValue(static_cast<int>( this->_v)).As<v8::Int32>();
    return v8::Local<v8::Int32>();
};
Value::Number::operator v8::Local<v8::BigInt>(){
    if(this->val.IsEmpty()) return v8::Local<v8::BigInt>();
    if(this->val->IsBigInt()) return this->val.As<v8::BigInt>();
    if(this->val->IsNumber()) return Value::CreateValue(static_cast<long long int>( this->_v)).As<v8::BigInt>();
    if(this->val->IsInt32()) return Value::CreateValue(static_cast<long long int>( this->_v)).As<v8::BigInt>();
    return v8::Local<v8::BigInt>();
}
Value::Number::operator v8::Local<v8::BigInt>() const{
    if(this->val.IsEmpty()) return v8::Local<v8::BigInt>();
    if(this->val->IsBigInt()) return this->val.As<v8::BigInt>();
    if(this->val->IsNumber()) return Value::CreateValue(static_cast<long long int>( this->_v)).As<v8::BigInt>();
    if(this->val->IsInt32()) return Value::CreateValue(static_cast<long long int>( this->_v)).As<v8::BigInt>();
    return v8::Local<v8::BigInt>();
}
Value::Number::operator v8::Local<v8::Number>() {
    if(this->val.IsEmpty()) return v8::Local<v8::Number>();
    if(this->val->IsNumber()) return this->val.As<v8::Number>();
    if(this->val->IsBigInt()) return Value::CreateValue(static_cast<double>( this->_v)).As<v8::Number>();
    if(this->val->IsInt32()) return Value::CreateValue(static_cast<double>( this->_v)).As<v8::Number>();
    return v8::Local<v8::Number>();
}
Value::Number::operator v8::Local<v8::Number>() const {
    if(this->val.IsEmpty()) return v8::Local<v8::Number>();
    if(this->val->IsNumber()) return this->val.As<v8::Number>();
    if(this->val->IsBigInt()) return Value::CreateValue(static_cast<double>( this->_v)).As<v8::Number>();
    if(this->val->IsInt32()) return Value::CreateValue(static_cast<double>( this->_v)).As<v8::Number>();
    return v8::Local<v8::Number>();
}
Value::Number::operator Value::TypeDef(){return Value::TypeDef("Number");}
Value::Number::operator Value::TypeDef() const {return Value::TypeDef("Number");}
Value::Number::operator double() const {return this->_v;}
v8::Local<v8::Value> Value::Number::operator->(){return this->val;}
Value::Number Value::Number::operator=(const Number& value){
    this->val = value.val;
    this->_v = value._v;
    this->type = value.type;
    return *this;
}
Value::Number Value::Number::operator=(const Number* value){
    this->val = value->val;
    this->_v = value->_v;
    this->type = value->type;
    return *this;
}
Value::Number Value::Number::operator=(double value){
    return Value::Number(value);
}
Value::Number Value::Number::operator=(int value){
    return Value::Number(value);
}
Value::Number Value::Number::operator=(unsigned long int value){
    return Value::Number(value);
}
Value::Number Value::Number::operator=(long long int value){
    return Value::Number(value);
}












Value::Number::Int32::Int32(){
    this->val = v8::Local<v8::Int32>();
}
Value::Number::Int32::Int32(int value):Int32(){
    this->val = Value::CreateValue(value).As<v8::Int32>();
    this->_val = value;
}
Value::Number::Int32::Int32(unsigned long value):Int32(){
    if(Value::Number::IsInt16(value) || Value::Number::IsInt32( value)){
        this->val = Value::CreateValue(static_cast<int>(value)).As<v8::Int32>();
        this->_val = static_cast<int>(value);
    }
}
Value::Number::Int32::Int32(long long int value):Int32(){
    if(Value::Number::IsInt16(value) || Value::Number::IsInt32( value)){
        this->val = Value::CreateValue(static_cast<int>(value)).As<v8::Int32>();
        this->_val = static_cast<int>(value);
    }
}
Value::Number::Int32::Int32(double value):Int32(){
    if(Value::Number::IsInt16(value) || Value::Number::IsInt32( value)){
        this->val = Value::CreateValue(static_cast<int>(value)).As<v8::Int32>();
        this->_val = static_cast<int>(value);
    }
}
Value::Number::Int32::Int32(Value::Number value):Int32(){ 
    if(value.IsInt16() || value.IsInt32()){
        this->val = Value::CreateValue(static_cast<int>(value.CppValue())).As<v8::Int32>();
        this->_val = static_cast<int>(value.CppValue());
    }
}
Value::Number::Int32::Int32(v8::Local<v8::Number> value):Int32(){
    Value::Number num(value.As<v8::Value>());
    if(num.IsInt16() || num.IsInt32()){
        this->val = Value::CreateValue(static_cast<int>(num.CppValue())).As<v8::Int32>();
        this->_val = static_cast<int>(num.CppValue());
    }
}
Value::Number::Int32::Int32(v8::Local<v8::Int32> value):Int32(){
    Value::Number num(value.As<v8::Value>());
    if(num.IsInt16() || num.IsInt32()){
        this->val = Value::CreateValue(static_cast<int>(num.CppValue())).As<v8::Int32>();
        this->_val = static_cast<int>(num.CppValue());
    }
}
Value::Number::Int32::Int32(v8::Local<v8::Value> value):Int32(){
    Value::Number num(value);
    if(num.IsInt16() || num.IsInt32()){
        this->val = Value::CreateValue(static_cast<int>(num.CppValue())).As<v8::Int32>();
        this->_val = static_cast<int>(num.CppValue());
    }
}
Value::Number::Int32::Int32(v8::MaybeLocal<v8::Value> value):Int32(){
    Value::Number num(value);
    if(num.IsInt16() || num.IsInt32()){
        this->val = Value::CreateValue(static_cast<int>(num.CppValue())).As<v8::Int32>();
        this->_val = static_cast<int>(num.CppValue());
    }
}
Value::Number::Int32::~Int32(){};
v8::Local<v8::Value> Value::Number::Int32::Cast(){return this->val.As<v8::Value>();}
int Value::Number::Int32::CppValue(){return this->_val;}
bool Value::Number::Int32::IsEmpty(){return this->val.IsEmpty();}
Value::Number::Int32::operator v8::Local<v8::Int32>(){ return this->val;}
Value::Number::Int32::operator v8::Local<v8::Int32>() const {return this->val;}
Value::Number::Int32::operator v8::Local<v8::Value>() { return this->val.As<v8::Value>();}
Value::Number::Int32::operator v8::Local<v8::Value>() const { return this->val.As<v8::Value>();};
Value::Number::Int32::operator Value::TypeDef(){return Value::TypeDef("Int32") ;}
Value::Number::Int32::operator Value::TypeDef() const{return Value::TypeDef("Int32") ;}
Value::Number::Int32::operator int() const{return this->_val;}
Value::Number::Int32 Value::Number::Int32::operator=(const Int32& value){
    this->val =value.val;
    this->_val = value._val;
    return *this;
}
Value::Number::Int32 Value::Number::Int32::operator=(const Int32* value){
    this->val =value->val;
    this->_val = value->_val;
    return *this;
}
Value::Number::Int32 Value::Number::Int32::operator=(double value){
    if(Value::Number::IsInt16(value) || Value::Number::IsInt32( value)){
        this->val = Value::CreateValue(static_cast<int>(value)).As<v8::Int32>();
        this->_val = static_cast<int>(value);
    }
    return *this;
}
Value::Number::Int32 Value::Number::Int32::operator=(int value){
    this->val = Value::CreateValue(static_cast<int>(value)).As<v8::Int32>();
    this->_val = static_cast<int>(value);
    return *this;
}
Value::Number::Int32 Value::Number::Int32::operator=(unsigned long int value){
    if(Value::Number::IsInt16(value) || Value::Number::IsInt32( value)){
        this->val = Value::CreateValue(static_cast<int>(value)).As<v8::Int32>();
        this->_val = static_cast<int>(value);
    }
    return *this;
}
Value::Number::Int32 Value::Number::Int32::operator=(long long int value){
    if(Value::Number::IsInt16(value) || Value::Number::IsInt32( value)){
        this->val = Value::CreateValue(static_cast<int>(value)).As<v8::Int32>();
        this->_val = static_cast<int>(value);
    }
    return *this;
}
v8::Local<v8::Int32> Value::Number::Int32::operator->(){return this->val;}
















Value::Number::Int64::Int64(){
    this->val = v8::Local<v8::BigInt>();
}
Value::Number::Int64::Int64(int value):Int64(){
    this->val = Value::CreateValue( value).As<v8::BigInt>();
    this->_val = value;
}
Value::Number::Int64::Int64(unsigned long value):Int64(){
    this->val = Value::CreateValue(static_cast<long long int>(value)).As<v8::BigInt>();
    this->_val = static_cast<long long int>(value);
}
Value::Number::Int64::Int64(long long int value , bool safeCheck):Int64(){ 
    bool safe = safeCheck ? Value::Number::IsSafe(value) : true;
    if(safe){
        this->val = Value::CreateValue(static_cast<long long int>(value)).As<v8::BigInt>();
        this->_val = static_cast<long long int>(value);
    }
}
Value::Number::Int64::Int64(double value ,  bool safeCheck):Int64(){
    bool safe = safeCheck ? Value::Number::IsSafe(value) : true;
    if(safe){
        this->val = Value::CreateValue(static_cast<long long int>(value)).As<v8::BigInt>();
        this->_val = static_cast<long long int>(value);
    }
}
Value::Number::Int64::Int64(Value::Number value , bool safeCheck):Int64(){
    if(value.IsInt(safeCheck)){
        this->val = Value::CreateValue(static_cast<long long int>(value.CppValue())).As<v8::BigInt>();
        this->_val = static_cast<long long int>(value.CppValue());
    }
}
Value::Number::Int64::Int64(v8::Local<v8::BigInt> value, bool safeCheck ):Int64(){
    Value::Number num(value.As<v8::Value>());
    if(num.IsInt(safeCheck)){
        this->val = Value::CreateValue(static_cast<long long int>(num.CppValue())).As<v8::BigInt>();
        this->_val = static_cast<long long int>(num.CppValue());
    }
}
Value::Number::Int64::Int64(v8::Local<v8::Value> value , bool safeCheck):Int64(){
    Value::Number num(value.As<v8::Value>());
    if(num.IsInt(safeCheck)){
        this->val = Value::CreateValue(static_cast<long long int>(num.CppValue())).As<v8::BigInt>();
        this->_val = static_cast<long long int>(num.CppValue());
    }
}
Value::Number::Int64::Int64(v8::Local<v8::Number> value , bool safeCheck):Int64(){
    Value::Number num(value.As<v8::Value>());
    if(num.IsInt(safeCheck)){
        this->val = Value::CreateValue(static_cast<long long int>(num.CppValue())).As<v8::BigInt>();
        this->_val = static_cast<long long int>(num.CppValue());
    }
}
Value::Number::Int64::Int64(v8::MaybeLocal<v8::Value> value , bool safeCheck ):Int64(){
    Value::Number num(value);
    if(num.IsInt(safeCheck)){
        this->val = Value::CreateValue(static_cast<long long int>(num.CppValue())).As<v8::BigInt>();
        this->_val = static_cast<long long int>(num.CppValue());
    }
}
Value::Number::Int64::~Int64(){};
v8::Local<v8::Value> Value::Number::Int64::Cast(){return this->val.As<v8::Value>();}
long long int Value::Number::Int64::CppValue(){return this->_val;}
bool Value::Number::Int64::IsEmpty(){return this->val.IsEmpty();}
Value::Number::Int64::operator v8::Local<v8::BigInt>(){ return this->val;}
Value::Number::Int64::operator v8::Local<v8::BigInt>() const {return this->val;}
Value::Number::Int64::operator v8::Local<v8::Value>() { return this->val.As<v8::Value>();}
Value::Number::Int64::operator v8::Local<v8::Value>() const { return this->val.As<v8::Value>();};
Value::Number::Int64::operator Value::TypeDef(){return Value::TypeDef("Int64") ;}
Value::Number::Int64::operator Value::TypeDef() const{return Value::TypeDef("Int64") ;}
Value::Number::Int64::operator long() const{return this->_val;}
Value::Number::Int64 Value::Number::Int64::operator=(const Int64& value){
    this->val =value.val;
    this->_val = value._val;
    return *this;
}
Value::Number::Int64 Value::Number::Int64::operator=(const Int64* value){
    this->val =value->val;
    this->_val = value->_val;
    return *this;
}
Value::Number::Int64 Value::Number::Int64::operator=(double value){
    if(Value::Number::IsInt(value)){
        this->val = Value::CreateValue(static_cast<long long int>(value)).As<v8::BigInt>();
        this->_val = static_cast<long long int>(value);
    }
    return *this;
}
Value::Number::Int64 Value::Number::Int64::operator=(int value){
    this->val = Value::CreateValue(static_cast<long long int>(value)).As<v8::BigInt>();
    this->_val = static_cast<long long int>(value);
    return *this;
}
Value::Number::Int64 Value::Number::Int64::operator=(unsigned long int value){
    this->val = Value::CreateValue(static_cast<long long int>(value)).As<v8::BigInt>();
    this->_val = static_cast<long long int>(value);
    return *this;
}
Value::Number::Int64 Value::Number::Int64::operator=(long long int value){
    this->val = Value::CreateValue(static_cast<long long int>(value)).As<v8::BigInt>();
    this->_val = static_cast<long long int>(value);
    return *this;
}
v8::Local<v8::BigInt> Value::Number::Int64::operator->(){return this->val;}









 
Value::Number::Double::Double(){
    this->val = v8::Local<v8::Number>();
}
Value::Number::Double::Double(double value , bool safeCheck): Double(){
    bool safe = safeCheck ? Value::Number::IsSafe(value) : true;
    if(safe){
        this->val = Value::CreateValue(value).As<v8::Number>();
        this->_val = value;
    }
}
Value::Number::Double::Double(v8::Local<v8::Value> value , bool safeCheck) : Double(){
    if(!value.IsEmpty()){
        if(value->IsNumber()){
            bool safe = safeCheck ? Value::Number::IsSafe(value.As<v8::Number>()->Value()) : true;
            if(safe){
                this->val = value.As<v8::Number>();
                this->_val = this->val->Value();
            }
        }
        else if( value->IsNumberObject()){
            bool safe = safeCheck ? Value::Number::IsSafe(value.As<v8::NumberObject>()->ToNumber(Node::Context()).ToLocalChecked()->Value() ) : true;
            if(safe){
                this->val = value.As<v8::NumberObject>()->ToNumber(Node::Context()).ToLocalChecked();
                this->_val = this->val->Value();
            }
        }
    }
}
Value::Number::Double::Double(v8::Local<v8::Number> value , bool safeCheck) : Double(){
    if(!value.IsEmpty()){
        bool safe = safeCheck ? Value::Number::IsSafe(value.As<v8::Number>()->Value()) : true;
        if(safe){
            this->val = value.As<v8::Number>();
            this->_val = this->val->Value();
        }
    }
}
Value::Number::Double::Double(v8::MaybeLocal<v8::Value> value , bool safeCheck) : Double(value.ToLocalChecked(),safeCheck){}
Value::Number::Double::~Double(){}
v8::Local<v8::Value> Value::Number::Double::Cast(){ return this->val.As<v8::Value>();}
double Value::Number::Double::CppValue(){ return this->_val;}
Value::Number::Double::operator v8::Local<v8::Number>(){ return this->val;}
Value::Number::Double::operator v8::Local<v8::Number>() const{ return this->val;}
Value::Number::Double::operator v8::Local<v8::Value>(){ return this->val.As<v8::Value>();}
Value::Number::Double::operator v8::Local<v8::Value>() const{ return this->val.As<v8::Value>();}
Value::Number::Double::operator Value::TypeDef(){ return "Double";}
Value::Number::Double::operator Value::TypeDef() const{ return "Double";}
Value::Number::Double::operator long() const {return this->_val;}
Value::Number::Double Value::Number::Double::operator=(const Double& value){
    this->val = value.val;
    this->_val = value._val;
    return *this;
}
Value::Number::Double Value::Number::Double::operator=(const Double* value){
    this->val = value->val;
    this->_val = value->_val;
    return *this;
}
Value::Number::Double Value::Number::Double::operator=(double value){
    this->val = Value::CreateValue(value).As<v8::Number>();
    this->_val = value;
}
Value::Number::Double Value::Number::Double::operator=(int value){
    this->val = Value::CreateValue(static_cast<double>(value)).As<v8::Number>();
    this->_val = static_cast<double>(value);
}
Value::Number::Double Value::Number::Double::operator=(unsigned long int value){
    this->val = Value::CreateValue(static_cast<double>(value)).As<v8::Number>();
    this->_val = static_cast<double>(value);
}
Value::Number::Double Value::Number::Double::operator=(long long int value){
    this->val = Value::CreateValue(static_cast<double>(value)).As<v8::Number>();
    this->_val = static_cast<double>(value);
}
v8::Local<v8::Number> Value::Number::Double::operator->(){ return this->val;}
  
        























// Int
Value::Int::Int(){
    this->val = v8::Local<v8::Int32>();
};
Value::Int::Int(int value) : val(Value(value)){};
Value::Int::Int(unsigned long int value):Int(){
    Value::Number num(value);
    if(!num.IsEmpty() && (num.IsInt16() || num.IsInt32())){
        this->val = num.Cast().As<v8::Int32>();
        this->_v = this->val->Value();
    }
};
Value::Int::Int(long long int value):Int(){
    Value::Number num(value);
    if(!num.IsEmpty() && (num.IsInt16() || num.IsInt32())){
        this->val = num.Cast().As<v8::Int32>();
        this->_v = this->val->Value();
    }
};
Value::Int::Int(double value):Int(){
    Value::Number num(value);
    if(!num.IsEmpty() && (num.IsInt16() || num.IsInt32())){
        this->val = num.Cast().As<v8::Int32>();
        this->_v = this->val->Value();
    }
};
Value::Int::Int(v8::Local<v8::Int32> value) : Int(){
    this->val = value;
    this->_v = this->val->Value();
};
Value::Int::Int(v8::Local<v8::BigInt> value):Int(){
    Value::Number num(value);
    if(!num.IsEmpty() && (num.IsInt16() || num.IsInt32())){
        this->val = num.Cast().As<v8::Int32>();
        this->_v = this->val->Value();
    }
};
Value::Int::Int(v8::Local<v8::Integer> value) : val(value.As<v8::Int32>()){};
Value::Int::Int(v8::Local<v8::Value> value): Int(){
    Value::Number num(value);
    if(!num.IsEmpty() && (num.IsInt16() || num.IsInt32())){
        this->val = num.Cast().As<v8::Int32>();
        this->_v = this->val->Value();
    }
};
Value::Int::~Int(){}
bool Value::Int::IsEmpty(){return this->val.IsEmpty();}
int Value::Int::CppValue(){return this->_v;}
v8::Local<v8::Value> Value::Int::Cast(){return this->val.As<v8::Value>();}
Value::Int::operator Value(){ return Value(this->val);}
Value::Int::operator Value() const { return Value(this->val);}
Value::Int::operator v8::Local<v8::Value>(){return this->val.As<v8::Value>();}
Value::Int::operator v8::Local<v8::Value>()const{return this->val.As<v8::Value>();}
Value::Int::operator v8::Local<v8::Int32>(){return this->val;}
Value::Int::operator v8::Local<v8::Int32>()const{return this->val;}
Value::Int::operator Value::TypeDef(){return Value::TypeDef("Int");}
Value::Int::operator Value::TypeDef()const{return Value::TypeDef("Int");}
Value::Int::operator int(){return this->_v;}
Value::Int::operator int()const{return this->_v;}
Value::Int Value::Int::operator=(int value){
    this->val.Clear();
    this->val= Value::CreateValue(value).As<v8::Int32>();
    this->_v = value;
    return *this;
}
Value::Int Value::Int::operator=(const Value::Int& value){
    this->val.Clear();
    this->val = value.val;
    this->_v =value._v;
    return *this;
}
Value::Int Value::Int::operator=(const Value::Int* value){
    this->val.Clear();
    this->val = value->val;
    this->_v =value->_v;
    return *this;
}



































// Int
Value::BigInt::BigInt(){
    this->val = v8::Local<v8::BigInt>();
};
Value::BigInt::BigInt(double value) :BigInt(){
    Value::Number num(value);
    if(!num.IsEmpty() && num.IsInt64()){
        this->val = Value::CreateValue(static_cast<long long int>(num.CppValue())).As<v8::BigInt>();
        this->_v = static_cast<long long int>(num.CppValue());
    }
};
Value::BigInt::BigInt(unsigned long int value) :BigInt() {
    Value::Number num(value);
    if(!num.IsEmpty() && num.IsInt64()){
        this->val = Value::CreateValue(static_cast<long long int>(num.CppValue())).As<v8::BigInt>();
        this->_v = static_cast<long long int>(num.CppValue());
    }
};
Value::BigInt::BigInt(long long int value) :BigInt(){
    Value::Number num(value);
    if(!num.IsEmpty() && num.IsInt64()){
        this->val = Value::CreateValue(static_cast<long long int>(num.CppValue())).As<v8::BigInt>();
        this->_v = static_cast<long long int>(num.CppValue());
    }
}; 
Value::BigInt::BigInt(v8::Local<v8::BigInt> value){
    Value::Number num(value);
    if(!num.IsEmpty() && num.IsInt64()){
        this->val = Value::CreateValue(static_cast<long long int>(num.CppValue())).As<v8::BigInt>();
        this->_v = static_cast<long long int>(num.CppValue());
    }
};
Value::BigInt::BigInt(v8::Local<v8::Value> value){
    Value::Number num(value);
    if(!num.IsEmpty() && num.IsInt64()){
        this->val = Value::CreateValue(static_cast<long long int>(num.CppValue())).As<v8::BigInt>();
        this->_v = static_cast<long long int>(num.CppValue());
    }
};
Value::BigInt::~BigInt(){}
bool Value::BigInt::IsEmpty(){return this->val.IsEmpty();}
long long int Value::BigInt::CppValue(){return this->_v;}
v8::Local<v8::Value> Value::BigInt::Cast(){return this->val.As<v8::Value>();}
Value::BigInt::operator Value(){ return Value(this->val);}
Value::BigInt::operator Value() const { return Value(this->val);}
Value::BigInt::operator v8::Local<v8::Value>(){return this->val;}
Value::BigInt::operator v8::Local<v8::Value>()const{return this->val;}
Value::BigInt::operator v8::Local<v8::BigInt>(){return this->val;}
Value::BigInt::operator v8::Local<v8::BigInt>() const{return this->val;}
Value::BigInt::operator Value::TypeDef(){return Value::TypeDef("BigInt");}
Value::BigInt::operator Value::TypeDef()const{return Value::TypeDef("BigInt");}
Value::BigInt::operator long(){return this->_v;}
Value::BigInt::operator long()const{return this->_v;}
Value::BigInt Value::BigInt::operator=(unsigned long int value){
    this->val.Clear();
    this->val= Value::CreateValue(value).As<v8::BigInt>();
    this->_v = value;
    return *this;
}
Value::BigInt Value::BigInt::operator=(long long int value){
    this->val.Clear();
    this->val= Value::CreateValue(value).As<v8::BigInt>();
    this->_v = value;
    return *this;
}
Value::BigInt Value::BigInt::operator=(const Value::BigInt& value){
    this->val.Clear();
    this->val = value.val;
    return *this;
}
Value::BigInt Value::BigInt::operator=(const Value::BigInt* value){
    this->val.Clear();
    this->val = value->val;
    return *this;
}





