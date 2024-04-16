
#ifndef V8_EZITO_OBJECT_CLASS_HELPER
#define V8_EZITO_OBJECT_CLASS_HELPER
#include <stdarg.h>
#include <string>
#include "node.h"

#define NODE_STRING_TYPE 1
#define NODE_NUMBER_TYPE 2
#define NODE_INT_TYPE 3
#define NODE_INT16_TYPE 4
#define NODE_INT32_TYPE 5
#define NODE_INT64_TYPE 6
#define NODE_FLOATE_TYPE 7
#define NODE_DOUBLE_TYPE 8
#define NODE_FUNCTION_TYPE 9
#define NODE_OBJECT_TYPE 10
#define NODE_UNDEFINED_TYPE 11
#define NODE_NULL_TYPE 12

#define MAX_INT_NODE_SAFE 9007199254740991
#define MAX_INT_SIGNED_NODE_SAFE -9007199254740991
#define MAX_INT_64 9223372036854775808
#define MAX_SIGNED_INT_64 -9223372036854775808
#define MAX_INT_32 0x7fffffff
#define MAX_SIGNED_INT_32 -0x7fffffff
#define MAX_INT_16 32768
#define MAX_SIGNED_INT_16 -32768

#define MAX_DOUBLE_NODE_SAFE 562949953421312
#define MAX_SIGNED_DOUBLE_NODE_SAFE -562949953421312

class Value {
    private:
    v8::Local<v8::Value> val;
    public:
    typedef const v8::FunctionCallbackInfo<v8::Value>& Argumants;
    class String;
    class Number;
    class Int;
    class BigInt;
    class Boolean;
    class Function;
    class Array;
    class Null;
    class Undefined;
    class Object;   
    class Null;
    class Udefined;
    class Class;
    class TypeDef;
    Value();
    Value(void *);
    Value(const char *);
    Value(int);
    Value(signed long int value); // big int
    Value(unsigned long int value); // big int 
    Value(signed long long int value); // big int 64
    Value(unsigned long long int value); // big int 64
    Value(bool);
    Value(double);
    Value(float);
    Value(v8::Local<v8::Primitive>);
    Value(v8::FunctionCallback , const char * , v8::Local<v8::Value>);
    Value(v8::Local<v8::Value>);
    Value(v8::Local<v8::Object>);
    Value(v8::Local<v8::Array>);
    Value(v8::Local<v8::String>);
    Value(v8::Local<v8::Int32>);
    Value(v8::Local<v8::BigInt>);
    Value(v8::Local<v8::Number>);
    Value(v8::Local<v8::External>);
    Value(v8::Local<v8::Boolean>);
    Value(v8::Local<v8::Function>);
    Value(v8::MaybeLocal<v8::Value>);
    Value(v8::MaybeLocal<v8::Array>);
    Value(v8::MaybeLocal<v8::String>);
    Value(v8::MaybeLocal<v8::Int32>); 
    Value(v8::MaybeLocal<v8::BigInt>);
    Value(v8::MaybeLocal<v8::Number>);
    Value(v8::MaybeLocal<v8::Boolean>);
    Value(v8::MaybeLocal<v8::Object>); 
    Value(v8::MaybeLocal<v8::Function>);
    v8::Local<v8::Value> AutoCast();
    v8::Local<v8::Value> Cast();
    ~Value();


    bool IsEmpty();
    bool IsString();
    bool IsBoolean();
    bool IsFunction();
    bool IsInt();
    bool IsBigInt();
    bool IsArray();
    bool IsNumber();
    bool IsNull();
    bool IsUndefined();
    bool IsObject();
    v8::Local<v8::Value> ToLocal();

