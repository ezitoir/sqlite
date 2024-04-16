


function serialize(Database){
    const args = Array.prototype.slice.call(arguments).slice(1);
    const name = args[0];
    const callback = typeof args[1] == "function" ? args[1] : null;
    return this.Serialize( name , function(err , buffer){
        if(this._eventMode)if(err) this.events.emit("error", err);
        if(typeof callback == "function"){
            return callback.call(this,err, buffer);
        }
        return [ err , buffer ];
    })
}

module.exports = serialize;