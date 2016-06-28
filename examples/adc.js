var lib = require("../libs/ltps_adc.node");

var adc = new lib.Adc();

console.log("Voltage for channel 1 = %d mV", adc.getVoltage("s1", 1));
console.log("Voltage for channel 2 = %d mV", adc.getVoltage("s1", 2));
console.log("Voltage for channel 3 = %d mV", adc.getVoltage("s1", 3));
console.log("Voltage for channel 4 = %d mV", adc.getVoltage("s1", 4));