    static bool ISEmpty(v8::Local<v8::Value> , bool * safe=(bool*)nullptr);
    static bool ISString(v8::Local<v8::Value> , bool * safe=(bool*)nullptr);
    static bool ISBoolean(v8::Local<v8::Value>, bool * safe=(bool*)nullptr);
    static bool ISFunction(v8::Local<v8::Value> , bool * safe=(bool*)nullptr);
    static bool ISInt(v8::Local<v8::Value> , bool * safe=(bool*)nullptr);
    static bool ISBigInt(v8::Local<v8::Value> , bool * safe=(bool*)nullptr);
    static bool ISArray(v8::Local<v8::Value> , bool * safe=(bool*)nullptr);
    static bool ISNumber(v8::Local<v8::Value> , bool * safe=(bool*)nullptr);
    static bool ISNull(v8::Local<v8::Value> , bool * safe=(bool*)nullptr);
    static bool ISUndefined(v8::Local<v8::Value> , bool * safe=(bool*)nullptr);
    static bool ISObject(v8::Local<v8::Value> , bool * safe=(bool*)nullptr);

    operator v8::Local<v8::Value>();
    operator v8::Local<v8::Array>();
    operator v8::Local<v8::String>();
    operator v8::Local<v8::Number>();
    operator v8::Local<v8::Object>();
    operator v8::Local<v8::Function>();
    operator v8::Local<v8::FunctionTemplate>();
    operator v8::Local<v8::Boolean>();
    operator v8::Local<v8::Int32>();
    operator v8::Local<v8::External>();
    operator v8::Local<v8::Name>();  
    operator v8::Local<v8::BigInt>();  

    operator Value::String();
    operator Value::Class();
    operator Value::Object();
    operator Value::Array();
    operator Value::Function();
    operator Value::Number(); 
    operator Value::Int(); 
    operator Value::BigInt(); 
    operator Value::Boolean(); 


    operator v8::Local<v8::Value> () const;
    operator v8::Local<v8::Array> () const;
    operator v8::Local<v8::String> () const;
    operator v8::Local<v8::Number> () const;
    operator v8::Local<v8::Object> () const;
    operator v8::Local<v8::Function> () const;
    operator v8::Local<v8::FunctionTemplate> () const;
    operator v8::Local<v8::Boolean> () const;
    operator v8::Local<v8::Int32> () const;
    operator v8::Local<v8::External>() const;
    operator v8::Local<v8::Name>() const;  
    operator v8::Local<v8::BigInt>() const; 

    operator Value::String() const;
    operator Value::Class() const;
    operator Value::Object() const;
    operator Value::Array() const;
    operator Value::Function() const;
    operator Value::Number() const;
    operator Value::Int() const;
    operator Value::BigInt() const;
    operator Value::Boolean() const; 

    Value operator=(v8::Local<v8::Value>);
    Value operator=(v8::Local<v8::Array>);
    Value operator=(v8::Local<v8::String>);
    Value operator=(v8::Local<v8::Number>);
    Value operator=(v8::Local<v8::Object>);
    Value operator=(v8::Local<v8::Function>);
    Value operator=(v8::Local<v8::Boolean>);
    Value operator=(v8::Local<v8::Int32>);
    Value operator=(v8::Local<v8::Name>);

    Value operator=(Value::String);
    Value operator=(Value::Number);
    Value operator=(Value::Int);
    Value operator=(Value::BigInt);
    Value operator=(Value::Function);
    Value operator=(Value::Array);
    Value operator=(Value::Object);
    Value operator=(Value::Undefined);
    Value operator=(Value::Null);
    Value operator=(Value::Class);
    Value operator=(const Value& value);
    Value operator=(const Value* value);

    v8::Local<v8::Value> operator->();

    v8::Local<v8::Array> ToV8Array();
    v8::Local<v8::String> ToV8String();
    v8::Local<v8::Object> ToV8Object();
    v8::Local<v8::Number> ToV8Number();
    v8::Local<v8::Int32> ToV8Int();
    v8::Local<v8::Function> ToV8Function();
    v8::Local<v8::Boolean> ToV8Boolean();


