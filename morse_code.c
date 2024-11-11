/**
 * The given template is a guideline for your coursework only.
 * You are free to edit/create any functions and variables.
 * You can add extra C files if required.
*/


#include <stdio.h>
#include <time.h>
#include <string.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"

#define BUTTON_PIN			16	// Pin 21 (GPIO 16)

// declare global variables e.g., the time when the button is pressed 
int pressed ;
char morse[256];
double time1, time_diff;

// --------------------------------------------------------------------
// declare the function definitions, e.g, decoder(...); and ther functions
// given the user input, you can decode if the input is a character
void decoder();

// check if the button press is a dot or a dash
void checkButton();

int main() {
	timer_hw->dbgpause = 0;
	stdio_init_all();

	// Initialise the seven segment display.
	seven_segment_init();
	seven_segment_off();

	//Displays the number 8 and a welcome message then clears the display
	seven_segment_show(8);
	printf("Welcome to MorsePi\n");
	sleep_ms(1000);
	seven_segment_off();

	// Initialise the button's GPIO pin.
	gpio_init(BUTTON_PIN);
	gpio_set_dir(BUTTON_PIN, GPIO_IN);
	gpio_pull_down(BUTTON_PIN); // Pull the button pin towards ground (with an internal pull-down resistor).

	while (true) {

		while (gpio_get(BUTTON_PIN)){			
            // record how long the button is pressed
            time1 = (double) clock();
			time1 = time1 / CLOCKS_PER_SEC;
		} 
        time_diff = (((double) clock()) / CLOCKS_PER_SEC) - time1;
		checkButton();
	}
}

void decoder(){
    // a function to be implemented
}

void checkButton(double clock){
	if (clock > 250) { 
		morse[0] = '-'
	} else {
		morse[0] = '.'
	}
    // a function to be implemented
}

