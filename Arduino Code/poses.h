#ifndef POSES
#define POSES

#include <avr/pgmspace.h>

#define ROT_PERIOD 10000 //milliseconds per full rotation and return
#define TILT_PERIOD 800   //milliseconds per full upward tilt and return
#define INCREMENT 10 //this is the millisecond increment for smooth motion

#define ROT_MAX 4096
#define TILT_MAX 1308

#define ROT_HOME 0
#define TILT_HOME 1137

const PROGMEM uint16_t arraySize = 300;//BTILT * BROT * 10;
float t = 0;
float theta = 0;
float phi = 0;


const PROGMEM uint16_t Center[] = {2, 2048, 2048};
const PROGMEM uint16_t Home[] = {2, 0, TILT_HOME};

#endif
