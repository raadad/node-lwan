// hello.cc
#include <node.h>
#include <v8.h>
#include <cstdlib>

#include "./lwan/common/lwan.h"
#include "./lwan/common/lwan-config.h"


using namespace v8;

static inline char *TO_CHAR(Handle<Value> val) {
    String::Utf8Value utf8(val->ToString());

    int len = utf8.length() + 1;
    char *str = (char *) calloc(sizeof(char), len);
    strncpy(str, *utf8, len);

    return str;
}

Isolate* isolate = Isolate::GetCurrent();
HandleScope scope(isolate);

Persistent<Function> xcb;


lwan_http_status_t execute (lwan_request_t *request __attribute__((unused)),
      lwan_response_t *response,
      void *data __attribute__((unused)))
{
    printf("%s\n","SS1");
    Local<Value> c = { String::NewFromUtf8(isolate, "hello dawg"); }
    printf("%s\n","SS2");


    // Persistent<Value> argx = xcb->Call(isolate->GetCurrentContext()->Global(), 1, {} );
    // printf("%s\n","SS3");

    // //char* from = argx->ToString();


    char *x = TO_CHAR(c);
    printf("%s", x);
    
    strbuf_set_static(response->buffer, x, sizeof(x) - 1);
    //free(x);

    response->mime_type = "text/plain";
    return HTTP_OK;

};


// 1.run lwan
// 2.mutate response lwan
// 3.push v8 object as resposne lwan
// 4.execute v8 function in c
// 5.execute v8 function from node in c


// 6.attach node function to event lwan event handler and execute on request
// 7.return response from node function that is attached to event handler on request




void Method(const FunctionCallbackInfo<Value>& args) {

      // Persistent<Value, NonCopyablePersistentTraits<Value>> persistent(isolate, args[0]);
      // Persistent<Value> handle = Persistent<Value>();
      // handle.Reset(v8::Isolate::GetCurrent(), args[0]);
      // xcb = Persistent<Function>::Cast(persistent);


      //Persistent<Value> argv[argc] = { String::NewFromUtf8(isolate, "hello world") };
      //cb->Call(isolate->GetCurrentContext()->Global(), argc, argv);




    lwan_url_map_t url;
    url.prefix = "/";
    url.handler = execute;

    static const lwan_url_map_t url_map[] = { url };

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
    lwan_set_url_map(&l, url_map);
    lwan_main_loop(&l);

}

void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "startServer", Method);
}

NODE_MODULE(addon, init)
