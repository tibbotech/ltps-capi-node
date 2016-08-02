var sleep = require('sleep'); // https://www.npmjs.com/package/sleep
var lib = require("../libs/ltps_pic.node");

var pic = new lib.Pic();
pic.initPic("s1", 32); // 32 MHz, 16 MHz or 8 MHz

for (var i = 1; i < 4; i++) // Support by Tibbit's #16, #17 and #31
{
	console.log("Configure PIC as PWM at channel %d", i);
	pic.configurePwm("s1", i); // Channels for PWM: 1, 2 or 3
	
	console.log("Start PWM at channel %d (pusle = %d, period = %d, prescaler = %d)", i, 100 * i, 512, 1);
	/*!
		\param socket I2C bus name (eg: s1, s15)
		\param channel Channel number (1, 2 or 3)
 		\param pulse PWM pulse width is defined as the base frequency clock count (0, 1, 2...1023)
		\param period PWM period is defined as the base frequency clock count (0, 4, 8...1023)
		\param prescaler Prescaler affects the base frequency (the period is multiplied to the prescaler) (1, 4, 16 or 64)
	*/
	// void startPwm(const char *socket, int channel, int pulse, int period, int prescaler);
	pic.startPwm("s1", i, 100 * i, 512, 1);
	sleep.sleep(3);
	
	console.log("Stop PWM at channel %d", i);
	pic.stopPwm("s1", i);
}

sleep.sleep(1);

for (var i = 1; i < 5; i++) // Support by Tibbit #31
{
	console.log("Configure PIC as ADC at channel %d", i);
	pic.configureAdc("s1", i); // Channels for ADC: 1, 2, 3 or 4
	sleep.sleep(1);
	
	console.log("Channel %d = %d mV", i, pic.getAdcVoltage("s1", i));
}
