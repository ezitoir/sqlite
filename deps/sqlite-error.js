

const EzitoError = require("ezito-utils/public/trace/error");
class SqliteError extends EzitoError {
    constructor(){
        super(...arguments);
    }
}

module.exports = SqliteError;
