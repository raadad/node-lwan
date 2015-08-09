set -e
node-gyp build --python /usr/bin/python2.7 --nodedir ~/workspace/node
~/workspace/node/node hook.js;
