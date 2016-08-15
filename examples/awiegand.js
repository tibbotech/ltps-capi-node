var addon = require('./ltps_awiegand.node').WiegandAsync,
    events = require('events');

inherits(addon, events);

module.exports = addon;

function inherits(target, source)
{
	for (var k in source.prototype)
		target.prototype[k] = source.prototype[k];
}

var asyncWiegand = new addon();

asyncWiegand.on("dataReceivedEvent", (a, b,c ) => console.log("Wiegand data received: socket - %s, key - %s, length - %d", a, b, c));
asyncWiegand.setPollPeriod(100); // Optionally, default value is 100 ms
asyncWiegand.startLoop();

asyncWiegand.addWatch("s05");
asyncWiegand.addWatch("s07");

//asyncWiegand.setMode("s05", 1); // 0 - Clock/data, 1 - Wiegand (default)
//asyncWiegand.setMode("s07", 1); // 0 - Clock/data, 1 - Wiegand (default)

//asyncWiegand.removeWatch("s07");
//asyncWiegand.removeWatch("s05");

setInterval(() => {}, 5000); // Prevent module exit