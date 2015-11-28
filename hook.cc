
#include "./hook.h" // beacuse Im a good c++ citizen

using namespace v8; // why the fuck not!

// How to convert a v8 string into a char*
// super simple :| ;
static char *TO_CHAR(Handle<Value> val) {
    String::Utf8Value utf8(val->ToString());
    int len = utf8.length() + 1;
    char *str = (char *) calloc(sizeof(char), len);
    strncpy(str, *utf8, len);
    return str;
}


// REFERNCE ONLY
// Cool way to create an isolate if one does not exist -
// Objects cant be used between isolates,
// so this wont work for us because we need to re use the function we pass in from js land
static Isolate* getIsolate(){
    Isolate* isolate = Isolate::GetCurrent();

    if (!isolate) {
        isolate = Isolate::New();
        isolate->Enter();
    }
    return isolate;
}



lwan_http_status_t Webserver::helloWorld(lwan_request_t *request, lwan_response_t *response, void *data){

    printf("ACTUALLY TRYING TO SERVE A PAGE FROM HOOK.CC CODE\n");
    // // REFERNCE ONLY - how to create an isolate and enter it :| and then use it to create stuff in the vm
    // Isolate* isolate = getIsolate();
    // Locker locker(isolate);
    // HandleScope handleScope(isolate);

    //Handle<String> testString = String::NewFromUtf8(isolate, "I Was Created in c++");
    //char* testStringToChar = TO_CHAR(testString);

    Handle<Value> argv[0] = {}; // Because our function does not need args (AT THIS POINT)
    Handle<Function> _cb = *cb;

    //Handle<ObjectTemplate> global = bjectTemplate::New(isolate);
  TryCatch try_catch;
    Handle<Value> result = _cb->Call(_cb->CreationContext()->Global(), 0, argv);



    //_cb->Call(isolate->GetCurrentContext()->Global(), 0, argv); // WHAT WE NEED TO FIX!

    // we should then get the result of the ^ function and then pass it to the thing below:

    // // write the response out!!!!
    //strbuf_set_static(response->buffer, testStringToChar, sizeof(testStringToChar) - 1);

    response->mime_type = "text/plain"; //Because fuck it why not! atleast this line has not given me trouble

    // Maybe we should free some things ... hmmm

    return HTTP_OK; // ITS NOT OK NOTHING IS FUCKING OK, OK!!!!

};

static lwan_http_status_t testHttpResponse(lwan_request_t *request,
            lwan_response_t *response, void *data) {
         return HTTP_OK;
};


static lwan_url_map_t createUrlMap(char* prefix, lwan_http_status_t (*handler)(lwan_request_t *request, lwan_response_t *response, void *data)){

    lwan_url_map_t *url;
    url->prefix = prefix;
    url->handler = handler;

    return *url;
};

// WE GOTTA BUID THIS IS GLOBAL SCOPE< FUKING C - C++ BULLSHIT
//lwan_url_map_t url = createUrlMap("/test", testHttpResponse);
lwan_url_map_t url = createUrlMap("/", statHelloWorld);
static const lwan_url_map_t default_map[] = { url };



void Webserver::startServer(const FunctionCallbackInfo<Value>& args) {  // This is what gets run when we run addon.startServer(xtr); in hook.js!!!
    Isolate* isolate = Isolate::GetCurrent(); // Lets get the isolate that is currently being used in js land

    Handle<Function> _cb = Local<Function>::Cast(args[0]); //args[0] is the xtr object that was passed in to addon.startServer(xtr);

    // lets run the function here to see if it works!
    Handle<Value> argv[0] = {};    //Functions need arguments, in our case we have none, so we create an empty one
    _cb->Call(isolate->GetCurrentContext()->Global(), 0, argv); //how to run a function from js in c++!!!1

    //Hopefully it did!

    //Lets tell the vm not to garbage collect the function!
    Persistent<Function> p_cb;
    p_cb.Reset(isolate, _cb);

    currentWebserverInstance->cb = &_cb;  //fucking bullshit static programming environments
    currentWebserverInstance->isolate = isolate; //oh we kind of need to keep track of this aswell.

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    // LWAN CONFIG - no were near as fucking bullshit as v8 or node
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    char LISTENHOST[20] = "localhost:3000"; // yeah buddy

    lwan_config_t lwan_config = { //even more yeah buddy
        .listener = LISTENHOST,
        .keep_alive_timeout = 15,
        .quiet = false,
        .reuse_port = false,
        .expires = 1 * ONE_WEEK,
        .n_threads = 0
    };


    lwan_t l;

    lwan_init_with_config(&l, &lwan_config);
    lwan_set_url_map(&l, default_map);
    lwan_main_loop(&l);
    lwan_shutdown(&l);
};


// Ok so we cant use c++ member funcs so we gotta proxy through a static func
static lwan_http_status_t statHelloWorld(lwan_request_t *request,
            lwan_response_t *response, void *data) {
         return currentWebserverInstance->helloWorld(request, response, data); //oh yeah served hot from the global scope
};

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// CRAPPY NODE v8 requirments!!
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "startServer", currentWebserverInstance->startServer);
}

NODE_MODULE(addon, init)




