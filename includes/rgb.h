#include <stdio.h>
#include "hardware/pwm.h"
#include "pico/stdlib.h"

//Define pin numbers
#define R 13 
#define G 12 
#define B 11 

#define LOOP_SLEEP 10
#define MAX_COLOUR_VALUE 255
#define MAX_PWM_LEVEL 65535

#define UP true
#define DOWN false

void setup_rgb();
// Allow a colour value [0,255] and scale it up to uint16_t [0,65535].
// Then scale it by brightness (out of 100) and invert the value (LED low is ON).
void show_rgb(int r, int g, int b, int BRIGHTNESS);

// if direction is UP (which is true), the value of r,g or b will be increased
// if direction is DOWN (which is false), the value of r,g or b will be decreased
int loop_colour(int r, int g, int b, int brightness, char colourToIncrement, bool direction);