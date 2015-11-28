set -e
./node/node ./node_modules/node-gyp/bin/node-gyp.js --nodedir ./node configure
./node/node ./node_modules/node-gyp/bin/node-gyp.js --nodedir ./node build --debug --python /usr/bin/python2.7
./node/node tread.js;

