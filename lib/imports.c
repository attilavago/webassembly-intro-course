#include <emscripten.h>
#include <stdio.h>

// declare reusable .js function
EM_JS(void, jsFunction, (int n), {
    console.log("Call from EM_JS: " + n);
});

int main(){
    printf("WASM Ready! Testing imports\n");

    // running JS within C is an anti-pattern!!!
    // call .js function via (eval)
    emscripten_run_script("console.log('Hello from C!')");

    // call .js function async via (eval)
    emscripten_async_run_script("console.log('Hello from C - async!')", 2000);

    // Get return value from js function instead!!! - integer
    int jsValue = emscripten_run_script_int("getNum()");
    printf("Value from getNum(): %d\n", jsValue);

    // Get return value from js function instead!!! - string
    char * jsValueStr = emscripten_run_script_string("getStr()");
    printf("Value from getStr(): %s\n", jsValueStr);

    // Execute EM_JS function
    jsFunction(144);

    return 1;
}