    static v8::Local<v8::Value> CreateValue(const char*);
    static v8::Local<v8::Value> CreateValue(int);
    static v8::Local<v8::Value> CreateValue(signed long int value);
    static v8::Local<v8::Value> CreateValue(unsigned long int value);
    static v8::Local<v8::Value> CreateValue(unsigned long long int value);
    static v8::Local<v8::Value> CreateValue(signed long long int value);
    static v8::Local<v8::Value> CreateValue(bool);
    static v8::Local<v8::Value> CreateValue(double);
    static v8::Local<v8::Value> CreateValue(float);
    static v8::Local<v8::Value> CreateValue(void(*)(const v8::FunctionCallbackInfo<v8::Value>&) , const char * , v8::Local<v8::Value>);

    static const char * ToCppString(v8::Local<v8::Value>);
    static const char * ToCppString(v8::Local<v8::String>);
    static int ToCppInt(v8::Local<v8::Value>);
    static int ToCppInt(v8::Local<v8::Int32>);
    static signed long long ToCppBigInt(v8::Local<v8::Value>);
    static signed long long ToCppBigInt(v8::Local<v8::BigInt>);
    static bool ToCppBool(v8::Local<v8::Value>);
    static bool ToCppBool(v8::Local<v8::Boolean>);
    static double ToCppDouble(v8::Local<v8::Value>);
    static double ToCppDouble(v8::Local<v8::Number>);

    static const char * ToCppString(v8::MaybeLocal<v8::Value>);
    static int ToCppInt(v8::MaybeLocal<v8::Value>);
    static bool ToCppBool(v8::MaybeLocal<v8::Value>);
    static double ToCppDouble(v8::MaybeLocal<v8::Value>);

    String ToString();
    Int ToInt();
    BigInt ToBigInt();
    Number ToNumber();
    Boolean ToBoolean();
    Function ToFunction();
    Object ToObject();
    Array ToArray();

    class TypeDef {
        private:
        std::string str;
        public:
        TypeDef();
        TypeDef(const char *);
        ~TypeDef();
        operator char*();
        operator char*()const;
    };

    class String {
        private :
        v8::Local<v8::String> val;
        public:
        int length = 0;
        String();
        String(const char *);
        String(const unsigned char *);
        String(v8::Local<v8::String> value);
        String(v8::Local<v8::Value> value);
        String(v8::MaybeLocal<v8::Value> value);
        ~String();
        const char * CppValue();
        bool IsEmpty(); 
        v8::Local<v8::Value> AutoCast();
        v8::Local<v8::Value> Cast();
        operator Value();
        operator Value()const;
        operator v8::Local<v8::Value>();
        operator v8::Local<v8::Value> ()const;
        operator v8::Local<v8::String>();
        operator v8::Local<v8::String> () const;
        operator char*();
        operator char*() const;
        operator TypeDef(){ return TypeDef("String");}
        operator TypeDef() const { return TypeDef("String");}
        v8::Local<v8::String> operator ->(){return this->val;}; 
        String operator=(const String& string);
        String operator=(const String* string);
        String operator=(const char *);
        bool operator==(const char *) const;
    };



