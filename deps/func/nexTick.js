const { thread } = require("ezito-async");




function nextTick(Database , callback){
    thread(()=>{
        callback();
    })
}

module.exports = nextTick;