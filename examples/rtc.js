var lib = require("../libs/ltps_rtc.node");

var rtc = new lib.Rtc();

var data = new lib.RtcTemp();

var i = 0;

var temperature = function()
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
	
		if (i == 10)
		{
			clearInterval(timer);
			i = 0;
			clock();
		}
	}, 1000);
}

var clock = function()
{
	var ts = new lib.RtcTime();
	ts.sec = 0;
	ts.min = 20;
	ts.hour = 15;
	ts.mday = 23;
	ts.mon = 9;
	ts.year = 2016;
	ts.wday = 5;
	
	var clock = new lib.RtcClock();
	clock.time = ts;
	
	rtc.setTime("s1", clock); // Set current time
	
	if (clock.status == 0)
	{
		console.log("Time has been successfully installed");
	}
	else
	{
		console.log(status.error);
	}
	
	var timer = setInterval(function()
	{
		rtc.getTime("s1", clock); // Get current time
		if (clock.status == 0)
		{
			console.log("The time now is: %d sec, %d min, %d hour, %d wday, %d mday, %d mon, %d year, %d syear", 
				clock.time.sec, clock.time.min, clock.time.hour, clock.time.wday, clock.time.mday, clock.time.mon, clock.time.year, clock.time.year_s);
			i++;
		}
		else
		{
			i = 10;
			console.log(clock.error);
		}
	
		if (i == 10)
		{
			clearInterval(timer);
			alarms();
		}
	}, 1000);
}

var alarms = function()
{
	var result = new lib.RtcResult();
	
	rtc.stopAlarm1("s1", result); // Clear Alarm 1 triggered status
	
	if (result.status == 0)
	{
		console.log("Alarm 1 triggered status successfully cleared");
	}
	else
	{
		console.log(result.error);
	}
	
	rtc.stopAlarm2("s1", result); // Clear Alarm 2 triggered status
	
	if (result.status == 0)
	{
		console.log("Alarm 2 triggered status successfully cleared");
	}
	else
	{
		console.log(result.error);
	}
	
	
	var alarm1 = new lib.RtcAlarm();
	
	alarm1.sec = 30;
	alarm1.min = 21;
	alarm1.hour = 15;
	alarm1.day = 23;
	
	// Component to be checked to trigger the alarm:
	// seconds (false to enable, true to disable) - does not matter for Alarm 2
   // minutes (false to enable, true to disable)
   // hours (false to enable, true to disable)
   // days (false to enable, true to disable)
   // wdays (Day of week == true/day of month == false)
	var flags = new lib.RtcAlarmFlags();

	flags.seconds = false;
	flags.minites = false;
	flags.hours = false;
	flags.days = false;
	flags.wdays = false;
	
	rtc.setAlarm1("s1", alarm1, flags); // Set Alarm 1 time
	
	if (flags.status == 0)
	{
		console.log("Alarm 1 time successfully set");
	}
	else
	{
		console.log(flags.error);
	}
	
	rtc.getAlarm1("s1", alarm1, flags); // Get Alarm 1 time
    
	if (flags.status == 0)
	{
		console.log("Alarm 1 time: %d sec, %d min, %d hour, %d wday, flag seconds = %d, flag minutes = %d, flag hours = %d, flag days = %d, flag wdays = %d",
			alarm1.sec, alarm1.min, alarm1.hour, alarm1.day, flags.seconds, flags.minites, flags.hours, flags.days, flags.wdays);
	}
	else
	{
		console.log(flags.error);
	}
	
	
	var alarm2 = new lib.RtcAlarm();
	
	alarm2.sec = 0; // Does not matter for Alarm 2
	alarm2.min = 21;
	alarm2.hour = 15;
	alarm2.day = 23;

	flags.seconds = false; // Does not matter for Alarm 2
	flags.minites = false;
	flags.hours = false;
	flags.days = false;
	flags.wdays = false;
	
	rtc.setAlarm2("s1", alarm2, flags); // Set Alarm 2 time
	
	if (flags.status == 0)
	{
		console.log("Alarm 2 time successfully set");
	}
	else
	{
		console.log(flags.error);
	}
	
	rtc.getAlarm2("s1", alarm2, flags); // Get Alarm 2 time
    
	if (flags.status == 0)
	{
		console.log("Alarm 2 time: %d min, %d hour, %d wday, flag minutes = %d, flag hours = %d, flag days = %d, flag wdays = %d",
			alarm2.min, alarm2.hour, alarm2.day, flags.minites, flags.hours, flags.days, flags.wdays);
	}
	else
	{
		console.log(flags.error);
	}
	
	
	rtc.enableAlarms("s1", true, true, result); // Activate alarms pin (INT/MISO pin will be set to LOW when alarms triggered)
    
	if (result.status == 0)
	{
		console.log("Alarms pin was successfully activated");
	}
	else
	{
		console.log(result.error);
	}
	
	
	var a1 = false;
	var a2 = false;
	
	var timer = setInterval(function()
	{
		var clock = new lib.RtcClock();
		rtc.getTime("s1", clock); // Get current time
		if (clock.status == 0)
		{
			console.log("The time now is: %d sec, %d min, %d hour, %d wday, %d mday, %d mon, %d year, %d syear", 
				clock.time.sec, clock.time.min, clock.time.hour, clock.time.wday, clock.time.mday, clock.time.mon, clock.time.year, clock.time.year_s);
		}
		else
		{
			a1 = true;
			a2 = true;
			console.log(clock.error);
		}
		
		var status = new lib.RtcAlarmsStatus();
		
		rtc.isAlarm1Triggered("s1", status); // Check Alarm 1 triggered status
		
		if (status.status == 0)
		{
			a1 = status.triggered;
		}
		else
		{
			a1 = true;
			console.log(status.error);
		}
		
		rtc.isAlarm2Triggered("s1", status); // Check Alarm 2 triggered status
		
		if (status.status == 0)
		{
			a2 = status.triggered;
		}
		else
		{
			a2 = true;
			console.log(status.error);
		}
		
		console.log("Alarm 1 status:", a1);
		console.log("Alarm 2 status:", a2);
	
		if ((a1 == true) && (a2 == true))
		{
			console.log("All alarms triggered");			
			clearInterval(timer);
			sram();
		}
	}, 10000);
}

var sram = function()
{
	var sram = new lib.RtcSram();
	
	sram.address = 0x16;
	sram.value = 69; // 0...255
	
	rtc.setSramValue("s1", sram); // Write value to SRAM
	
	if (sram.status == 0)
	{
		console.log("Value successfully write to SRAM register");
	}
	else
	{
		console.log(sram.error);
	}
	
	rtc.getSramValue("s1", sram); // Read value from SRAM
	
	if (sram.status == 0)
	{
		console.log("Value in SRAM register:", sram.value);
	}
	else
	{
		console.log(sram.error);
	}
}

temperature();
