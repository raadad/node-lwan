{
  'variables': {
      'shared_libzip%':'true',
      'shared_libzip_includes%':'/usr/lib',
      'shared_libzip_libpath%':'/usr/include'
  },
  "targets": [
    {

    'conditions': [
            ['shared_libzip == "false"', {
                'dependencies': [
                  'deps/libzip.gyp:libzip'
                ]
            },
            {
                'libraries': [
                   '-L<@(shared_libzip_libpath)',
                   '-lz'
                ],
                'include_dirs': [
                   '<@(shared_libzip_includes)',
                   '<@(shared_libzip_libpath)/libzip/include',
                ]
            }
            ],
        ],
      "cflags_cc": ['-std=c++11'],
      "cflags_c": [  '-Wall', '-Wextra', '-Wshadow' ,'-Wconversion', '-std=gnu11', '-Wunused-variable' ],
      "target_name": "tread",
      "sources": [
        "tread.cc",
        "./lwan/common/mime-types.h",
        "./lwan/common/base64.c",
        "./lwan/common/base64.h",
        "./lwan/common/hash.c",
        "./lwan/common/hash.h",
        "./lwan/common/int-to-str.c",
        "./lwan/common/int-to-str.h",
        "./lwan/common/list.c",
        "./lwan/common/list.h",
        "./lwan/common/lwan.c",
        "./lwan/common/lwan-cache.c",
        "./lwan/common/lwan-cache.h",
        "./lwan/common/lwan-config.c",
        "./lwan/common/lwan-config.h",
        "./lwan/common/lwan-coro.c",
        "./lwan/common/lwan-coro.h",
        "./lwan/common/lwan.h",
        "./lwan/common/lwan-http-authorize.c",
        "./lwan/common/lwan-http-authorize.h",
        "./lwan/common/lwan-io-wrappers.c",
        "./lwan/common/lwan-io-wrappers.h",
        "./lwan/common/lwan-job.c",
        "./lwan/common/lwan-private.h",
        "./lwan/common/lwan-redirect.c",
        "./lwan/common/lwan-redirect.h",
        "./lwan/common/lwan-request.c",
        "./lwan/common/lwan-response.c",
        "./lwan/common/lwan-serve-files.c",
        "./lwan/common/lwan-serve-files.h",
        "./lwan/common/lwan-socket.c",
        "./lwan/common/lwan-status.c",
        "./lwan/common/lwan-status.h",
        "./lwan/common/lwan-template.c",
        "./lwan/common/lwan-template.h",
        "./lwan/common/lwan-tables.c",
        "./lwan/common/lwan-thread.c",
        "./lwan/common/lwan-trie.c",
        "./lwan/common/lwan-trie.h",
        "./lwan/common/murmur3.c",
        "./lwan/common/murmur3.h",
        "./lwan/common/reallocarray.c",
        "./lwan/common/reallocarray.h",
        "./lwan/common/realpathat.c",
        "./lwan/common/realpathat.h",
        "./lwan/common/sd-daemon.c",
        "./lwan/common/sd-daemon.h",
        "./lwan/common/strbuf.c",
        "./lwan/common/strbuf.h",
        ]
    }
  ]
}
