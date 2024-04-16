
require("ezito-require");
const sqlite3 = require("ezito-bindings")("ezito_sqlite.node"); 
const open = require("./func/open");
const close = require("./func/close");
const all = require("./func/all");
const allPromise = require("./func/allPromise");
const get = require("./func/get");
const getPromise = require("./func/getPromise");
const exec = require("./func/exec");
const execPromise = require("./func/execPromise");
const each = require("./func/each");
const eachPromise = require("./func/eachPromise");
const runPromise = require("./func/runPromise");
const run = require("./func/run");
const nextTick = require("./func/nexTick");
const extension = require("./func/extension");
const serialize = require("./func/serialize");
const aggregate = require("./func/aggregate");
const transaction = require("./func/transaction");
const transactionDeferred = require("./func/transactionDeferred");
const transactionImmediate = require("./func/transactionImmediate");
const transactionExclusive = require("./func/transactionExclusive");
const backup = require("./func/backup");
const iterate = require("./func/iterate");
const exists = require("./func/exitsts");
const existsPromise = require("./func/exitstsPromise");
const { EventEmitter } = require("events");
const _function = require("./func/function");
const tables = require("./func/tables");
const Statement = require("./func/statemenet");
const prepare = require("./func/prepare");
const openOption = open.defaultOption;
const fucntionOption = _function.defaultOption;

