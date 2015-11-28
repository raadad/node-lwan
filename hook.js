// hello.js
var addon = require('./build/Debug/hook'); // MAKE SURE YOU gyp  WITH DEBUG or this wont exist

xtr = function (req, res) { //function that should be run from lwan request
    console.log("AND I RAN, I RAN SO FAR AWAY, I JUST RAN, I RAN ALL NIGHT AND DAY!!!!!"); // proof that it executed
    return "SO YOU THINK YOU CAN RETURN ME TO THE C++ WORLD AND THEN TO C WORLD TO BE FAST YO"; // what the http server should serve back
};

console.log("ABOUT TO ENTER INTO THE DARKSIDE");
var x = addon.startServer(xtr); // hit
console.log("OMG I SURVIVED");

setTimeout(function(){
	xtr();
	console.log("WHY DID YOU KEEP ME RUNNING FOR SO LONG");
}, 100000);


console.log("@@@@@@@@@@@@@@@@@@@@@@@@@");
console.log(x);
console.log("@@@@@@@@@@@@@@@@@@@@@@@@@");
