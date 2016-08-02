{
	"targets": [
    {
		"target_name": "ltps_agpio",

		"sources": [ "agpio.cpp",
			"../../ltps-capi/src/lutils.cpp",
			"../../ltps-capi/src/drivers/cpin.cpp",
			"../../ltps-capi/src/drivers/Ci2c.cpp",
			"../../ltps-capi/src/drivers/Ci2c_smbus.cpp" ],

	  	"include_dirs": [ "<!(node -e \"require('nan')\")",
				"../../ltps-capi/include/drivers",
				"../../ltps-capi/include" ],

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
