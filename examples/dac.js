var lib = require("../libs/ltps_dac");

var dac = new lib.Dac();

console.log("Set 2500 mV for channel 1");
dac.setVoltage("s3", 1, 2500); // Voltage values: -10000...10000

console.log("Set 5000 mV for channel 2");
dac.setVoltage("s3", 2, 5000);

console.log("Set -7500 mV for channel 3");
dac.setVoltage("s3", 3, -7500);

console.log("Set 10000 mV for channel 4");
dac.setVoltage("s3", 4, 10000);