

function transactionExclusive(Database){
    const args = Array.prototype.slice.call(arguments).slice(1);
    const callback = typeof args[0] == "function" ? args[0] : null;

    let before, after, undo;
    if (this._transaction) {
		before = ()=>this.run('SAVEPOINT `\t_es.\t`');
		after = ()=>this.run('RELEASE `\t_es.\t`');
		undo = ()=>this.run('ROLLBACK TO `\t_es.\t`');
	} else {
		before = ()=>this.run('BEGIN EXCLUSIVE');
		after = ()=>this.run('COMMIT');
		undo = ()=>this.run('ROLLBACK');
	}

	before();
	try {
		const result = callback();
		after()
		return result;
	} catch (ex) {
		if (this._transaction) {
			undo();
		}
		throw ex;
	}
}

module.exports = transactionExclusive;
