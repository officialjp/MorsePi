#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "includes/potentiometer.h"

#define POTENTIOMETER_PIN       26      // Pin 31 (GPIO 26, ADC 0)
#define POTENTIOMETER_MIN       20
#define POTENTIOMETER_MAX       4050

//initialises the potentiometer
void potentiometer_init() {
    adc_init();
    adc_gpio_init(POTENTIOMETER_PIN);
}

//reads the raw input given by the potentiometer
unsigned int potentiometer_read_raw() {
    adc_select_input(POTENTIOMETER_PIN - 26);
    return adc_read();
}

//maps the input to a certain structure
int map(
    int value,
    int original_min,
    int original_max,
    int min,
    int max
) {
    int original_range = original_max - original_min;
    int range = max - min;

    return (value - original_min) * range / original_range + min;
}

//clumps the input
int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

//reads the potentiometer with a given limit
unsigned int potentiometer_read(unsigned int limit) {
    return map(
        clamp(potentiometer_read_raw(), POTENTIOMETER_MIN, POTENTIOMETER_MAX),
        POTENTIOMETER_MIN, POTENTIOMETER_MAX,
        0, limit
    );
}
