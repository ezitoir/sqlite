const { sync, queue } = require("ezito-async");



function close(Database){
    const args = Array.prototype.slice.call(arguments).slice(1); 
    const callback = typeof args[0] == "function" ? args[0] :  null;
    return this.Close(function(err){
        if(this._eventMode){
            if(!err) this.events.emit("close");
            else this.events.emit("error", err);
        }
        if(typeof callback == "function"){
            return callback.call( this , err , null);
        }
        return [ err , null ];
    });
}

module.exports= close;