# node-lwan

The ultimate goal is to replace node.js http server implementation, or atleast provide an alternative which does more of the heavy lifting down below

lwan was chosen for testing purposes but could be switched to ulib, nginx, or even undertow.

# dev
	Compile nodewith debug and gdb flags for more information - http://google.com

	configure\compile ect ect with that node executable

	node-gyp configure --python /usr/bin/python2.7 --nodedir ../node/ --debug
	node-gyp build --python /usr/bin/python2.7 --nodedir ../node/ --debug
	node-gyp rebuild --python /usr/bin/python2.7 --nodedir ../node/ --debug

	gdb --tui --args ../node/node hook.js
