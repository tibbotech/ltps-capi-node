var sleep = require('sleep'); // https://www.npmjs.com/package/sleep
var lib = require("../libs/ltps_pic");

var pic = new lib.Pic();
pic.initPic("s1", 32); // 32 MHz, 16 MHz or 8 MHz

for (var i = 1; i < 4; i++) // Support by Tibbit's #16, #17 and #31
{
	console.log("Configure PIC as PWM at channel %d", i);
	pic.configurePwm("s1", i);
	
	sleep.sleep(1);
	
	console.log("Start PWM at channel %d (pusle = %d, period = %d, prescaler = %d)", i, 100, i * 300, 1);
	pic.startPwm("s1", i, 100, i * 300, 1);
	sleep.sleep(3);
	
	console.log("Stop PWM at channel %d", i);
	pic.stopPwm("s1", i);
}

sleep.sleep(1);

for (var i = 1; i < 5; i++) // Support by Tibbit #31
{
	console.log("Configure PIC as ADC at channel %d", i);
	pic.configureAdc("s1", i);
	sleep.sleep(1);
	
	console.log("Channel %d = %d mV", i, pic.getAdcVoltage("s1", i));
}
