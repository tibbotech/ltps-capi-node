#include <stdio.h>
#include <unistd.h>

#include <map>

#include <nan.h>

#include "drivers/cpin.h"
#include "lutils.h"

#define PINS_INI_FILE       "/opt/tps-shared/hwini/pins.ini"

using namespace Nan;

class GpioAsync : public ObjectWrap
{
public:
    static NAN_MODULE_INIT(Init);

private:
    GpioAsync();
    ~GpioAsync();

    static NAN_METHOD(New);
    static NAN_METHOD(SetPollPeriod);
    static NAN_METHOD(StartLoop);
    static NAN_METHOD(AddWatch);
    static NAN_METHOD(RemoveWatch);
    static Persistent<v8::Function> constructor;
};

struct gpio_event_data
{
    uv_work_t request;
    std::string *event_name;
    std::string pin;
    int value;
};

Persistent<v8::Function> GpioAsync::constructor;

GpioAsync::GpioAsync()
{

}

GpioAsync::~GpioAsync()
{

}

NAN_MODULE_INIT(GpioAsync::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New<v8::String>("GpioAsync").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(tpl, "setPollPeriod", SetPollPeriod);
    SetPrototypeMethod(tpl, "startLoop", StartLoop);
    SetPrototypeMethod(tpl, "addWatch", AddWatch);
    SetPrototypeMethod(tpl, "removeWatch", RemoveWatch);

    constructor.Reset(tpl->GetFunction());
    Set(target, Nan::New("GpioAsync").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(GpioAsync::New)
{
    if (info.IsConstructCall())
    {
        GpioAsync* obj = new GpioAsync();
        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    }
    else
    {
        v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
        info.GetReturnValue().Set(cons->NewInstance());
    }
}

GpioAsync* gpioAsyncThreadLoop;
uv_thread_t gpioThread;
int threadNum = 1;
unsigned int pollPeriod = 25;

std::map<std::string, int> gpioMap;

NAN_INLINE void noop_execute (uv_work_t* req)
{

}

NAN_INLINE void callback_async_event (uv_work_t* req)
{
    Nan::HandleScope scope;
  
    gpio_event_data* data = static_cast<gpio_event_data*>(req->data);
    v8::Local<v8::Value> emit_argv[] = { Nan::New("valueChangeEvent").ToLocalChecked(), Nan::New<v8::String>(data->pin).ToLocalChecked(), Nan::New<v8::Integer>(int(data->value)) };

    MakeCallback(gpioAsyncThreadLoop->handle(), "emit", 3, emit_argv);

    delete data;
}

void emit_event()
{
    for (std::map<std::string, int>::iterator it = gpioMap.begin(); it != gpioMap.end(); it++)
    {
        CPin pin;
        if (!pin.init(Lutils::readInteger(PINS_INI_FILE, "CPU", it->first.c_str())))
        {
            int value = pin.R();

            if (gpioMap.at(it->first) != value)
            {
                gpioMap[it->first] = value;

                gpio_event_data *gpioEventdata = new gpio_event_data();
                gpioEventdata->request.data = (void *) gpioEventdata;

                gpioEventdata->pin = it->first;
                gpioEventdata->value = value;

                uv_queue_work(uv_default_loop(), &gpioEventdata->request, noop_execute, reinterpret_cast<uv_after_work_cb>(callback_async_event));
            }
        }
    }
}

void threadLoop(void *)
{
    while(true)
    {
        usleep(pollPeriod * 1000);
        emit_event();
    }
}

NAN_METHOD(GpioAsync::SetPollPeriod)
{
    if(info.Length() != 1 || !info[0]->IsUint32())
        return Nan::ThrowError("Argument must be a unsigned integer value");

    unsigned int period = info[0]->ToUint32()->Value();

    if (period > 900000)
        return Nan::ThrowError("Period must be less than 900000");

    pollPeriod = period;
}

NAN_METHOD(GpioAsync::StartLoop)
{
    if(gpioAsyncThreadLoop)
        return ThrowError("Can't call twice");

    gpioAsyncThreadLoop = Nan::ObjectWrap::Unwrap<GpioAsync>(info.Holder());
    uv_thread_create(&gpioThread, threadLoop, &threadNum);
}

NAN_METHOD(GpioAsync::AddWatch)
{
    if(info.Length() != 1 || !info[0]->IsString())
        return Nan::ThrowError("Argument must be a GPIO pin name");

    v8::String::Utf8Value param(info[0]->ToString());

    CPin pin;
    if (!pin.init(Lutils::readInteger(PINS_INI_FILE, "CPU", std::string(*param).c_str())))
        gpioMap[std::string(*param)] = pin.R();
    else
    {
        std::string error = "Can't add watcher for pin " + std::string(*param);
        return Nan::ThrowError(error.c_str());
    }
}

NAN_METHOD(GpioAsync::RemoveWatch)
{
    if(info.Length() != 1 || !info[0]->IsString())
        return Nan::ThrowError("Argument must be a GPIO pin name");

    v8::String::Utf8Value param(info[0]->ToString());

    std::map<std::string, int>::iterator it = gpioMap.find(std::string(*param));

    if (it != gpioMap.end())
        gpioMap.erase(it);
}

NODE_MODULE(makecallback, GpioAsync::Init)
