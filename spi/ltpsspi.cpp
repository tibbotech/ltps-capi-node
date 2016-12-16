/*!
    \copyright Tibbo Technology Inc
    \author Vitaly Gribko (vitaliy.gribko@tibbo.com)
*/

#include <nan.h>
#include <v8.h>

#include "Cspi.h"

#include "lutils.h"

Cspi m_spi;

class LtpsSpi: public Nan::ObjectWrap
{
public:
    static NAN_MODULE_INIT(Init);

private:
    LtpsSpi() {}
    virtual ~LtpsSpi() {}

    static NAN_METHOD(New);

    static NAN_METHOD(SetDev);
    static NAN_METHOD(SetMode);
    static NAN_METHOD(SetBits);
    static NAN_METHOD(SetSpeed);
    static NAN_METHOD(SetDelay);

    static NAN_METHOD(GetSpiBusNum);

    static NAN_METHOD(GetBus);
    static NAN_METHOD(GetDev);
    static NAN_METHOD(GetMode);
    static NAN_METHOD(GetBits);
    static NAN_METHOD(GetSpeed);
    static NAN_METHOD(GetDelay);

    static NAN_METHOD(WR);

    static Nan::Persistent<v8::Function> constructor;
};

Nan::Persistent<v8::Function> LtpsSpi::constructor;

NAN_MODULE_INIT(LtpsSpi::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New<v8::String>("LtpsSpi").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(tpl, "setDev", SetDev);
    SetPrototypeMethod(tpl, "setMode", SetMode);
    SetPrototypeMethod(tpl, "setBits", SetBits);
    SetPrototypeMethod(tpl, "setSpeed", SetSpeed);
    SetPrototypeMethod(tpl, "setDelay", SetDelay);

    SetPrototypeMethod(tpl, "getSpiBusNum", GetSpiBusNum);

    SetPrototypeMethod(tpl, "getBus", GetBus);
    SetPrototypeMethod(tpl, "getDev", GetDev);
    SetPrototypeMethod(tpl, "getMode", GetMode);
    SetPrototypeMethod(tpl, "getBits", GetBits);
    SetPrototypeMethod(tpl, "getSpeed", GetSpeed);
    SetPrototypeMethod(tpl, "getDelay", GetDelay);

    SetPrototypeMethod(tpl, "WR", WR);

    constructor.Reset(tpl->GetFunction());
    Nan::Set(target, Nan::New("LtpsSpi").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(LtpsSpi::New)
{
    if (!info.IsConstructCall())
        return Nan::ThrowTypeError("Use the new operator to construct the LtpsSpi object");

    LtpsSpi* obj = new LtpsSpi();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(LtpsSpi::SetDev)
{
    if (info.Length() != 2 || !info[0]->IsUint32() || !info[1]->IsUint32())
        return Nan::ThrowError("Arguments must be a pair bus number/device (eg: 1, 0)");

    unsigned int bus = info[0]->Uint32Value();
    unsigned int dev = info[1]->Uint32Value();

    int result = m_spi.set_dev(bus, dev);

    info.GetReturnValue().Set(result);
}

NAN_METHOD(LtpsSpi::SetMode)
{
    if (info.Length() != 1 || !info[0]->IsUint32())
        return Nan::ThrowError("Argument must be a unsigned integer number (0...3)");

    unsigned int mode = info[0]->Uint32Value();

    m_spi.settings_get();
    m_spi.set_mode(mode);
    m_spi.settings_set();
}

NAN_METHOD(LtpsSpi::SetBits)
{
    if (info.Length() != 1 || !info[0]->IsUint32())
        return Nan::ThrowError("Argument must be a unsigned integer number");

    unsigned int bits = info[0]->Uint32Value();

    m_spi.settings_get();
    m_spi.set_bits(bits);
    m_spi.settings_set();
}

NAN_METHOD(LtpsSpi::SetSpeed)
{
    if (info.Length() != 1 || !info[0]->IsUint32())
        return Nan::ThrowError("Argument must be a unsigned integer number");

    unsigned int speed = info[0]->Uint32Value();

    m_spi.settings_get();
    m_spi.set_speed(speed);
    m_spi.settings_set();
}

NAN_METHOD(LtpsSpi::SetDelay)
{
    if (info.Length() != 1 || !info[0]->IsUint32())
        return Nan::ThrowError("Argument must be a unsigned integer number");

    unsigned int delay = info[0]->Uint32Value();

    m_spi.settings_get();
    m_spi.set_delay(delay);
    m_spi.settings_set();
}

NAN_METHOD(LtpsSpi::GetSpiBusNum)
{
    if (info.Length() != 1 || !info[0]->IsString())
        return Nan::ThrowError("Argument must be a SPI socket name (eg: s1, s15)");

    v8::String::Utf8Value socket(info[0]->ToString());

    int value = Lutils::getInstance().getSpiBusNum(*socket);

    info.GetReturnValue().Set(value);
}

NAN_METHOD(LtpsSpi::GetBus)
{
    int bus = m_spi.cur_bus();

    info.GetReturnValue().Set(bus);
}

NAN_METHOD(LtpsSpi::GetDev)
{
    int dev = m_spi.cur_dev();

    info.GetReturnValue().Set(dev);
}

NAN_METHOD(LtpsSpi::GetMode)
{
    int mode = m_spi.cur_mode();

    info.GetReturnValue().Set(mode);
}

NAN_METHOD(LtpsSpi::GetBits)
{
    int bits = m_spi.cur_bits();

    info.GetReturnValue().Set(bits);
}

NAN_METHOD(LtpsSpi::GetSpeed)
{
    int speed = m_spi.cur_speed();

    info.GetReturnValue().Set(speed);
}

NAN_METHOD(LtpsSpi::GetDelay)
{
    int delay = m_spi.cur_delay();

    info.GetReturnValue().Set(delay);
}

NAN_METHOD(LtpsSpi::WR)
{
    if (info.Length() == 2 && (!info[0]->IsObject() || !info[1]->IsUint32()))
        return Nan::ThrowError("Incorrect argument passed to WR(w, bytecount)");

    int byteCount = info[1]->Uint32Value();

    v8::Local<v8::Object> wBufObject = info[0]->ToObject();
    char *wData = node::Buffer::Data(wBufObject);

    v8::Local<v8::Object> rBuffer = Nan::NewBuffer(byteCount).ToLocalChecked();

    m_spi.WR((uint8_t*) wData, (uint8_t*) node::Buffer::Data(rBuffer), byteCount);

    info.GetReturnValue().Set(rBuffer);
}

NODE_MODULE(ltpsspi, LtpsSpi::Init)
