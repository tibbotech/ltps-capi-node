var lib = require("../libs/ltps_adc.node");

var adc = new lib.Adc();
var data = new lib.AdcData();

for (var i = 1; i < 5; i++)
{
	adc.getVoltage("s1", i, false, data); // Set the third argument in the true to get previous voltage conversion (1 reading cycle)

	if (data.status == 0)
		console.log("Voltage for channel %d = %d mV", i, data.voltage);
	else
		console.log(data.error);
}
