
const { thread } = require("ezito-async");
function execPromise(Database){
    const args = Array.prototype.slice.call(arguments).slice(1);
    const sql = args[0]; 
    const callback = typeof args[1] == "function" ? args[1] : null;
    const $this = this;
    
    return new Promise(function(resolve){
        thread(function(){ 
            resolve(
                $this.Exec(sql , function( err , rows ){
                    if(this._eventMode)if(err) this.events.emit("error", err);
                    if(typeof callback == "function"){
                        return callback.call( this , err , rows );
                    }
                    return [ err , rows ];
                })
            );
        })
    })
}

module.exports = execPromise;