const console = require("ezito-log");
const node_path = require("path");
const node_fs = require("fs");
const readDir = require("ezito-utils/server/fs/read-directory");
const sqlite3 = require("./sqlite3");



class Migration {
    constructor(dir){
        const [ err , dir_source ] = require.resolve(dir , { dir : true , error : false });
        if(err) throw err;
        readDir(dir_source , { justFile : true , ext :[".sql"]} , function(migrate_file){
            const export_base_name= node_path.basename(migrate_file);
            if(/(.*?)\.(migration)\.sql/.test(export_base_name)){
                const export_db_name = node_path.join( dir_source , export_base_name.split(".").at(0) + ".sqlite" );
                const db = new sqlite3();
                var [ err , data ] = db.open( export_db_name , sqlite3.OPEN_MODE.MUSTEXISTS);
                if(err) console.log(console.FC(err));
                [err , data ] = db.exec(node_fs.readFileSync(migrate_file,{encoding:"utf-8"}));
                if(err) console.log(console.FC(err));
                db.close();
            }
        });
    };
}


module.exports = Migration;