    class Class {
        private:
        v8::Local<v8::FunctionTemplate> class_context;
        v8::Local<v8::Value> external_data;
        v8::Local<v8::String> class_name;
        public:
        Class();
        Class( v8::FunctionCallback callback, const char * class_name );
        Class( v8::FunctionCallback callback, const char * class_name , v8::Local<v8::Value> data); 
        Class( v8::FunctionCallback callback, const char * class_name , v8::Local<v8::Function> extends);
        Class( v8::FunctionCallback callback, const char * class_name , v8::Local<v8::FunctionTemplate> extends);
        Class(
            v8::FunctionCallback callback, 
            const char * class_name ,
            v8::Local<v8::FunctionTemplate> extends, 
            v8::Local<v8::Value> data);
        virtual ~Class();
        void SetMethod(v8::FunctionCallback callback , const char * func_name , v8::Local<v8::Value> data=v8::Local<v8::Value>());
        void SetField(
            v8::AccessorGetterCallback getter_callback ,
            v8::AccessorSetterCallback setter_callbak,
            const char * field_name ,
            v8::Local<v8::Value> data=v8::Local<v8::Value>()
        );
        void SetProperty(const char * pro_name , v8::Local<v8::Value> value);
        void SetProperty(v8::AccessorGetterCallback callback , const char * func_name , v8::Local<v8::Value> data=v8::Local<v8::Value>());
        void SetConstructor(v8::FunctionCallback callback , v8::Local<v8::Value> data = v8::Local<v8::Value>());
        void SetName(const char * class_name);
        v8::Local<v8::Value> AutoCast();
        v8::Local<v8::Value> Cast();
        operator Value();
        operator Value()const;
        operator v8::Local<v8::Function>();
        operator v8::Local<v8::Function>() const;
        operator v8::Local<v8::FunctionTemplate>();
        operator v8::Local<v8::FunctionTemplate>() const;
        operator v8::Local<v8::Value>();
        operator v8::Local<v8::Value>() const;
        Class operator=(const Class& string);
        Class operator=(const Class* string);
        v8::Local<v8::FunctionTemplate> operator ->(); 
    };



    class Object {
        private :
        v8::Local<v8::Object> val;
        public:
        Object(); 
        Object(v8::Local<v8::Object> value);
        Object(v8::Local<v8::Array> value);
        Object(v8::Local<v8::Value> value);
        Object(v8::MaybeLocal<v8::Object> value);
        Object(v8::MaybeLocal<v8::Array> value);
        Object(v8::MaybeLocal<v8::Value> value);
        v8::Local<v8::Value> AutoCast();
        v8::Local<v8::Value> Cast();
        ~Object();
        void CppValue();
        bool IsEmpty();
        operator Value();
        operator Value()const;
        operator v8::Local<v8::Value>();
        operator v8::Local<v8::Value> () const;
        operator v8::Local<v8::Object>();
        operator v8::Local<v8::Object> () const;
        operator TypeDef(){ return TypeDef("Object");}
        operator TypeDef() const{ return TypeDef("Object");}
        Object operator=(const Object& string);
        Object operator=(const Object* string);
        v8::Local<v8::Object> operator ->(){return this->val;}; 
        void Set(int , int);
        void Set(int , double);
        void Set(int , const char*);
        void Set(int , bool);
        void Set(int , Object);
        void Set(int , v8::Local<v8::Value>);
        void Set(const char* , int);
        void Set(const char* , double);
        void Set(const char* , const char*);
        void Set(const char* , bool);
        void Set(const char* , Object);
        void Set(const char* , v8::Local<v8::Value>);

        Value Get(const char*);
        Value Get(int);
    };


    class Function {
        private :
        v8::Local<v8::Function> val;
        public:
        Function();
        Function(void * data);
        Function(v8::FunctionCallback , const char * , v8::Local<v8::Value> data = v8::Local<v8::Value>());
        Function(v8::Local<v8::Value> value); 
        Function(v8::MaybeLocal<v8::Value> value); 
        Function(v8::Local<v8::Function> value);
        Function(v8::MaybeLocal<v8::Function> value);
        Function(v8::Local<v8::FunctionTemplate> value);
        v8::Local<v8::Value> AutoCast();
        v8::Local<v8::Value> Cast();
        ~Function();
        void CppValue();
        bool IsEmpty();
        operator Value();
        operator Value()const;
        operator v8::Local<v8::Value>();
        operator v8::Local<v8::Value> () const;
        operator v8::Local<v8::Function>();
        operator v8::Local<v8::Function> () const; 
        operator TypeDef(){ return TypeDef("Function");}
        operator TypeDef() const { return TypeDef("Function");}
        v8::Local<v8::Function> operator ->(){return this->val;}; 
        Function operator=(const Function& value);
        Function operator=(const Function* value);

