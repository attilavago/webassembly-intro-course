
#include <stdio.h>
#include <emscripten.h>

// Init circle data and start render - JS
int main() {

  printf("Init circles\n");
  emscripten_run_script("render()");
}

// Return circles to JS
int getCircles() {
  return 1;
}
