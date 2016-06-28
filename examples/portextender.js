var lib = require("../libs/ltps_portextender.node");

var data = new lib.PortexData();
var pext = new lib.Portextender();

data.direction = false; // false for output, true for input
data.pullup = false; // read/write for input, read for output

for (var i = 1; i < 9; i++)
{
	console.log("Set pin %d to output with value = %d", i, i % 2);
	
	if (i % 2 == 0)
		data.value = false; // read/write for output, read for input
	else
		data.value = true;
		
	pext.setData("s1", i, data);
}