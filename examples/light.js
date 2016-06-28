var lib = require("../libs/ltps_light.node");

var light = new lib.Light();

console.log("Illumination = %d lx", light.getIllumination("s1"));