        Value Call(int count , ...);
        Value Call(v8::Local<v8::Value>context, int count , ...);
    };

 
    class Number{
        private:
        v8::Local<v8::Value> val;
        short int type;
        double _v;
        public:
        class Int32;
        class Int64;
        class Double;
        Number();
        Number(double , bool safeCheck = false);
        Number(int);
        Number(unsigned long int , bool safeCheck = false);
        Number(long long int , bool safeCheck = false);
        Number(v8::Local<v8::Number> , bool safeCheck = false);
        Number(v8::Local<v8::Int32>);
        Number(v8::Local<v8::BigInt> , bool safeCheck = false);
        Number(v8::Local<v8::Value> , bool safeCheck = false);
        Number(v8::MaybeLocal<v8::Value> , bool safeCheck = false);
        void Clear();
        double CppValue();
        v8::Local<v8::Value> AutoCast();
        v8::Local<v8::Value> Cast();
        bool IsInt(bool safeCheck = false);
        bool IsInt16();
        bool IsInt32();
        bool IsInt64(bool safeCheck = false);
        bool IsEmpty();
        bool IsDouble(bool safeCheck = false);
        bool IsSafe();

        Number::Int32 ToInt32();
        Number::Int64 ToInt64();
        Number::Double ToDouble();

        static bool IsInt(double , bool safeCheck = false);
        static bool IsInt16(double);
        static bool IsInt32(double);
        static bool IsInt64(double , bool safeCheck = false);
        static bool IsInt16(long long int);
        static bool IsInt16(unsigned long int);
        static bool IsInt16(int);
        static bool IsInt32(long long int);
        static bool IsInt32(unsigned long int);
        static bool IsInt32(int);
        static bool IsInt64(long long int , bool safeCheck = false);
        static bool IsInt64(unsigned long int , bool safeCheck = false);
        static bool IsInt64(int , bool safeCheck = false);
        static bool IsDouble(double , bool safeCheck = false);
        static bool IsSafe(long long int);
        static bool IsSafe(double);
        
        operator Value();
        operator Value() const;
        operator v8::Local<v8::Value> ();
        operator v8::Local<v8::Value> () const;
        operator v8::Local<v8::Int32> ();
        operator v8::Local<v8::Int32> () const;
        operator v8::Local<v8::BigInt>();
        operator v8::Local<v8::BigInt>() const;
        operator v8::Local<v8::Number>();
        operator v8::Local<v8::Number>() const;
        operator TypeDef();
        operator TypeDef() const;
        operator double()const;
        Number operator=(const Number& value);
        Number operator=(const Number* value);
        Number operator=(double);
        Number operator=(int);
        Number operator=(unsigned long int);
        Number operator=(long long int);
        v8::Local<v8::Value> operator->(); 

        class Int32{
            private:
            v8::Local<v8::Int32> val;
            int _val;
            public:
            Int32();
            Int32(int);
            Int32(double);
            Int32(unsigned long int);
            Int32(long long int);
            Int32(Value::Number);
            Int32(v8::Local<v8::Int32>);
            Int32(v8::Local<v8::Value>);
            Int32(v8::Local<v8::Number>);
            Int32(v8::MaybeLocal<v8::Value>);
            ~Int32();
            v8::Local<v8::Value> Cast();
            int CppValue();
            bool IsEmpty();
            operator v8::Local<v8::Int32>();
            operator v8::Local<v8::Int32>() const;
            operator v8::Local<v8::Value>();
            operator v8::Local<v8::Value>() const;
            operator TypeDef();
            operator TypeDef() const;
            operator int() const;
            Number::Int32 operator=(const Int32& value);
            Number::Int32 operator=(const Int32* value);
            Number::Int32 operator=(double);
            Number::Int32 operator=(int);
            Number::Int32 operator=(unsigned long int);
            Number::Int32 operator=(long long int);
            v8::Local<v8::Int32> operator->(); 
        };

