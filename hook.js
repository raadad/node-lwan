// hello.js
var addon = require('./build/Release/hook');

var xtr = function (req, res) {
    console.log("ssInternal");
    return "LOLOL";
};

var x = addon.startServer(xtr);

console.log(x);
