#!/bin/sh

if [ $# -lt 1 ]; then
	echo "Usage $0 path_to_ltps_toolchain_environment"
	exit 1;
fi;

source $1

node-gyp clean configure build --arch=arm

cp ./build/Release/ltps_${PWD##*/}.node ../libs
rm -fR ./build
