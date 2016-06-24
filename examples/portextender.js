var lib = require("../libs/ltps_portextender");

var data = new lib.PortexData();
var pext = new lib.Portextender();

data.direction = false;
data.pullup = false; // It does not matter for output mode

for (var i = 1; i < 9; i++)
{
	console.log("Set pin %d to output with value = %d", i, i % 2);
	
	if (i % 2 == 0)
		data.value = false;
	else
		data.value = true;
		
	pext.setData("s1", i, data);
}