const { thread } = require("ezito-async");



function backup(Database){
    const args = Array.prototype.slice.call(arguments).slice(1);
    const dest_name = args[0];
    const param = typeof args[1] == "string" ? args[1] : "main";
    const callback = typeof args[1] == "function" ? args[1] : typeof args[2] == "function" ? args[2] : null;
    thread(()=>{
        this.Backup(dest_name , param , function (err , progress , total , rem ){
            if(this._eventMode)if(err) this.events.emit("error", err);
            if(typeof callback == "function"){
                return callback.call(this ,err , (progress ?? 0).toFixed(0) , total , rem);
            }
        });
    })
}

module.exports = backup;
