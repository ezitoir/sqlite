

const SqliteError = require("../sqlite-error");
const is = require("ezito-utils/public/is");
const trace = require("ezito-utils/public/trace");

function each(Database){
    const args = Array.prototype.slice.call(arguments).slice(1);
    const sql = args[0];
    const param = is.object(args[1]) || args[1] instanceof Array ? args[1] : args[1] != undefined ? [ args[1] ] : [];
    const callback = typeof args[1] == "function" ? args[1] : typeof args[2] == "function" ? args[2] : null;
    if(!is.string(sql) || sql.trim().length < 1) throw new SqliteError(trace.createErrorOption(1 , "sql praram must be string"));
    
    return this.Each(sql , param , function(err , rows , index){
        if(this._eventMode)if(err) this.events.emit("error", err);
        if(typeof callback == "function"){
            return callback.call(this ,err, rows , index);
        }
    });
}

module.exports = each;