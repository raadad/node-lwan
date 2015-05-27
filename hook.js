// hello.js
var addon = require('./build/Release/hook');

console.log(addon.startServer(
    { testa:"wooohoo" }
)); // 'world'
