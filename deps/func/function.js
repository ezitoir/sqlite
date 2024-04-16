const has = require("ezito-utils/public/object/has");
const is = require("ezito-utils/public/is");
const trace = require("ezito-utils/public/trace");
const SqliteError = require("../sqlite-error");
const defaultOption = {
    argCount : -1,
    deterministic :false,
    directOnly : false,
    safeInt : true 
};

function _function(Database){
    const args = Array.prototype.slice.call(arguments).slice(1);
    const name = args[0];
    /** @type {defaultOption} */
    const option = is.object(args[1]) ? {...defaultOption , ...args[1] } : defaultOption ;
    const callback = is.function(args[1]) ? args[1] : is.function(args[2]) ? args[2] : null;
    if(!is.string(name) || name.trim().length < 1) throw new SqliteError(trace.createErrorOption(1,"name must be string"));
    if(!is.function(callback)) throw new SqliteError(trace.createErrorOption(1,"callback must be function"));
    if(!is.number(option.argCount)) throw new SqliteError(trace.createErrorOption(1,"option.argCount must be int"));
    if((option.argCount) > 100) throw new SqliteError(trace.createErrorOption(1,"User-defined functions cannot have more than 100 arguments"));
    if(!is.boolean(option.deterministic)) throw new SqliteError(trace.createErrorOption(1,"option.deterministic must be bool"));
    if(!is.boolean(option.directOnly)) throw new SqliteError(trace.createErrorOption(1,"option.directOnly must be bool"));
    if(!is.boolean(option.safeInt)) throw new SqliteError(trace.createErrorOption(1,"option.safeInt must be boolean"));
    this.Function(name , option , callback);
}
_function.defaultOption = defaultOption;
module.exports = _function;
