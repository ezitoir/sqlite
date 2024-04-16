const is = require("ezito-utils/public/is");
const trace = require("ezito-utils/public/trace");
const SqliteError = require("./../sqlite-error");

const defaultOption = {
    openMode : 6 ,
    busyTime : 30000,
    buffer : null,
    eventMode : false,
    safeInts : true,
    safeDouble : true,
    throwError : false,
};

function open(option){
    if(!is.object(option)) option = {};

    const args = Array.prototype.slice.call(arguments).slice(1);
    const file_name = is.buffer(args[0]) ? "" : is.string(args[0]) ? args[0].trim().toLowerCase() : args[0];
    /** @type {defaultOption} */
    const config = typeof args[1] == "object" ? {...defaultOption , ...option, ...args[1] } : {...defaultOption , ...option};
    config.buffer =  Buffer.isBuffer(args[0]) ? args[0] : null ;
    const callback = typeof args[1] == "function" ? args[1] : typeof args[2] == "function" ? args[2] : null;
    if(!is.number(config.openMode)) throw new SqliteError(trace.createErrorOption(1,"option.openMode must be int"));
    if(!is.number(config.busyTime)) throw new SqliteError(trace.createErrorOption(1,"option.busyTime must be int"));
    if(!is.boolean(config.eventMode)) throw new SqliteError(trace.createErrorOption(1,"option.eventMode must be boolean"));
    if(!is.boolean(config.safeInts)) throw new SqliteError(trace.createErrorOption(1,"option.safeInts must be boolean"));
    if(!is.boolean(config.safeDouble)) throw new SqliteError(trace.createErrorOption(1,"option.safeDouble must be boolean"));
    
    return this.Open([ null , undefined , ":memory:" ].includes(file_name) ? "" : file_name , config , function(err){
        if(this._eventMode){
            if(!err)this.events.once("error",()=>{});
        }
        function events(err, event , nt){
            if(this._eventMode){
                if(!err) this.events.emit(new String(event).toLowerCase() , err, nt);
                if(err) this.events.emit("error", err);
            }
        }
        this.Events(events.bind(this));
        if(this._eventMode){
            if(!err) this.events.emit("open" , err);
        }

        if(typeof callback == "function"){
            return callback.call( this , err , null);
        }
        return [ err , null ]
    });
}
open.defaultOption = defaultOption;
module.exports= open;
