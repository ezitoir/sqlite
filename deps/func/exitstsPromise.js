const { thread } = require("ezito-async");


function existsPromise(Database){
    const args = Array.prototype.slice.call(arguments).slice(1);
    const sql = args[0]; 
    const param = args[1] instanceof Array || (args[1] instanceof Object && !(args[1] instanceof Function)) ? args[1] : [];
    const $this = this;
    return new Promise(resolve => {
        thread(()=>{
            resolve($this.Exists(sql , param))
        });
    })
}

module.exports = existsPromise;