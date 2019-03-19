
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <emscripten.h>

// number of circles to create and animate
#define NUM_CIRCLES 200

struct Circle {
    int x;  // y coord
    int y;  // x coord
    int r;  // radius
    int cr; // color red
    int cg; // color green
    int cb; // color blue
};

// circle animation data struct
struct CircleAnimationData {
    int x;  // y coord
    int y;  // x coord
    int r;  // radius
    int xv; // x axis velocity
    int yv; // y axis velocity
    int xd; // x axis direction (1 = fwd, 0 = bkwd)
    int yd; // y axis direction (1 = fwd, 0 = bkwd)
};

struct Circle circles[NUM_CIRCLES];
struct CircleAnimationData animationData[NUM_CIRCLES];

int getRand(max){
    return (rand() % max);
}

// Init circle data and start render - JS
int main() {
    srand(time(NULL));

    for(int i = 0; i < NUM_CIRCLES; i++){
        int radius = getRand(50);
        int x = getRand(1000) + radius;
        int y = getRand(1000) + radius;

        animationData[i].x = x;
        animationData[i].y = y;
        animationData[i].r = radius;
        animationData[i].xv = getRand(10);
        animationData[i].yv = getRand(10);
        animationData[i].xd = 1;
        animationData[i].yd = 1;

        circles[i].x = x;
        circles[i].y = y;
        circles[i].r = radius;
        circles[i].cr = getRand(255);
        circles[i].cg = getRand(255);
        circles[i].cb = getRand(255);
    }

    // start js rendering
    EM_ASM({render($0, $1);}, NUM_CIRCLES * 6, 6);
};

// Return circles to JS
struct Circle * getCircles(int canvasWidth, int canvasHeight) {
    for(int i = 0; i < NUM_CIRCLES; i++){
        if((animationData[i].x + animationData[i].r) >= canvasWidth) animationData[i].xd = 0;
        if((animationData[i].x - animationData[i].r) <= 0) animationData[i].xd = 1;
        if((animationData[i].y - animationData[i].r) <= 0) animationData[i].yd = 1;
        if((animationData[i].y + animationData[i].r) >= canvasHeight) animationData[i].yd = 0;

        if(animationData[i].xd == 1){
            animationData[i].x += animationData[i].xv;
        } else {
            animationData[i].x -= animationData[i].xv;
        }

        if(animationData[i].yd == 1){
            animationData[i].y += animationData[i].yv;
        } else {
            animationData[i].y -= animationData[i].yv;
        }

        circles[i].x = animationData[i].x;
        circles[i].y = animationData[i].y;
    }

    return circles;
};
