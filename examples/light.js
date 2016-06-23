var lib = require("../libs/ltps_light");

var light = new lib.Light();

console.log("Illumination = %d lx", light.getIllumination("s1"));