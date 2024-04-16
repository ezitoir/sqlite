

function exists(Database){
    const args = Array.prototype.slice.call(arguments).slice(1);
    const sql = args[0]; 
    const param = args[1] instanceof Array || (args[1] instanceof Object && !(args[1] instanceof Function)) ? args[1] : [];
    return this.Exists(sql , param);
}

module.exports = exists;