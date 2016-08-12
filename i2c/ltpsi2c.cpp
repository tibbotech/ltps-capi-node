/*!
    \copyright Tibbo Technology Inc
    \author Vitaly Gribko (vitaliy.gribko@tibbo.com)
*/

#include <nan.h>

#include <unistd.h>

#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "Ci2c_smbus.h"

class LtpsI2C: public Nan::ObjectWrap
{
public:
    static NAN_MODULE_INIT(Init);

private:
    LtpsI2C() {}
    virtual ~LtpsI2C() {}

    static NAN_METHOD(New);
    static NAN_METHOD(Read);
    static NAN_METHOD(Write);

    static Nan::Persistent<v8::Function> constructor;
};

Nan::Persistent<v8::Function> LtpsI2C::constructor;

NAN_MODULE_INIT(LtpsI2C::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New<v8::String>("LtpsI2C").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(tpl, "read", Read);
    SetPrototypeMethod(tpl, "write", Write);

    constructor.Reset(tpl->GetFunction());
    Nan::Set(target, Nan::New("LtpsI2C").ToLocalChecked(), tpl->GetFunction());
}


NAN_METHOD(LtpsI2C::New)
{
    if (!info.IsConstructCall())
        return Nan::ThrowTypeError("Use the new operator to construct the LtpsI2C object");

    LtpsI2C* obj = new LtpsI2C();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NAN_METHOD(LtpsI2C::Read)
{
    if ((info.Length() != 3 && info.Length() != 4) ||
            (info.Length() != 4 && info.Length() != 3))
        return Nan::ThrowError("Incorrect argument passed to read(bus, address, bytecount) or read(bus, address, register, bytecount)");

    if (info.Length() == 3 && (!info[0]->IsUint32() || !info[1]->IsUint32() || !info[2]->IsUint32()))
        return Nan::ThrowError("Incorrect argument passed to read(bus, address, bytecount)");

    if (info.Length() == 4 && (!info[0]->IsUint32() || !info[1]->IsUint32() || !info[2]->IsUint32() || !info[3]->IsUint32()))
        return Nan::ThrowError("Incorrect argument passed to read(bus, address, register, bytecount)");

    unsigned int busn = info[0]->Uint32Value();

    unsigned int addr = info[1]->Uint32Value();

    if(addr > 0x7F)
        return Nan::ThrowError("Device address must be in 0..127 range");

    int byteCount = info[info.Length() - 1]->Uint32Value();

    if(byteCount == 0)
        return Nan::ThrowError("Bytecount must be more than 0");

    v8::Local<v8::Object> nodeBuffer = Nan::NewBuffer(byteCount).ToLocalChecked();

    for (int i = 0; i < byteCount; i++)
        nodeBuffer->Set(i, Nan::New<v8::Integer>(0));

    if (info.Length() == 3)
    {
        char fileName[PATH_MAX];
        snprintf(fileName, PATH_MAX, "/dev/i2c-%d", busn);

        int file = open(fileName, O_RDONLY);

        if (file < 0)
            return Nan::ThrowError(strerror(errno));

        if (ioctl(file, I2C_SLAVE_FORCE, addr) < 0)
        {
            close(file);
            return Nan::ThrowError(strerror(errno));
        }

        if (read(file, node::Buffer::Data(nodeBuffer), byteCount) != byteCount)
        {
            close(file);
            return Nan::ThrowError(strerror(errno));
        }

        close(file);
        info.GetReturnValue().Set(nodeBuffer);
    }

    if (info.Length() == 4)
    {
        Ci2c_smbus i2c;

        if (i2c.set_bus(busn) != 1)
            return Nan::ThrowError("I2C set bus error");

        unsigned int reg = info[2]->Uint32Value();

        if (i2c.Rbb(addr, reg, (uint8_t*) node::Buffer::Data(nodeBuffer), byteCount) != byteCount)
            return Nan::ThrowError("I2C read error");

        info.GetReturnValue().Set(nodeBuffer);
    }
}

NAN_METHOD(LtpsI2C::Write)
{
    if ((info.Length() != 3 && info.Length() != 4) ||
            (info.Length() != 4 && info.Length() != 3))
        return Nan::ThrowError("Incorrect argument passed to write(bus, address, bytecount) or write(bus, address, register, bytecount)");

    if (info.Length() == 3 && (!info[0]->IsUint32() || !info[1]->IsUint32() || !info[2]->IsObject()))
        return Nan::ThrowError("Incorrect argument passed to write(bus, address, bytecount)");

    if (info.Length() == 4 && (!info[0]->IsUint32() || !info[1]->IsUint32() || !info[2]->IsUint32() || !info[3]->IsObject()))
        return Nan::ThrowError("Incorrect argument passed to write(bus, address, register, bytecount)");

    unsigned int busn = info[0]->Uint32Value();

    unsigned int addr = info[1]->Uint32Value();

    if(addr > 0x7F)
        return Nan::ThrowError("Device address must be in 0..127 range");

    v8::Local<v8::Object> bufObject = info[info.Length() - 1]->ToObject();

    char *data = node::Buffer::Data(bufObject);
    int byteCount = node::Buffer::Length(bufObject);

    if (info.Length() == 3)
    {
        char fileName[PATH_MAX];
        snprintf(fileName, PATH_MAX, "/dev/i2c-%d", busn);

        int file = open(fileName, O_WRONLY);

        if (file < 0)
            return Nan::ThrowError(strerror(errno));

        if (ioctl(file, I2C_SLAVE_FORCE, addr) < 0)
        {
            close(file);
            return Nan::ThrowError(strerror(errno));
        }

        if (byteCount > 0)
        {
            if (write(file, data, byteCount) != byteCount)
            {
                close(file);
                return Nan::ThrowError(strerror(errno));
            }
        }

        close(file);
    }

    if (info.Length() == 4)
    {
        Ci2c_smbus i2c;

        if (i2c.set_bus(busn) != 1)
            return Nan::ThrowError("I2C set bus error");

        unsigned int reg = info[2]->Uint32Value();

        if (i2c.Wbb(addr, reg, (uint8_t*) data, byteCount) != byteCount)
            return Nan::ThrowError("I2C write error");
    }
}

NODE_MODULE(ltpsi2c, LtpsI2C::Init)
