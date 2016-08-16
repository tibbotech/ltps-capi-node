var lib = require("../libs/ltps_humidity.node");

var data = new lib.HumData();
var hum = new lib.Humidity();

hum.getData("s1", data);

if (data.status == 0)
{
	console.log("RH: %d%", data.humidity);
	console.log("Temperature: %d degrees Celsius", data.temperature);
}
else
{
	console.log(data.error);
}
