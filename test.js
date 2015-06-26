var hi = require("./build/Release/SSPWrapper");

console.log("Attempting to open port");
var port = hi.OpenSSPPort("not a port");

console.log("Closing port");
hi.CloseSSPPort(port);
