{
	"targets": [
    {
		"target_name": "ltps_awiegand",

		"sources": [ "awiegand.cpp",
			"../../ltps-capi/src/drivers/CWg.cpp" ],

	  	"include_dirs": [ "<!(node -e \"require('nan')\")",
				"../../ltps-capi/include/drivers" ],

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
