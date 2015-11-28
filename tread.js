var addon = require('./build/Debug/tread'); // MAKE SURE YOU gyp  WITH DEBUG or this wont exist

var xtr = function (req, res) { //function that should be run from lwan request
    console.log("AND I RAN, I RAN SO FAR AWAY, I JUST RAN, I RAN ALL NIGHT AND DAY!!!!!"); // proof that it executed
    return "SO YOU THINK YOU CAN RETURN ME TO THE C++ WORLD AND THEN TO C WORLD TO BE FAST YO"; // what the http server should serve back
};

var x = addon.startServer(xtr); // hit
console.log("IM BACK");
