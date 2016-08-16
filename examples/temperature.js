var lib = require("../libs/ltps_temperature.node");

var temp = new lib.Temperature();
var data = new lib.TempData();

temp.getTemperature("s1", data);

if (data.status == 0)
	console.log("Temperature = %d degrees Celsius", data.temp);
else
	console.log(data.error);
