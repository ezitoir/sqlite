
 
function exec(Database){
    const args = Array.prototype.slice.call(arguments).slice(1);
    const sql = args[0]; 
    const callback = typeof args[1] == "function" ? args[1] : null;
    return this.Exec(sql , function( err , rows){
        if(this._eventMode)if(err) this.events.emit("error", err);
        if(typeof callback == "function"){ 
            return callback.call( this ,err , rows); 
        }
        return [ err , rows ];
    }); 
}

module.exports = exec;