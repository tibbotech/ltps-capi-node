var lib = require("../libs/ltps_gpio.node");

var gpio = new lib.Gpio();

gpio.setDirection("S1A", 1); // 0 for "input", 1 for "output"
console.log("Direction for S1A pin:", gpio.getDirection("S1A"));

gpio.setValue("S1A", 1);
console.log("Value for S1A pin:", gpio.getValue("S1A"));