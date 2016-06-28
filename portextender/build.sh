#!/bin/sh

swig -I../../ltps-capi/include/tibbits/i2c -c++ -javascript -node ${PWD##*/}.i
node-gyp clean configure build --arch=arm

cp ./build/Release/ltps_${PWD##*/}.node ../libs
rm -fR ./build ${PWD##*/}_wrap.cxx
