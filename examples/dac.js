var lib = require("../libs/ltps_dac.node");

var dac = new lib.Dac();
var data = new lib.DacData();

for (var i = 1; i < 5; i++)
{
	dac.setVoltage("s1", i, i * 2500, data);
	if (data.status == 1)
		console.log(data.error);
	else
		console.log("Voltage %d mV for channel %d applied successfully", i * 2500, i);
}
