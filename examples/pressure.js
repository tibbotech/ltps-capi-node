var lib = require("../libs/ltps_pressure");

var data = new lib.PresData();
var pres = new lib.Pressure();

pres.getData("s1", data);

console.log("Pressure = %d mm Hg", data.pressure);
console.log("Temperature = %d degrees Celsius", data.temperature);