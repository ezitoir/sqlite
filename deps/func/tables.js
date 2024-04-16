

const filter = require("ezito-utils/public/object/filter");
/** 
 ** @returns {Object}
 **/
function tables(){
    const result = {};
    /** @type {Array} data */
    var [ err , data ] = this.all("SELECT name FROM sqlite_master WHERE type='table';");
    if(err) return [ err , null ];
    for (const iterator of data) {
        [ err , data ] = this.all(`PRAGMA table_info(${iterator.name});`);
        if(err) return [ err , null ];
        result[iterator.name] = {};
        for (const iterator2 of data) {
            result[iterator.name] = { ... result[iterator.name] , [iterator2.name] : filter(iterator2 , { name : false }) };
        }
    }
    return result;
}

module.exports = tables;
