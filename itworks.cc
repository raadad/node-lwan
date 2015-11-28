#include <node.h>
#include <string>
#include <cstdlib>
#include <v8.h>
#include <thread>
#include <chrono>
#include <uv.h>
#include <sys/types.h>
#include <unistd.h>



using namespace v8;

struct Work {
  uv_work_t  request;
  Persistent<Function> callback;

};



static void call_async(uv_work_t *req) {
    printf("\n%s Thread id : gettid() == %d\n",__FUNCTION__,getpid());

    Work *work = static_cast<Work *>(req->data);
    usleep(4000 * 100);

};

static void call_async_complete(uv_work_t *req,int status) {
    printf("\n%s Thread id : gettid() == %d\n",__FUNCTION__,getpid());

    Isolate * isolate = Isolate::GetCurrent();

    v8::HandleScope handleScope(isolate);

    Work *work = static_cast<Work *>(req->data);

    Handle<Value> argv[] = { };
    Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), 0, argv);
    delete work;


};


void call(const FunctionCallbackInfo<Value>& args) {
    printf("\n%s Thread id : gettid() == %d\n",__FUNCTION__,getpid());

    Isolate* isolate = args.GetIsolate();

    Work * work = new Work();
    work->request.data = work;

    Local<Function> callback = Local<Function>::Cast(args[0]);
    work->callback.Reset(isolate, callback);

    uv_queue_work(uv_default_loop(),&work->request,call_async,call_async_complete);

    args.GetReturnValue().Set(Undefined(isolate));

    return;
};

void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "startServer", call);
}

NODE_MODULE(addon, init)




