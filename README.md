# ezito-sqlite
This package provides synchronous and asynchronous operations using ezito-async and sqlite3.


# Installing
```bash
npm install ezito-sqlite
```



# Methods
- [open] sync
- [close] sync
- [all] sync
- [allPromise] async
- [run] sync
- [runPromise] async
- [get] sync
- [getPromise] async
- [each] sync
- [eachPromise] async
- [exec] sync
- [exists] sync
- [execPromise] async
- [on] eventEmmiter.on
- [once] eventEmmiter.once
- [extension] sync
- [function] sync
- [aggregate] sync
- [backup] async
- [iterate] sync
- [prepare] sync
- [config.safeMode] sync
- [config.busyTime] sync
- [transaction] sync
- [transactionDeferred] sync
- [transactionImmediate] sync
- [transactionExclusive] sync


# Example open
- `ezito-sqlite.open` This method works simultaneously .<br/>
- if the first parameter is null or undefined or ":memory:" or an -empty string, the database is created in memory .<br/>
- The second parameter of this method specifies the int value of the database opening mode, the default value is 6, both read and write and create.
```js
const sqlite3 = require('ezito-sqlite');
const db = new sqlite3();
db.open("") ; // memory
db.open(undefined); // memory
db.open(null); // memory
db.open("./test.db" , sqlite3.OPEN_MODE.READONLY);
db.open("./test.db" , sqlite3.OPEN_MODE.READWRITE);
db.open("./test.db" , sqlite3.OPEN_MODE.EXISTS); // 6 

db.open("./test.db" , { openMode : 6 , busyTime : 30000 });
db.open("./test.db" , { openMode : 6 , busyTime : 30000 } , function(err){ });

```



# Example close
- `ezito-sqlite.close` This method works simultaneously .<br/>
```js
const sqlite3 = require('ezito-sqlite');
const db = new sqlite3();
db.open("") ; // memory
const [err ] = db.close();
db.close((err)=>console.log(err));

```


# Example all | allPromise
- `ezito-sqlite.all | ezito-sqlite.allPromise` all method works simultaneously and allPromise method works async .<br/>
<br/>
# Example all [sync]
```js
const sqlite3 = require('ezito-sqlite');
const db = new sqlite3();
db.open("") ; // memory
const [ err , rows ] = db.all("select * from test");
db.all("select * from test" , (err, rows)=>{});
const [ err , rows ] = db.all("select * from test where id = ?" , [10]);
db.all("select * from test where id = ?" , [10] , (err, rows)=>{});
const [ err , rows ] = db.all("select * from test where id = $id" , { $id : 10 });
db.all("select * from test where id = $id" , { $id : 10 } , (err,rows)=>{});
db.close();
```
# Example allPromise [async] 
- When you use async methods, you must also close the database asynchronously, this is done with nextTick ezito-sqlite
```js
const sqlite3 = require('ezito-sqlite');
const db = new sqlite3();
db.open("") ; // memory
const [ err , rows ] = db.allPromise("select * from test");
const [err ,rows] = await db.allPromise("select * from test" , (err, rows)=>{});
const [ err , rows ] = db.allPromise("select * from test where id = ?" , [10]);
db.allPromise("select * from test where id = ?" , [10] , (err, rows)=>{});
const [ err , rows ] = db.allPromise("select * from test where id = $id" , { $id : 10 });
db.allPromise("select * from test where id = $id" , { $id : 10 } , (err,rows)=>{});
db.nextTick(()=>db.close());
```




## Global-Examples

``` js
const sqlite3 = require('ezito-sqlite');
const db = new sqlite3();

const [ err ] =  db.open(":memory:");
// or
db.open(":memory:" , (err)=>{});


const [err , row ] = db.all("select * from tab;");

const [err , row ] = db.all("select * from tab where id = ? ;" , [ 1 ]);

const [err , row ] = db.all("select * from tab where id = $id ;" , { $id });


db.all("select * from test2" , (err , rows)=>{
  console.log(rows)
});


db.all("select * from test2 where id = $id" , { $id : 1 }, (err , rows)=>{
  console.log(rows)
});




const [err , row ] = db.get("select * from tab;");

const [err , row ] = db.get("select * from tab where id = ? ;" , [ 1 ]);

const [err , row ] = db.get("select * from tab where id = $id ;" , { $id });



db.get("select * from test2" , (err , rows)=>{
  console.log(rows)
});


db.get("select * from test2 where id = $id" , { $id : 1 }, (err , rows)=>{
  console.log(rows)
});



```







``` js
const sqlite3 = require('ezito-sqlite')
const db = new sqlite3();

const [ err ] =  db.open(":memory:");
// or
db.open(":memory:" , (err)=>{ });


const [err , row ] = await db.allPromise("select * from tab;");

const [err , row ] = await db.alltPromise("select * from tab where id = ? ;" , [ 1 ]);

const [err , row ] = await db.allPromise("select * from tab where id = $id ;" , { $id });


db.allPromise("select * from test2" , (err , rows)=>{
  console.log(rows)
});


db.allPromise("select * from test2 where id = $id" , { $id : 1 }, (err , rows)=>{
  console.log(rows)
});




const [err , row ] = await db.getPromise("select * from tab;");

const [err , row ] = await db.getPromise("select * from tab where id = ? ;" , [ 1 ]);

const [err , row ] = await db.getPromise("select * from tab where id = $id ;" , { $id });


db.getPromise("select * from tab;").then(([ err , row ])=>{});

db.getPromise("select * from tab where id = ? ;" , [ 1 ]).then(([ err , row ])=>{});

db.getPromise("select * from tab where id = $id ;" , { $id }).then(([ err , row ])=>{});



db.getPromise("select * from test2" , (err , rows)=>{
  console.log(rows)
});


db.getPromise("select * from test2 where id = $id" , { $id : 1 }, (err , rows)=>{
  console.log(rows)
});


```



