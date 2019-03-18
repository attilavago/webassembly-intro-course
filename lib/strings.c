#include <emscripten.h>
#include <stdio.h>

char * str = "my luffly string variable";

char * getStr(){
    return str;
}

int main(){
    printf("WASM Ready! Testing strings\n");

    return 1;
}
