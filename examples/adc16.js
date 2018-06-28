var lib = require("../libs/ltps_adc16.node");

var adc = new lib.Adc16();
var data = new lib.Adc16Data();

for (var i = 1; i < 5; i++)
{
	adc.getVoltage("s1", i, data);

	if (data.status == 0)
		console.log("Voltage for channel %d = %d V", i, data.voltage);
	else
		console.log(data.error);
}
