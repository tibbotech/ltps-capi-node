{
	"targets": [
    {
		"target_name": "ltps_potentiometer",

		"sources": [ "potentiometer_wrap.cxx", 
			"../../ltps-capi/src/tibbits/i2c/potentiometer.cpp",
			"../../ltps-capi/src/lutils.cpp",
			"../../ltps-capi/src/drivers/cpin.cpp",
			"../../ltps-capi/src/drivers/Ci2c.cpp",
			"../../ltps-capi/src/drivers/Ci2c_smbus.cpp",
			"../../ltps-capi/src/drivers/Cspi.cpp" ],

	  	"include_dirs": [ "../../ltps-capi/include",
				"../../ltps-capi/include/drivers",
	  			"../../ltps-capi/include/tibbits/i2c",
				"../../ltps-capi/include/tibbits/spi" ],

		"cflags": [
        	"-fdata-sections",
			"-ffunction-sections",
			"-feliminate-unused-debug-types",
			"-fno-var-tracking-assignments" ],

      	"cflags!": [ "-fno-exceptions" ],

      	"cflags_cc!": [ "-fno-exceptions" ],

        "ldflags": [
            "-Wl,--strip-all",
			"-Wl,--hash-style=gnu",
			"-Wl,--as-needed",
			"-Wl,--gc-sections" ]
    }
	]  
}
