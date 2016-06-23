#!/bin/sh

if [ $# -lt 1 ]; then
	echo "Usage $0 path_to_ltps_toolchain_environment"
	exit 1;
fi;

source $1

swig -I../../ltps-capi/include/tibbits/i2c -c++ -javascript -node ${PWD##*/}.i
node-gyp clean configure build --arch=arm

cp ./build/Release/ltps_${PWD##*/}.node ../libs
rm -fR ./build ${PWD##*/}_wrap.cxx
