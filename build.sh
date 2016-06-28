#!/bin/sh

cd ./adc
./build.sh

cd ../dac
./build.sh

cd ../pic
./build.sh

cd ../light
./build.sh

cd ../temperature
./build.sh

cd ../humidity
./build.sh

cd ../pressure
./build.sh

cd ../accelerometer
./build.sh

cd ../potentiometer
./build.sh

cd ../portextender
./build.sh

cd ../agpio
./build.sh

cd ../i2c
./build.sh
