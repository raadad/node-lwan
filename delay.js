var addon = require('./build/Release/delay');

var i = 0;

setInterval(function() {
  console.log(i++);
},500);

// test the delay function
addon.delay(3,'hello world',function(a,b) {
  console.log('delay : ' + a + ',' + b);
});

