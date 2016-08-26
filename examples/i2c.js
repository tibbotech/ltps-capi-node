var lib = require("../libs/ltps_i2c.node");
var buf = require('buffer');

var i2c = new lib.LtpsI2C();

var buf1 = new buf.Buffer([0x01]);
i2c.write(4, 0x18, 0x08, buf1); // bus, address, register, buffer

var buf2 = new buf.Buffer([0x08, 0x01]);
i2c.write(4, 0x18, buf2); // bus, address, buffer

var buf3 = new buf.Buffer([0x00, 0x00]);
buf3 = i2c.read(4, 0x18, 0x05, 2); // bus, address, register, buffer

console.log(buf3[0]);
console.log(buf3[1]);

var buf4 = new buf.Buffer([0x00, 0x00]);
buf4 = i2c.read(4, 0x50, 2); // bus, address, buffer

console.log(buf4[0]);
console.log(buf4[1]);

var busNum = i2c.getI2CBusNum("s1"); // Get bus number for socket
console.log("Bus number for socket s1:", busNum);