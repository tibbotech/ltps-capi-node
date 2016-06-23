{
	"targets": [
    {
		"target_name": "ltps_pic",

		"sources": [ "pic_wrap.cxx", 
			"../../ltps-capi/src/tibbits/i2c/pic.cpp",
			"../../ltps-capi/src/lutils.cpp",
			"../../ltps-capi/src/drivers/cpin.cpp",
			"../../ltps-capi/src/drivers/ci2c.cpp",
			"../../ltps-capi/src/drivers/ci2c_smbus.cpp" ],

	  	"include_dirs": [ "../../ltps-capi/include",
	  			"../../ltps-capi/include/tibbits/i2c" ],

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
