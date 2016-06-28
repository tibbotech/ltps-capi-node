var lib = require("../libs/ltps_temperature.node");

var temp = new lib.Temperature();

console.log("Temperature = %d degrees Celsius", temp.getTemperature("s1"));