
const path = require("path");
function extension(Database){
    const args = Array.prototype.slice.call(arguments).slice(1);
    const entry_file = args[0];
    const entry = typeof args[1] == "string"  ? args[1] : "";
    const callback = typeof args[1] == "function" ? args[1] : typeof args[2] == "function" ? args[2] : null;

    const auto_entry = path.basename(entry_file).slice(0 , -path.extname(entry_file).length);
    return this.Extension(entry_file , entry , function(err){
        if(err){
            return this.Extension(entry_file , auto_entry , function(err){
                if(typeof callback == "function"){
                    return callback.all(this , err, null);
                }
                return [ err , null ];
            });
        }
        if(typeof callback == "function"){
            return callback(err, null);
        }
        return [ err , null];
    });
}

module.exports = extension;