var lib = require("../libs/ltps_rtc.node");

var rtc = new lib.Rtc();

var data = new lib.RtcTemp();

var i = 0;

var step1 = function()
{
	var timer = setInterval(function()
	{
		rtc.getTemperature("s1", data); // Get current temperature
		if (data.status == 0)
		{
			console.log("Temperature = %d degrees Celsius", data.temp);
			i++;
		}
		else
		{
			i = 10;
			console.log(data.error);
		}
	
		if(i==10)
		{
			clearInterval(timer);
			//step2();
		}
	},1000);
}

step1();
