{
	"targets": [
    {
		"target_name": "ltps_i2c",

		"sources": [ "./ltpsi2c.cpp",
			"../../ltps-capi/src/drivers/ci2c.cpp",
			"../../ltps-capi/src/drivers/ci2c_smbus.cpp" ],

	  	"include_dirs": [ "<!(node -e \"require('nan')\")",
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