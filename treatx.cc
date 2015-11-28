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


void runner(){
    printf("IM IN ANOTHER THREAD!!! \n");
};

// void myThread(){
//     printf("XXXXXXXXXXXXX \n");
//     Handle<Value> argv[0] = {}; // Because our function does not need args (AT THIS POINT)
//     Handle<Function> _cb = *cb;
//     _cb->Call(_isolate->GetCurrentContext()->Global(), 0, argv);
// }

struct CallbackPackage {
    Isolate* isolate;
    Persistent<Function>* cb;
};

void call_work(uv_work_t* req) {
    printf("\n%s Thread id : gettid() == %d\n",__FUNCTION__,getpid());
    printf("I HAVE AWAKEND\n");
};

void call_work_after(uv_work_t* req) {
    // Isolate *isolate = Isolate::GetCurrent();
    // HandleScope scope(isolate);
    // Persistent<Function> callback;
    // callback.Reset(isolate, args[0].As<Function>())
    // const unsigned argc = 2;
    // Local<Value> argv[argc] = { Null(isolate), String::NewFromUtf8(isolate, "success") };
    // Local<Function>::New(isolate, work->callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);
    // callback.Reset();

    //Handle<Function> _cb = *baton->cb;
    //Handle<Value> result = _cb->Call(context->Global(), 0, argv);
    // printf("XXXX\n");
    CallbackPackage* baton = static_cast<CallbackPackage*>(req->data);
    Handle<Function> _cb = *baton->cb;

    const unsigned argc = 0;
    Handle<Value> argv[0] = {};


    Local<Function>::New(isolate, callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    // printf("%i\n", baton->cb );
    // Handle<Value> argv[0] = {};

    // Isolate* isolate = Isolate::GetCurrent();
    // HandleScope scope(isolate);
    // printf("XXXX");

    // TryCatch try_catch
    // printf("XXX111\n");

    // Local<Object> context  = isolate->GetCurrentContext()->Global();
    // printf("XXX222%i\n", argv);
    // _cb->Call(context, 0, argv);

};


void startServer(const FunctionCallbackInfo<Value>& args) {
    printf("\n%s Thread id : gettid() == %d\n",__FUNCTION__,getpid());

    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    Persistent<Function> callback;
    callback.Reset(isolate, args[0].As<Function>());

    const unsigned argc = 0;
    Handle<Value> argv[0] = {};
    Local<Function>::New(isolate, callback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);

    //callback.Reset();



    //std::thread t1(runner);
    //t1.detach();
    CallbackPackage baton;
    baton.cb = &callback;

    uv_work_t *req = new uv_work_t();
    req->data = &baton;

    uv_queue_work(uv_default_loop(), req, call_work,
                               (uv_after_work_cb)call_work_after);

    return;
};

void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "startServer", startServer);
}

NODE_MODULE(addon, init)




