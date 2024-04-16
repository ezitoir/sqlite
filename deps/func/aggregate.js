


function aggregate(Database , name , func ){
    const args = typeof func == "object" ? func : { step : null , result : null };
    if(typeof args.result != "function") args.result = ()=>{};
    this.AggregateFunction(name , new Array , args.step , args.result );
}

module.exports = aggregate;
