var lib = require("../libs/ltps_light.node");

var light = new lib.Light();
var data = new lib.LightData();

light.getIllumination("s1", data);
if (data.status == 0)
	console.log("Illumination = %d lx", data.ill);
else
	console.log(data.error);
