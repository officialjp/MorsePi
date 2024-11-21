#include <stdio.h>
#include "hardware/pwm.h"
#include "includes/rgb.h"
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

void setup_rgb()
{
    // Tell the LED pins that the PWM is in charge of its value.
    gpio_set_function(R, GPIO_FUNC_PWM);
    gpio_set_function(G, GPIO_FUNC_PWM);
    gpio_set_function(B, GPIO_FUNC_PWM);

    // Figure out which slice we just connected to the LED pin, this is done for the other colors below
    uint slice_num = pwm_gpio_to_slice_num(R);
    // Get the defaults for the slice configuration. By default, the
    // counter is allowed to wrap over its maximum range (0 to 2**16-1)
    pwm_config config = pwm_get_default_config();
    // Load the configuration into our PWM slice, and set it running.
    pwm_init(slice_num, &config, true);

    slice_num = pwm_gpio_to_slice_num(G);
    pwm_init(slice_num, &config, true);

    slice_num = pwm_gpio_to_slice_num(B);
    pwm_init(slice_num, &config, true);
}

// Allow a colour value [0,255] and scale it up to uint16_t [0,65535].
// Then scale it by brightness (out of 100) and invert the value (LED low is ON).
void show_rgb(int r, int g, int b, int BRIGHTNESS)
{
    printf("Showing RGB: %u %u %u\n", r, g, b);
    pwm_set_gpio_level(R, ~(MAX_PWM_LEVEL * r / MAX_COLOUR_VALUE * BRIGHTNESS / 100));
    pwm_set_gpio_level(G, ~(MAX_PWM_LEVEL * g / MAX_COLOUR_VALUE * BRIGHTNESS / 100));
    pwm_set_gpio_level(B, ~(MAX_PWM_LEVEL * b / MAX_COLOUR_VALUE * BRIGHTNESS / 100));
}

// if direction is UP (which is true), the value of r,g or b will be increased
// if direction is DOWN (which is false), the value of r,g or b will be decreased
int loop_colour(int r, int g, int b, int brightness, char colourToIncrement, bool direction)
{
    for (int i = 0; i < MAX_COLOUR_VALUE; i++)
    {
        switch (colourToIncrement)
        {
        case 'r':
            r = direction ? r + 1 : r - 1;
            break;
        case 'g':
            g = direction ? g + 1 : g - 1;
            break;
        case 'b':
            b = direction ? b + 1 : b - 1;
            break;
        }
        show_rgb(r, g, b, brightness);
        sleep_ms(LOOP_SLEEP);
    }

    return direction ? MAX_COLOUR_VALUE : 0;
}