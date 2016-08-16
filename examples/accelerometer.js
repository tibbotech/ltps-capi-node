var lib = require("../libs/ltps_accelerometer.node");

var accel = new lib.Accelerometer();
var data = new lib.AccelData();

accel.getData("s1", data);

if (data.status == 0)
{
	console.log("Acceleration X-axis = %d mG", data.lx);
	console.log("Acceleration Y-axis = %d mG", data.ly);
	console.log("Acceleration Z-axis = %d mG", data.lz);
}
else
{
	console.log(data.error);
}