        class Int64{
            private:
            v8::Local<v8::BigInt> val;
            long long int _val;
            public:
            Int64(); 
            Int64(int);
            Int64(double , bool safeCheck = false);
            Int64(unsigned long int );
            Int64(long long int , bool safeCheck = false);
            Int64(Value::Number , bool safeCheck = false);
            Int64(v8::Local<v8::BigInt> , bool safeCheck = false);
            Int64(v8::Local<v8::Value> , bool safeCheck = false);
            Int64(v8::Local<v8::Number> , bool safeCheck = false);
            Int64(v8::MaybeLocal<v8::Value> , bool safeCheck = false);
            ~Int64();
            v8::Local<v8::Value> Cast();
            long long int CppValue();
            bool IsEmpty();
            operator v8::Local<v8::BigInt>();
            operator v8::Local<v8::BigInt>() const;
            operator v8::Local<v8::Value>();
            operator v8::Local<v8::Value>() const;
            operator TypeDef();
            operator TypeDef() const;
            operator long() const;
            Number::Int64 operator=(const Int64& value);
            Number::Int64 operator=(const Int64* value);
            Number::Int64 operator=(int);
            Number::Int64 operator=(double);
            Number::Int64 operator=(unsigned long int);
            Number::Int64 operator=(long long int);
            v8::Local<v8::BigInt> operator->(); 
        };

        class Double {
            private:
            v8::Local<v8::Number> val;
            double _val;
            public:
            Double(); 
            Double(double , bool safeCheck = false);
            Double(v8::Local<v8::Value> , bool safeCheck = false);
            Double(v8::Local<v8::Number> , bool safeCheck = false);
            Double(v8::MaybeLocal<v8::Value>, bool safeCheck = false);
            ~Double();
            v8::Local<v8::Value> Cast();
            double CppValue();
            operator v8::Local<v8::Number>();
            operator v8::Local<v8::Number>() const;
            operator v8::Local<v8::Value>();
            operator v8::Local<v8::Value>() const;
            operator TypeDef();
            operator TypeDef() const;
            operator long() const;
            Number::Double operator=(const Double& value);
            Number::Double operator=(const Double* value);
            Number::Double operator=(int);
            Number::Double operator=(double);
            Number::Double operator=(unsigned long int);
            Number::Double operator=(long long int);
            v8::Local<v8::Number> operator->(); 
        };
    };



    class Int {
        private :
        v8::Local<v8::Int32> val;
        int _v;
        public:
        Int();
        Int(int);
        Int(unsigned long int);
        Int(long long int);
        Int(double);
        Int(v8::Local<v8::Int32> value);
        Int(v8::Local<v8::BigInt> value);
        Int(v8::Local<v8::Integer> value);
        Int(v8::Local<v8::Value> value); 
        Int(v8::MaybeLocal<v8::Value> value); 
        v8::Local<v8::Value> Cast();
        ~Int();
        int CppValue();
        bool IsEmpty();
        operator Value();
        operator Value()const;
        operator v8::Local<v8::Value>();
        operator v8::Local<v8::Value> () const;
        operator v8::Local<v8::Int32>();
        operator v8::Local<v8::Int32>() const;
        operator TypeDef();
        operator TypeDef()const;
        operator int();
        operator int() const; 
        operator long();
        operator long() const;
        v8::Local<v8::Int32> operator ->(){return this->val;};
        Int operator=(const Int& value);
        Int operator=(const Int* value);
        Int operator=(int);
    };

