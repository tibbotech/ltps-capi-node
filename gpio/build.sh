#!/bin/sh

swig -c++ -javascript -node ${PWD##*/}.i
node-gyp clean configure build --arch=arm

cp ./build/Release/ltps_${PWD##*/}.node ../libs
rm -fR ./build ${PWD##*/}_wrap.cxx
