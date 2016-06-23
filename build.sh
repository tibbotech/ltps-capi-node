#!/bin/sh

if [ $# -lt 1 ]; then
	echo "Usage $0 path_to_ltps_toolchain_environment"
	exit 1;
fi;

cd ./humidity
./build.sh $1

cd ../adc
./build.sh $1

cd ../dac
./build.sh $1

cd ../pic
./build.sh $1
