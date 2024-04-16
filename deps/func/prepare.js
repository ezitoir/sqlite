


const Statement  = require("./statemenet");

function prepare(Database , sql){
    return new Statement(this, sql);
}

prepare = prepare;
module.exports= prepare;
