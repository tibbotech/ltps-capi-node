#!/bin/sh

if [ $# -lt 1 ]; then
	echo "Usage $0 path_to_ltps_toolchain_environment"
	exit 1;
fi;

cd ./adc
./build.sh $1

cd ../dac
./build.sh $1

cd ../pic
./build.sh $1

cd ../light
./build.sh $1

cd ../temperature
./build.sh $1

cd ../humidity
./build.sh $1

cd ../pressure
./build.sh $1

cd ../accelerometer
./build.sh $1

cd ../potentiometer
./build.sh $1

cd ../portextender
./build.sh $1