    class BigInt {
        private :
        v8::Local<v8::BigInt> val;
        long long int _v;
        public:
        BigInt();
        BigInt(double); 
        BigInt(unsigned long int value); 
        BigInt(long long int value); 
        BigInt(v8::Local<v8::BigInt> value);
        BigInt(v8::Local<v8::Value> value);
        BigInt(v8::Local<v8::Number> value);
        BigInt(v8::MaybeLocal<v8::Value> value);
        v8::Local<v8::Value> Cast();
        ~BigInt();
        long long int CppValue(); 
        bool IsEmpty();
        operator Value();
        operator Value()const;
        operator v8::Local<v8::Value>();
        operator v8::Local<v8::Value> () const; 
        operator v8::Local<v8::BigInt>();
        operator v8::Local<v8::BigInt>() const;
        operator TypeDef();
        operator TypeDef() const;
        operator long();
        operator long() const;
        v8::Local<v8::BigInt> operator ->(){return this->val;};
        BigInt operator=(const BigInt& value);
        BigInt operator=(const BigInt* value); 
        BigInt operator=(unsigned long int);
        BigInt operator=(long long int);
    };

  
    class Boolean {
        private :
        v8::Local<v8::Boolean> val;
        public:
        Boolean();
        Boolean(bool);
        Boolean(v8::Local<v8::Boolean> value);
        Boolean(v8::Local<v8::Value> value);
        Boolean(v8::MaybeLocal<v8::Value> value);
        ~Boolean();
        bool CppValue();
        bool IsEmpty();
        v8::Local<v8::Value> AutoCast();
        v8::Local<v8::Value> Cast();
        operator Value();
        operator Value()const;
        operator v8::Local<v8::Value>();
        operator v8::Local<v8::Value>() const;
        operator v8::Local<v8::Boolean>() ;
        operator v8::Local<v8::Boolean>() const;
        operator TypeDef(){ return TypeDef("Boolean");}
        operator TypeDef() const { return TypeDef("Boolean");}
        operator bool() const;
        v8::Local<v8::Boolean> operator ->(){return this->val;}; 
        Boolean operator=(const Boolean& value);
        Boolean operator=(const Boolean* value);
        Boolean operator=(bool);
    };

    class Null {
        private :
        v8::Local<v8::Primitive> val;
        public:
        Null();
        ~Null();
        int CppValue();
        bool IsEmpty();
        v8::Local<v8::Value> AutoCast();
        v8::Local<v8::Value> Cast();
        operator Value();
        operator Value()const;
        operator v8::Local<v8::Value>();
        operator v8::Local<v8::Value>() const;
        operator v8::Local<v8::Primitive>();
        operator v8::Local<v8::Primitive>() const;
        operator TypeDef(){ return TypeDef("Null");}
        operator TypeDef() const { return TypeDef("Null");}
        Null operator=(const Null& value);
        Null operator=(const Null* value); 
    }; 
    
    class Undefined {
        private :
        v8::Local<v8::Primitive> val;
        public:
        Undefined();
        ~Undefined();
        int CppValue();
        bool IsEmpty();
        v8::Local<v8::Value> AutoCast();
        v8::Local<v8::Value> Cast();
        operator Value();
        operator Value()const;
        operator v8::Local<v8::Value>();
        operator v8::Local<v8::Value>() const;
        operator TypeDef(){ return TypeDef("Undefined");}
        operator TypeDef() const { return TypeDef("Undefined");}
        operator int();
        operator int() const; 
        Undefined operator=(const Undefined& value);
        Undefined operator=(const Undefined* value); 
    };



    class Array {
        private :
        v8::Local<v8::Array> val;
        v8::Local<v8::Object> arr_object;
        Value::Object array_global;
        public:
        int length;
        Array();
        Array(v8::Local<v8::Array> value);
        Array(v8::Local<v8::Value> value);
        Array(v8::Local<v8::Object> value);
        Array(v8::MaybeLocal<v8::Array> value);
        Array(v8::MaybeLocal<v8::Value> value);
        Array(v8::MaybeLocal<v8::Object> value);
        ~Array();
        void Push(v8::Local<v8::Value>);
        void Push(const char *);
        void Push(int);
        void Push(bool);
        void Push(double);
        bool CppValue();
        bool IsEmpty(); 
        v8::Local<v8::Value> AutoCast();
        v8::Local<v8::Value> Cast();
        Value Get(int);
        operator Value();
        operator Value()const;
        operator v8::Local<v8::Value>();
        operator v8::Local<v8::Value>() const;
        operator v8::Local<v8::Array>();
        operator v8::Local<v8::Array>() const;
        operator TypeDef(){ return TypeDef("Array");}
        operator TypeDef() const { return TypeDef("Array");}
        Value operator[](int);
        Value operator[](int) const;
        v8::Local<v8::Array> operator ->(){return this->val;}; 
        Array operator=(const Array& value);
        Array operator=(const Array* value);
    };
    





