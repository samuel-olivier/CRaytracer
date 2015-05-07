#ifndef __CONFIG__
#define __CONFIG__

#include <math.h>

#define EPSILON 0.0001
#define SHADOW_ENABLED 1
#define MAX_RECURSION_DEPTH 2
#define LIGHT_SAMPLE_NUMBER 500

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900

#define INTEGRATOR Pathtracing
#define INTEGRATOR_SAMPLE_NUMBER 1000000
// #define INTEGRATOR_SAMPLE_NUMBER 1

#endif
