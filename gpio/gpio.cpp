/*!
    \copyright Tibbo Technology Inc
    \author Vitaly Gribko (vitaliy.gribko@tibbo.com)
*/

#include <string.h>

#include <algorithm>

#include "nan.h"

#include "drivers/cpin.h"
#include "lutils.h"

#include "gpio.h"

CPin gpio;

LtpsGpio::LtpsGpio()
{

}

LtpsGpio::~LtpsGpio()
{

}

void LtpsGpio::setDirection(const char *pin, const char *direction)
{
    if (!gpio.init(Lutils::getInstance().readInteger("CPU", pin)))
    {
        if (strcmp(direction, "input") == 0)
            gpio.dir_set(PIN_DIR_I);
        else
            gpio.dir_set(PIN_DIR_O);
    }
    else
        Nan::ThrowError("GPIO PIN initialization error");
}

const char* LtpsGpio::getDirection(const char *pin)
{
    if (!gpio.init(Lutils::getInstance().readInteger("CPU", pin)))
    {
        if (gpio.dir_get() == PIN_DIR_I)
            return "input";
        else
            return "output";
    }
    else
        Nan::ThrowError("GPIO PIN initialization error");

    return "input";
}

void LtpsGpio::setValue(const char* pin, unsigned int value)
{
    if (!gpio.init(Lutils::getInstance().readInteger("CPU", pin)))
    {
        if (value == 0)
            gpio.W(0);
        else
            gpio.W(1);
    }
    else
        Nan::ThrowError("GPIO PIN initialization error");
}

unsigned int LtpsGpio::getValue(const char *pin)
{
    if (!gpio.init(Lutils::getInstance().readInteger("CPU", pin)))
    {
        if (gpio.R() == 0)
            return 0;
        else
            return 1;
    }
    else
        Nan::ThrowError("GPIO PIN initialization error");

    return 0;
}
