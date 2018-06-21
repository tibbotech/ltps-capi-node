var lib = require("../libs/ltps_adc420.node");

var adc = new lib.Adc420();
var data = new lib.Adc420Data();

adc.getCurrent("s1", data);

if (data.status == 0)
    console.log("Current = %d A", data.current);
else
    console.log(data.error);
