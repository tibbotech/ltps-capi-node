# Makefile for Java JNI Library

CPP			= $(shell echo $(CXX))
CPPFLAGS	= $(shell echo $(CXXFLAGS)) -fdata-sections -ffunction-sections -feliminate-unused-debug-types -fno-var-tracking-assignments
DLFLAGS		= $(shell echo $(LDFLAGS)) -Wl,--strip-all -Wl,--hash-style=gnu -Wl,--as-needed -Wl,--gc-sections
JAVAINC		= $(shell echo $(SDKTARGETSYSROOT))

VPATH       = $(JAVAINC)/opt/jdk1.7.0_60/include:$(JAVAINC)/opt/jdk1.7.0_60/include/linux:../../ltps-capi/include:../../ltps-capi/include/drivers
override 	CPPFLAGS += $(patsubst %,-I%,$(subst :, ,$(VPATH)))

OBJECTS		= Ci2c_smbus.o cpin.o lutils.o gpio.o gpio_wrap.o

BINNAME		= libgpio

all: $(BINNAME)

$(BINNAME): $(OBJECTS) 
	$(CPP) -shared $(DLFLAGS) $(OBJECTS) -o $(BINNAME).so

Ci2c_smbus.o:
	$(CPP) $(CPPFLAGS) -c -fpic ../../ltps-capi/src/drivers/Ci2c_smbus.cpp

cpin.o:
	$(CPP) $(CPPFLAGS) -c -fpic ../../ltps-capi/src/drivers/cpin.cpp

lutils.o:
	$(CPP) $(CPPFLAGS) -c -fpic ../../ltps-capi/src/lutils.cpp

gpio.o:
	$(CPP) $(CPPFLAGS) -c -fpic ../../ltps-capi/src/drivers/gpio.cpp

gpio_wrap.o:
	swig -I../../ltps-capi/include/drivers -c++ -java -package com.tibbo.linkserver.plugin.context.iec611313.common.function.gpio gpio.i
	$(CPP) $(CPPFLAGS) -c -fpic gpio_wrap.cxx

.PHONY : clean install

clean:
	$(RM) *.o core $(BINNAME).so *.cxx *.java *.tar.gz

install: all
	tar -zcvf $(BINNAME).tar.gz *.java $(BINNAME).so