# Example Each
- You can break the count either in serial mode or in non-serial mode
- The only difference is that in non-serialized mode you can have the data after the failure or after the process until the end, in then or using awiat
``` js

const sqlite3 = require('ezito-sqlite')
const db = new sqlite3(':memory:');

db.each("select * from test",(err,row,index)=>{
  if(index == 5000) return false;
});


db.each("select * from test", [] /** param or {} */ , (err,row,index)=>{
  if(err) return false;
  console.log(row);
  if(index == 5000) return false;
});


const [ err , row ] = db.eachPromise("select * from test",(err,row,index)=>{
  if(index == 5000) return false;
});

db.eachPromise("select * from test",(err,row,index)=>{
  if(index == 5000) return false;
}).then(([err, row])=>{
  console.log([ err , row ])
});

```




# Example function
- If an error is encountered while creating the function, it will be determined by the first value of the argument
``` js
const sqlite3 = require('ezito-sqlite');
const db = new sqlite3();
var [ err ] =  db.open(":memory:");
db.function("Hash",function(err , ...args){
    return args[0] + "ae3"; //  /:)
});
[ err ] = db.close();


/**
 ** if return object with meesage field you return error 
 */

db.function("validator",function(err , arg0){
  if(typeof arg0 != "string") return { message : "type error" }; 
  if(arg0.length < 10 ) return { message : "length error" }; 
  return arg0;
});
const [ err , rows ] = db.get("select * from test2 where name = validator(?)" , [1 ]);
console.log(err);
db.close();


```


# Example aggregate
- If an error is encountered while creating the aggregate(window function), it will be determined by the first value of the argument
``` js
const sqlite3 = require('ezito-sqlite');
const db = new sqlite3.Database();
var [ err ] =  db.open(":memory:");
db.aggregate("mid",{ 
  step : function(err , array , ...args){
    array.push(...args);
  },
  result : function(array){
    return array.length;
  }
});
db.get("select mid(id) from test"); // result mid(id) : array.length
[ err ] = db.close();
db.close();



db.open("./t.db");
db.aggregate("validator",{
  step:function(err , arr, arg0,arg1){
    arr.push(arg0);
    if(arr.length > 100 ) return { message : "custom error" };
  },
  result : function(arr){
    if(typeof arr[0] == "string") return { message : "custom error result" };
    return arr;
  }
});
const [ err , rows ] = db.get("select validator(name) from test2");
console.log(err);
db.close();


```


# Example extension
- If the api name is not mentioned, the same base file name without ext is considered Pay attention to the example below

```cpp

#include <stdio.h>
#include "sqlite3/sqlite3.h"
#include "sqlite3/sqlite3ext.h"

#ifndef __WIN32__
#define __WIN32__
#endif
#define BUILD_LIB

SQLITE_EXTENSION_INIT1;
#ifdef __WIN32__
#   ifdef BUILD_LIB
#      define LIB_CLASS __declspec(dllexport)
#   else
#      define LIB_CLASS __declspec(dllimport)
#   endif
#else
#   define LIB_CLASS 
#endif

LIB_CLASS int sqlite3_function(sqlite3 *db,  char **pzErrMsg, const sqlite3_api_routines *pApi ){
    SQLITE_EXTENSION_INIT2(pApi);
    // sqlite3_create_function_v2
    // sqlite3_create_function
    // or other
    return 0;
}

```

- windows 

```cmd
gcc -shared -o ./src/sqlite3_function.dll ./src/lib.c
```
- linux
```terminal
gcc -shared -o ./src/sqlite3_function.so  -fPIC  ./src/lib.c
```

`extension` now can using .
because you made the input name the same as the output file name, you don't need to enter the parameter entry

```js
const sqlite3 = require('ezito-sqlite');
const db = new sqlite3();
var [ err ] =  db.open(":memory:");

/*
lib.c
LIB_CLASS int sqlite3_function
*/
db.extension(require.resolve("src/sqlite3_function.dll" /*or src/sqlite3_function.so*/),function(err ){
    if(err){ ///:)
      console.error(err); // or 
    }
});
[ err ] = db.close();

```



# Example backup
`backup`

```js
const sqlite3 = require('ezito-sqlite');
const db = new sqlite3();
db.open("./t.db");
db.backup('./fff.db',  function(err , progress , total , rem ){
  console.log(`progress : `, progress , '%');
  if(prog == 100 || err ) db.close();
});
```


# Example iterate
`iterate`
```js
const sqlite3 = require('ezito-sqlite');
const db = new sqlite3();
db.open("./t.db");
var [ err , step ] = db.iterate("select * from test;" , []); 
while([ err , row ] = step()){
  if(!row) break;
  console.log(row)
}
db.close();
```
`migration`
- The names of the files must be combined with the name of the database and the word migration so that migration can find them
```js

const Migration = new Migration(); 
new Migration("./deps/migrations")
// products.migration.sql migrate to products.sqlite
// ./deps/migrations/products.migration.sql migrate to products.sqlite
// users.migration.sql migrate to users.sqlite
// ./deps/migrations/users.migration.sql migrate to users.sqlite
```


`config` sqlite3_limit <br>
[setLimit](https://www.sqlite.org/c3ref/c_limit_attached.html#sqlitelimitfunctionarg) db.config.setLimit(6 , 2);<br>
`config`
[safeMode](https://www.sqlite.org/c3ref/c_dbconfig_defensive.html#SQLITE_DBCONFIG_DEFENSIVE)db.config.safeMode(true || false)
