var addon = require('../libs/ltps_agpio').GpioAsync,
    events = require('events');

inherits(addon, events);

module.exports = addon;

function inherits(target, source)
{
	for (var k in source.prototype)
		target.prototype[k] = source.prototype[k];
}

var asyncGpio = new addon();

asyncGpio.on("valueChangeEvent", (a, b) => console.log("GPIO value for socket %s changed to %d", a, b));
asyncGpio.setPollPeriod(25); // Optionally, default value is 25 ms
asyncGpio.startLoop();

asyncGpio.addWatch("S1A");
asyncGpio.addWatch("S1B");
asyncGpio.addWatch("S1C");
asyncGpio.addWatch("S1D");

//asyncGpio.removeWatch("S1A");

setInterval(() => {}, 5000); // Prevent module exit