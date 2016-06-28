var lib = require("../libs/ltps_accelerometer.node");

var data = new lib.AccelData();
var accel = new lib.Accelerometer();

accel.getData("s1", data);

console.log("Acceleration X-axis = %d mG", data.lx);
console.log("Acceleration Y-axis = %d mG", data.ly);
console.log("Acceleration Z-axis = %d mG", data.lz);