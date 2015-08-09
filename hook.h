#include <node.h>
#include <string>
#include <cstdlib>
#include <v8.h>
#include <thread>

#include "./lwan/common/lwan.h"
#include "./lwan/common/lwan-config.h"

using namespace v8;

static char *TO_CHAR(Handle<Value> val);
static Isolate* getIsolate();
static lwan_http_status_t statHelloWorld(lwan_request_t *request, lwan_response_t *response, void *data);

class Webserver {
   Handle<Function>* cb;
   Isolate* isolate;
   public:
        static void startServer(const FunctionCallbackInfo<Value>& args);
        lwan_http_status_t helloWorld(lwan_request_t *request,lwan_response_t *response, void *data);
        Webserver();
};

Webserver::Webserver() {};

Webserver x = Webserver();
Webserver* currentWebserverInstance = &x;

void init(Handle<Object> exports);

