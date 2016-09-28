cmake_minimum_required( VERSION 3.0 )

find_package( SWIG 3.0.10 REQUIRED )

find_file( NodeGyp NAMES node-gyp )
if( NodeGyp )
	message( STATUS "Found node-gyp module" )
else()
	message( FATAL_ERROR "node-gyp module not found" )
endif()

if ( EXISTS $ENV{NODE_PATH}/nan/nan.h )
	message( STATUS "Found nan module" )
else()
	message( FATAL_ERROR "nan module not found" )
endif()

add_custom_target ( accelerometer
	COMMAND swig -I../../ltps-capi/include/tibbits/i2c -c++ -javascript -node accelerometer.i
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_accelerometer.node ../libs
	COMMAND rm -fR ./build ./accelerometer_wrap.cxx
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/accelerometer
	COMMENT "Building accelerometer module" VERBATIM
	)

add_custom_target ( adc
	COMMAND swig -I../../ltps-capi/include/tibbits/i2c -c++ -javascript -node adc.i
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_adc.node ../libs
	COMMAND rm -fR ./build ./adc_wrap.cxx
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/adc
	COMMENT "Building adc module" VERBATIM
	)

add_custom_target ( agpio
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_agpio.node ../libs
	COMMAND rm -fR ./build
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/agpio
	COMMENT "Building agpio module" VERBATIM
	)

add_custom_target ( awiegand
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_awiegand.node ../libs
	COMMAND rm -fR ./build
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/awiegand
	COMMENT "Building awiegand module" VERBATIM
	)

add_custom_target ( dac
	COMMAND swig -I../../ltps-capi/include/tibbits/i2c -c++ -javascript -node dac.i
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_dac.node ../libs
	COMMAND rm -fR ./build ./dac_wrap.cxx
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dac
	COMMENT "Building dac module" VERBATIM
	)

add_custom_target ( gpio
	COMMAND swig -I../../ltps-capi/include/drivers -c++ -javascript -node gpio.i
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_gpio.node ../libs
	COMMAND rm -fR ./build ./gpio_wrap.cxx
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/gpio
	COMMENT "Building gpio module" VERBATIM
	)

add_custom_target ( humidity
	COMMAND swig -I../../ltps-capi/include/tibbits/i2c -c++ -javascript -node humidity.i
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_humidity.node ../libs
	COMMAND rm -fR ./build ./humidity_wrap.cxx
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/humidity
	COMMENT "Building humidity module" VERBATIM
	)

add_custom_target ( i2c
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_i2c.node ../libs
	COMMAND rm -fR ./build
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/i2c
	COMMENT "Building i2c module" VERBATIM
	)

add_custom_target ( light
	COMMAND swig -I../../ltps-capi/include/tibbits/i2c -c++ -javascript -node light.i
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_light.node ../libs
	COMMAND rm -fR ./build ./light_wrap.cxx
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/light
	COMMENT "Building light module" VERBATIM
	)

add_custom_target ( pic
	COMMAND swig -I../../ltps-capi/include/tibbits/i2c -c++ -javascript -node pic.i
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_pic.node ../libs
	COMMAND rm -fR ./build ./pic_wrap.cxx
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pic
	COMMENT "Building pic module" VERBATIM
	)

add_custom_target ( portextender
	COMMAND swig -I../../ltps-capi/include/tibbits/i2c -c++ -javascript -node portextender.i
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_portextender.node ../libs
	COMMAND rm -fR ./build ./portextender_wrap.cxx
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/portextender
	COMMENT "Building portextender module" VERBATIM
	)

add_custom_target ( potentiometer
	COMMAND swig -I../../ltps-capi/include/tibbits/i2c -c++ -javascript -node potentiometer.i
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_potentiometer.node ../libs
	COMMAND rm -fR ./build ./potentiometer_wrap.cxx
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/potentiometer
	COMMENT "Building potentiometer module" VERBATIM
	)

add_custom_target ( pressure
	COMMAND swig -I../../ltps-capi/include/tibbits/i2c -c++ -javascript -node pressure.i
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_pressure.node ../libs
	COMMAND rm -fR ./build ./pressure_wrap.cxx
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pressure
	COMMENT "Building pressure module" VERBATIM
	)

add_custom_target ( rtc
	COMMAND swig -I../../ltps-capi/include/tibbits/spi -c++ -javascript -node rtc.i
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_rtc.node ../libs
	COMMAND rm -fR ./build ./rtc_wrap.cxx
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/rtc
	COMMENT "Building rtc module" VERBATIM
	)

add_custom_target ( temperature
	COMMAND swig -I../../ltps-capi/include/tibbits/i2c -c++ -javascript -node temperature.i
	COMMAND node-gyp clean configure build --arch=arm
	COMMAND cp ./build/Release/ltps_temperature.node ../libs
	COMMAND rm -fR ./build ./temperature_wrap.cxx
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/temperature
	COMMENT "Building temperature module" VERBATIM
	)

add_custom_target ( modules ALL DEPENDS 
	accelerometer
	adc
	agpio
	awiegand
	dac
	gpio
	humidity
	i2c
	light
	pic
	portextender
	potentiometer
	pressure
	rtc
	temperature
	)