class Database extends sqlite3.Database {
    /**
     ** @param {string} filename
     ** @param {function} callback 
     ** @returns {Database}
     **/
    open(filename , callback){};
    /**
     ** @param {string} filename
     ** @param {openOption} option
     ** @param {function} callback
     ** @returns {Database}
     **/
    open(filename,option,callback){};
    /**
     ** @param {string} sql 
     ** @param {function} callback 
     ** @returns {Database}
     **/
    all(sql,callback){};
    /**
     ** @param {string} sql 
     ** @param {Array} param 
     ** @param {function} callback
     ** @returns {Database}
     **/
    all(sql,param,callback){};
    /**
     ** @param {string} sql 
     ** @param {function} callback
     ** @returns {Promise} 
     **/
    allPromise(sql,callback){};
    /**
     ** @param {string} sql 
     ** @param {param} param 
     ** @param {function} callback
     ** @returns {Promise} 
     **/
    allPromise(sql,param,callback){};
    /**
     ** @param {string} sql
     ** @param {function} callback
     ** @returns {Database} 
     **/
     get(sql,callback){};
     /**
      ** @param {string} sql 
      ** @param {Array} param 
      ** @param {function} callback
      ** @returns {Database}
      **/
    get(sql,param,callback){};
     /**
      ** @param {string} sql 
      ** @param {Array} param
      ** @returns {Database}
      **/
    iterate(sql,param){};
    /**
     ** @param {string} sql 
     ** @param {function} callback
     ** @returns {Promise} 
     **/
    getPromise(sql,callback){};
     /**
      ** @param {string} sql 
      ** @param {param} param 
      ** @param {function} callback
      ** @returns {Promise} 
      **/
    getPromise(sql,param,callback){};
    /**
    ** @param {string} sql 
    ** @param {function} callback
    **/
    run(sql , callback){};
    /**
     ** @param {string} sql 
     ** @param {param} param 
     ** @param {function} callback
     ** @returns {Database} 
     **/
    run(sql,param,callback){};
    /**
     ** @param {string} sql
     ** @param {function} callback
     ** @returns {Promise} 
     **/
    runPromise(sql , callback){};
    /**
     ** @param {string} sql 
     ** @param {param} param 
     ** @param {function} callback
     ** @returns {Promise} 
     **/
    runPromise(sql, param,callback){};
    /**
     ** @param {function} callback
     ** @returns {Database} 
     **/
    close(){};
    /**
     ** @param {string} sql 
     ** @param {string} param 
     ** @param {function} callback
     ** @returns {Database} 
     **/
    each(sql,param,callback){};
    /**
     ** @param {string} sql
     ** @param {function} callback
     ** @returns {Database} 
     **/
    each(sql,callback){}
    /**
     ** @param {string} sql  
     ** @param {function} callback
     ** @returns {Promise} 
     **/
    eachPromise(sql,callback){};
    /**
     ** @param {string} sql 
     ** @param {param} param 
     ** @param {function} callback
     ** @returns {Promise} 
     **/
    eachPromise(sql,param,callback){};
    /**
     ** @param {string} sql  
     ** @param {function} callback
     ** @returns {Database} 
     **/
    exec(){};
    /**
     ** @param {string} sql  
     ** @param {(Object | Array)} param
     ** @returns {Database}
     **/
    exitsts(sql,param){};
    /**
     ** @param {string} sql  
     ** @param {(Object | Array)} param
     ** @returns {Database}
     **/
    exitstsPromise(sql,param){};
    /**
     ** @param {string} sql
     ** @param {function} callback
     ** @returns {Promise} 
     **/
    execPromise(){};
    /**
     ** @param {string} name
     ** @param {function} fn
     ** @returns {Database} 
     **/
    function(name ,fn){};
    /**
     ** @param {string} name
     ** @param {fucntionOption} option
     ** @param {function} fn
     ** @returns {Database} 
     **/
     function(name , option ,fn){};
    /**
     ** @param {string} dest_file 
     ** @param {string} attached 
     ** @param {function} callback 
     **/
    backup(dest_file , attached , callback){};
    /**
     ** @param {string} dest_file 
     ** @param {function} callback 
     **/
    backup(dest_file , callback){};
    /**
     ** @param {string} name
     ** @param {function} fn
     ** @returns {Database} 
     **/
    aggregate(name,fn){};
    /**
     ** @param {string} sql 
     ** @returns {Statement}
     **/
    prepare(sql){};
    /** 
     ** @param {string} file_name
     ** @param {string} entry
     ** @param {function} callback
     ** @returns {Database}
     **/
    extension(file_name , entry , callback){};
    /**
     ** @param {string} name
     **/
    serialize(name){};
    /** 
     ** @param {string} file_name 
     ** @param {function} callback
     ** @returns {Database}
     **/
    extension(file_name , callback){};
    /**
     ** @param {function} callback 
     **/
    transaction(callback){};
    /**
     ** @param {function} callback 
     **/
    transactionImmediate(callback){};
    /**
     ** @param {function} callback 
     **/
    transactionDeferred(callback){};
    /**
     ** @param {function} callback 
     **/
    transactionExclusive(callback){};
    nextTick(){};
    tables(){};
    config = {
      /**
       * @param {boolean} enable 
       */
      safeMode(enable){},
      /**
       * @param {int} time \\ ms
       */
      setBusyTime(time){},
      /**
       * 
       * @param {Number} id 
       * @param {Number} new_val 
       */
      setLimit(id , new_val){},
      /**
       * 
       * @param {Number} id 
       * @param {Boolean} mode 
       */
      dbConfig(id,mode){}
    } 
    events;
    _open;
    _memory;
    _safe;
    on(){};
    once(){};
    removeAllListeners(){};
    removeListener(){};
    /**
     ** @param {string} file
     ** @param {open.defaultOption} option 
     **/
    constructor(file , option){
        super(arguments);
        this.open = open.bind(this,option);
        this.close = close.bind(this,null);
        this.all = all.bind(this,null);
        this.allPromise = allPromise.bind(this,null); 
        this.get = get.bind(this,null);
        this.getPromise = getPromise.bind(this,null);
        this.exec = exec.bind(this,null);
        this.execPromise = execPromise.bind(this,null);
        this.exitsts = exists.bind(this,null);
        this.exitstsPromise = existsPromise.bind(this,null);
        this.each = each.bind(this,null);
        this.eachPromise = eachPromise.bind(this,null);
        this.extension = extension.bind(this,null);
        this.serialize = serialize.bind(this,null);
        this.function = _function.bind(this,null);
        this.tables = tables.bind(this,null);
        this.prepare = prepare.bind(this,null);
        this.iterate = iterate.bind(this,null);
        this.aggregate = aggregate.bind(this, null);
        this.backup = backup.bind(this,null);
        this.runPromise = runPromise.bind(this , null);
        this.run = run.bind(this,null);
        this.transaction = transaction.bind(this, null);
        this.transactionDeferred = transactionDeferred.bind(this,null);
        this.transactionImmediate = transactionImmediate.bind(this,null);
        this.transactionExclusive = transactionExclusive.bind(this,null);
        this.events = new EventEmitter();
        this.on = this.events.on.bind(this.events);
        this.once = this.events.once.bind(this.events); 
        this.removeAllListeners = this.events.removeAllListeners.bind(this.events);
        this.removeListener= this.events.removeListener.bind(this.events);
        this.nextTick = nextTick.bind(this,null);
        this.config.safeMode = this.ConfigSafeMode.bind(this);
        this.config.setBusyTime = this.ConfigBusyTime.bind(this);
        this.config.setLimit = this.ConfigLimit.bind(this);
        this.config.dbConfig = this.ConfigDatabase.bind(this);
        if(Array.prototype.slice.call(arguments).length > 0){
          this.open(...arguments);
        }
    }
};

Database.OPEN_MODE   = sqlite3.Database.OPEN_MODE;
Database.ERROR_CODES = sqlite3.Database.ERROR_CODES;

module.exports = Database;
