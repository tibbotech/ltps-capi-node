var lib = require("../libs/ltps_potentiometer");

var potent = new lib.Potentiometer();

console.log("Set impedance to 30 kOhm of 50 kOhm"); // Tibbit 40_3
potent.setImpedance("s1", 30000, 50000); // 5000, 10000, 50000 or 100000