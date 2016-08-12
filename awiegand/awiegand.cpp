/*!
    \copyright Tibbo Technology Inc
    \author Vitaly Gribko (vitaliy.gribko@tibbo.com)
*/

#include <nan.h>
#include <v8.h>

#include <unistd.h>

#include <string>
#include <vector>

#include "CWg.h"

class WiegandAsync : public Nan::ObjectWrap
{
public:
    static NAN_MODULE_INIT(Init);

private:
    WiegandAsync() {}
    virtual ~WiegandAsync() {}

    static NAN_METHOD(New);
    static NAN_METHOD(SetPollPeriod);
    static NAN_METHOD(StartLoop);
    static NAN_METHOD(AddWatch);
    static NAN_METHOD(RemoveWatch);

    static Nan::Persistent<v8::Function> constructor;
};

Nan::Persistent<v8::Function> WiegandAsync::constructor;

struct wiegand_event_data
{
    uv_work_t request;
    std::string *event_name;
    std::string data;
    int len;
};

NAN_MODULE_INIT(WiegandAsync::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New<v8::String>("WiegandAsync").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(tpl, "setPollPeriod", SetPollPeriod);
    SetPrototypeMethod(tpl, "startLoop", StartLoop);
    SetPrototypeMethod(tpl, "addWatch", AddWatch);
    SetPrototypeMethod(tpl, "removeWatch", RemoveWatch);

    constructor.Reset(tpl->GetFunction());
    Nan::Set(target, Nan::New("WiegandAsync").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(WiegandAsync::New)
{
    if (!info.IsConstructCall())
        return Nan::ThrowTypeError("Use the new operator to construct the WiegandAsync object");

    WiegandAsync* obj = new WiegandAsync();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

WiegandAsync* wiegandAsyncThreadLoop;

uv_thread_t wiegandThread;

int threadNum = 1;
unsigned int pollPeriod = 100;

std::vector<std::string> wiegandVector;

NAN_INLINE void noop_execute (uv_work_t* req)
{

}

NAN_INLINE void callback_async_event (uv_work_t* req)
{
    Nan::HandleScope scope;
  
    wiegand_event_data* data = static_cast<wiegand_event_data*>(req->data);
    v8::Local<v8::Value> emit_argv[] = { Nan::New("dataReceivedEvent").ToLocalChecked(), Nan::New<v8::String>(data->data).ToLocalChecked(), Nan::New<v8::Integer>(int(data->len)) };

    Nan::MakeCallback(wiegandAsyncThreadLoop->handle(), "emit", 3, emit_argv);

    delete data;
}

void emit_event()
{
    for (std::vector<std::string>::iterator it = wiegandVector.begin(); it != wiegandVector.end(); ++it)
    {
        CWg twg;

        wg_data_t result;
        memset(&result, 0, sizeof(wg_data_t));

        if (twg.init((*it).c_str()) < 0)
        {
            printf("Could not initialise the socket %s\n", (*it).c_str());
            continue;
        }

        if (twg.R(result) > 0)
        {
            char buff[TWG_MAX_BUF];

            for (int i = 0; i < result.blen / 8; i++)
                sprintf(buff + i * 2, "%02X", result.buff[i]);

            if (result.blen % 8 != 0)
                sprintf(buff + strlen(buff), "%02X", result.buff[result.blen / 8]);

            std::string key(buff);
            key = key.substr(0, result.blen / 4);

            wiegand_event_data *wiegandEventdata = new wiegand_event_data();
            wiegandEventdata->request.data = (void *) wiegandEventdata;

            wiegandEventdata->data = key;
            wiegandEventdata->len = result.blen;

            uv_queue_work(uv_default_loop(), &wiegandEventdata->request, noop_execute, reinterpret_cast<uv_after_work_cb>(callback_async_event));
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

NAN_METHOD(WiegandAsync::SetPollPeriod)
{
    if(info.Length() != 1 || !info[0]->IsUint32())
        return Nan::ThrowError("Argument must be a positive unsigned integer value");

    unsigned int period = info[0]->Uint32Value();

    if (period == 0)
        return Nan::ThrowError("Argument must be a positive unsigned integer value");

    if (period > 900000)
        return Nan::ThrowError("Period must be less than 900000");

    pollPeriod = period;
}

NAN_METHOD(WiegandAsync::StartLoop)
{
    if(wiegandAsyncThreadLoop)
        return Nan::ThrowError("Can't call twice");

    wiegandAsyncThreadLoop = Nan::ObjectWrap::Unwrap<WiegandAsync>(info.Holder());
    uv_thread_create(&wiegandThread, threadLoop, &threadNum);
}

NAN_METHOD(WiegandAsync::AddWatch)
{
    if(info.Length() != 1 || !info[0]->IsString())
        return Nan::ThrowError("Argument must be a socket name");

    v8::String::Utf8Value param(info[0]->ToString());

    std::string socket = *param;

    wiegandVector.push_back(*param);
}

NAN_METHOD(WiegandAsync::RemoveWatch)
{
    if(info.Length() != 1 || !info[0]->IsString())
        return Nan::ThrowError("Argument must be a socket name");

    v8::String::Utf8Value param(info[0]->ToString());

    std::vector<std::string>::iterator it = std::find(wiegandVector.begin(), wiegandVector.end(), *param);
    if (it != wiegandVector.end())
        wiegandVector.erase(it);
}

NODE_MODULE(awiegand, WiegandAsync::Init)
