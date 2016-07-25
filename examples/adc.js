var lib = require("../libs/ltps_adc.node");

var adc = new lib.Adc();

console.log("Voltage for channel 1 = %d mV", adc.getVoltage("s1", 1)); // Get actual voltage value (2 reading cycles)
console.log("Voltage for channel 2 = %d mV", adc.getVoltage("s1", 2)); // Get actual voltage value (2 reading cycles)
console.log("Voltage for channel 3 = %d mV", adc.getVoltage("s1", 3, false)); // Get actual voltage value (2 reading cycles) (false is by default)
console.log("Voltage for channel 4 = %d mV", adc.getVoltage("s1", 4, true)); // Get previous voltage conversion (1 reading cycle)