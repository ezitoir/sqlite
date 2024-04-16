const is = require("ezito-utils/public/is");
const trace = require("ezito-utils/public/trace");
const Database = require("../sqlite3");
const SqliteError = require("../sqlite-error");
const all = require("./all");
const get = require("./get");
const run = require("./run");
const each = require("./each");
const allPromise = require("./allPromise");
const getPromise = require("./getPromise");
const eachPromise = require("./eachPromise");
const execPromise = require("./execPromise");

/**
 ** 
 **/
class Statement {
    /** @type {string} */
    sql = "";
    /**
     ** @param {Database} db 
     ** @param {string} sql
     **/
    constructor(db , sql){
        if(!is.string(sql)) throw new SqliteError(trace.createErrorOption(1 , "sql arg must be string"));
        this.sql = sql ;
        this.all = all.bind(db , null , sql);
        this.get = get.bind(db , null , sql);
        this.run = run.bind(db , null , sql);
        this.each = each.bind(db, null ,sql);
        this.exec = this.exec.bind(db , null , sql);
        this.allPromise = allPromise.bind(db , null ,sql);
        this.getPromise = getPromise.bind(db , null , sql);
        this.eachPromise = eachPromise.bind(db , null , sql);
        this.execPromise = execPromise.bind(db , null , sql);
    }
    all(){};
    get(){};
    run(){};
    each(){};
    exec(){};
    allPromise(){};
    getPromise(){};
    runPromise(){};
    eachPromise(){};
    execPromise(){};
}



module.exports = Statement;




