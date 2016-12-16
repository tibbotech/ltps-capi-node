var lib = require("../libs/ltps_spi.node");
var buf = require('buffer');

var spi = new lib.LtpsSpi();

var bus = spi.getSpiBusNum("s1");

if (bus >= 0)
{
	var res = spi.setDev(bus, 0); // Use functions getBus/getDev to get values
	
	if (res >= 0)
	{
		spi.setMode(0); // Use function getMode to get value (possible arguments - 0...3: http://docs.tibbo.com/taiko/ssi_modes.htm)
		spi.setBits(8); // use function getBits to get value
		// setSpeed/getSpeed
		// setDelay/getDelay
		
		// Below example for RTC Tibbit (get temperature)
		
		var bufW = new buf.Buffer([0x11, 0x00, 0x00]); // Apply 0 byte as register
		var bufR = new buf.Buffer([0x00, 0x00, 0x00]);
		
		bufR = spi.WR(bufW, 3); // Just ignore the return result if you want to write only
		
		// Reads 2 bytes always from 1 byte
		var temp_msb = bufR[1];
		var temp_lsb = bufR[2] >> 6;
		
		var nint;
		
		if ((temp_msb & 0x80) != 0)
			nint = temp_msb | ~((1 << 8) - 1);
		else
			nint = temp_msb;

    	var rv = 0.25 * temp_lsb + nint;
    	
    	console.log("Temperature:", rv);
	}
	else
		console.log("Device not found");
}
else
	console.log("Socket not found");
