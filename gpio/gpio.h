/*!
    \copyright Tibbo Technology Inc
    \author Vitaly Gribko (vitaliy.gribko@tibbo.com)
*/

class LtpsGpio
{
public:

    LtpsGpio();

    virtual ~LtpsGpio();

    void setDirection(const char *pin, const char *direction);

    const char* getDirection(const char *pin);

    void setValue(const char* pin, unsigned int value);

    unsigned int getValue(const char *pin);
};
