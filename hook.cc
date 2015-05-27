// hello.cc
#include <node.h>
#include <v8.h>

#include "./lwan/common/lwan.h"
#include "./lwan/common/lwan-config.h"


using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  lwan_t l;
  lwan_config_t lwan_config = {
        .listener = "localhost:3000",
        .keep_alive_timeout = 15,
        .quiet = false,
        .reuse_port = false,
        .expires = 1 * ONE_WEEK,
        .n_threads = 0
    };

  lwan_init_with_config(&l, &lwan_config);
  lwan_main_loop(&l);

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "startServer", Method);
}

NODE_MODULE(addon, init)
