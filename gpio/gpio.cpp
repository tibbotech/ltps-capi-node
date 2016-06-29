/*!
    \copyright Tibbo Technology Inc
    \author Vitaly Gribko (vitaliy.gribko@tibbo.com)
*/

#include <string>
#include <algorithm>

#include "drivers/cpin.h"
#include "lutils.h"

#include "gpio.h"

#include "nan.h"

#define PINS_INI_FILE       "/opt/tps-shared/hwini/pins.ini"

LtpsGpio::LtpsGpio()
{

}

LtpsGpio::~LtpsGpio()
{

}

void LtpsGpio::setDirection(const char *pin, const char *direction)
{
    std::string spin(pin);
    std::transform(spin.begin(), spin.end(), spin.begin(), ::toupper);

    CPin gpio;
    if (!gpio.init(Lutils::readInteger(PINS_INI_FILE, "CPU", spin.c_str())))
    {
        std::string sdirection(direction);
        std::transform(sdirection.begin(), sdirection.end(), sdirection.begin(), ::tolower);

        if (sdirection.find("in") != std::string::npos)
            gpio.dir_set(PIN_DIR_I);
        else
            gpio.dir_set(PIN_DIR_O);
    }
    else
        Nan::ThrowError("GPIO PIN initialization error");
}

const char* LtpsGpio::getDirection(const char *pin)
{
    std::string spin(pin);
    std::transform(spin.begin(), spin.end(), spin.begin(), ::toupper);

    CPin gpio;
    if (!gpio.init(Lutils::readInteger(PINS_INI_FILE, "CPU", spin.c_str())))
    {
        int dir = gpio.dir_get();
        if (dir == PIN_DIR_I)
            return "input";
        else
            return "output";
    }
    else
        Nan::ThrowError("GPIO PIN initialization error");
}

void LtpsGpio::setValue(const char* pin, unsigned int value)
{
    std::string spin(pin);
    std::transform(spin.begin(), spin.end(), spin.begin(), ::toupper);

    CPin gpio;
    if (!gpio.init(Lutils::readInteger(PINS_INI_FILE, "CPU", spin.c_str())))
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
    std::string spin(pin);
    std::transform(spin.begin(), spin.end(), spin.begin(), ::toupper);

    CPin gpio;
    if (!gpio.init(Lutils::readInteger(PINS_INI_FILE, "CPU", spin.c_str())))
    {
        int value = gpio.R();
        if (value == 0)
            return 0;
        else
            return 1;
    }
    else
        Nan::ThrowError("GPIO PIN initialization error");
}
