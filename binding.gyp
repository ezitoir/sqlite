{
  'includes': ['src/common.gypi'],
  "targets": [
    {
      "target_name": "ezito_sqlite",
      "sources": [ 
        "src/database/sqlite-database.cpp",
        "src/node-lib/node-value.cpp",
        "src/sqlite.cc" , 
        "src/sqlite3/sqlite3.c"
      ] ,
      "conditions" : [
        ['OS=="linux"', {
            'defines': [
              'LINUX_OS',
            ],
            'include_dirs': [],
        }],
        ['OS=="win"',{
          'defines':[
            'WIN_OS'
          ],
          'include_dirs': [],
        }]
      ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "xcode_settings": {
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "CLANG_CXX_LIBRARY": "libc++",
        "MACOSX_DEPLOYMENT_TARGET": "10.7",
        'OTHER_CPLUSPLUSFLAGS': ['-std=c++11', '-stdlib=libc++'],
      },
      "msvs_settings": {
        "VCCLCompilerTool": {
          "ExceptionHandling": 1
        },
      },
      "include_dirs" : [
        "src/*"
      ],
           
  'defines': [
    'SQLITE_DEFAULT_CACHE_SIZE=-16000',
    'SQLITE_DEFAULT_FOREIGN_KEYS=1',
    'SQLITE_DEFAULT_MEMSTATUS=0',
    'SQLITE_DEFAULT_WAL_SYNCHRONOUS=1',
    'SQLITE_DQS=0',
    'SQLITE_ENABLE_COLUMN_METADATA',
    'SQLITE_ENABLE_DESERIALIZE',
    'SQLITE_ENABLE_FTS3',
    'SQLITE_ENABLE_FTS3_PARENTHESIS',
    'SQLITE_ENABLE_FTS4',
    'SQLITE_ENABLE_FTS5',
    'SQLITE_ENABLE_GEOPOLY',
    'SQLITE_ENABLE_JSON1',
    'SQLITE_ENABLE_MATH_FUNCTIONS',
    'SQLITE_ENABLE_RTREE',
    'SQLITE_ENABLE_STAT4',
    'SQLITE_ENABLE_UPDATE_DELETE_LIMIT',
    'SQLITE_LIKE_DOESNT_MATCH_BLOBS',
    'SQLITE_OMIT_DEPRECATED',
    'SQLITE_OMIT_GET_TABLE',
    'SQLITE_OMIT_PROGRESS_CALLBACK',
    'SQLITE_OMIT_SHARED_CACHE',
    'SQLITE_OMIT_TCL_VARIABLE',
    'SQLITE_SOUNDEX',
    'SQLITE_THREADSAFE=2',
    'SQLITE_TRACE_SIZE_LIMIT=32',
    'SQLITE_USE_URI=0',
    ]
  }
]
}