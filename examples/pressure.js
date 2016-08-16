var lib = require("../libs/ltps_pressure.node");

var data = new lib.PresData();
var pres = new lib.Pressure();

pres.getData("s1", data);

if (data.status == 0)
{
	console.log("Pressure = %d mm Hg", data.pressure);
	console.log("Temperature = %d degrees Celsius", data.temperature);
}
else
	console.log(data.error);
