var addon = require('../libs/ltps_awiegand.node').WiegandAsync,
    events = require('events');

inherits(addon, events);

module.exports = addon;

function inherits(target, source)
{
	for (var k in source.prototype)
		target.prototype[k] = source.prototype[k];
}

var asyncWiegand = new addon();

asyncWiegand.on("dataReceivedEvent", (a, b) => console.log("Wiegand data received: key - %s, length - %d bits", a, b));
asyncWiegand.setPollPeriod(100); // Optionally, default value is 100 ms
asyncWiegand.startLoop();

asyncWiegand.addWatch("s05");
asyncWiegand.addWatch("s07");

//asyncWiegand.removeWatch("s05");

setInterval(() => {}, 5000); // Prevent module exit