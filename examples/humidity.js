var lib = require("../libs/ltps_humidity");

var data = new lib.Hih6130();
var hum = new lib.Humidity();

hum.getData("-s01", data);

console.log("RH: %d%", data.humidity);
console.log("Temperature: %d degrees Celsius", data.temperature);
console.log("Status:", data.status);