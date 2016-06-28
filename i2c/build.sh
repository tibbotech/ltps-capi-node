#!/bin/sh

node-gyp clean configure build --arch=arm

cp ./build/Release/ltps_${PWD##*/}.node ../libs
rm -fR ./build
