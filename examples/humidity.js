var lib = require("../libs/ltps_humidity");
var hum = new lib.Humidity();
var data = hum.getData("s9");

console.log("RH: %d%", data.humidity);
console.log("Temperature: %d degrees Celsius", data.temperature);
console.log("Status:", data.status);