    class DynamicArray {
        private :
        v8::Local<v8::Object> val;
        void init();
        public:
        int length;
        DynamicArray();
        DynamicArray(v8::Local<v8::Array> value);
        DynamicArray(v8::Local<v8::Object> value);
        DynamicArray(v8::Local<v8::Value> value);
        DynamicArray(v8::MaybeLocal<v8::Array> value);
        DynamicArray(v8::MaybeLocal<v8::Object> value);
        DynamicArray(v8::MaybeLocal<v8::Value> value);
        ~DynamicArray();
        void Push(v8::Local<v8::Value>);
        void Push(const char *);
        void Push(int);
        void Push(bool);
        void Push(double);
        static v8::Local<v8::Array> ObjectToArray(v8::Local<v8::Object> , int);
        bool CppValue();
        bool IsEmpty();
        operator Value();
        operator Value()const;
        operator v8::Local<v8::Value>();
        operator v8::Local<v8::Value>() const;
        operator v8::Local<v8::Array>();
        operator v8::Local<v8::Array>() const;
        operator TypeDef(){ return TypeDef("Array");}
        operator TypeDef() const { return TypeDef("Array");}
        v8::Local<v8::Object> operator->(); 
        DynamicArray operator=(const DynamicArray& value);
        DynamicArray operator=(const DynamicArray* value);
    }; 
};
















class Node {
    private: 
    public:
    class Context;
    class Isolate;
    class Global;
    class Throw;
    Node();
    ~Node(); 

    class Isolate {
        private:
        v8::Isolate * val;
        public:
        Isolate();
        ~Isolate();
        operator v8::Isolate*();
        operator v8::Isolate*()const;
        v8::Isolate * operator ->();
    };

    class Context {
        private:
        v8::Local<v8::Context> val;
        public:
        Context();
        ~Context();
        operator v8::Local<v8::Context>();
        operator v8::Local<v8::Context>()const;
        v8::Context * operator ->();
    };

    class Throw {
        private:
        public:
        class Error;
        class Exception;
        Throw();
        ~Throw();

        class Exception {
            private:
            public:
            class Error;
            class RangeError;
            class ReferenceError;
            class TypeError;
            class SyntaxError; 
            Exception(); 
            ~Exception(); 
            class TypeError{
                private:
                public:
                TypeError(const char *);
                ~TypeError();
                operator v8::Local<v8::Value>();
                operator v8::Local<v8::Value>() const;
                operator void(){return;}
            };
            class RangeError{
                private:
                public:
                RangeError(const char *);
                ~RangeError();
                operator v8::Local<v8::Value>();
                operator v8::Local<v8::Value>() const;
            };
            class ReferenceError{
                private:
                public:
                ReferenceError(const char *);
                ~ReferenceError();
                operator v8::Local<v8::Value>();
                operator v8::Local<v8::Value>() const;
            };
            class SyntaxError{
                private:
                public:
                SyntaxError(const char *);
                ~SyntaxError();
                operator v8::Local<v8::Value>();
                operator v8::Local<v8::Value>() const;
            };
            class Error{
                private:
                public:
                Error(const char *);
                ~Error();
                operator v8::Local<v8::Value>();
                operator v8::Local<v8::Value>() const;
            };
            static void Argumants(const char * name , Value::TypeDef type);
            static void Constructor(const char * name);
        };
    };
};

#endif