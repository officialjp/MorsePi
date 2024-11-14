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
char morse[4];
char letters[4];
bool isPressed;
struct timeval start, end;
double diff, startTime ,endTime;


void inputInArray(char array[],char input) {
	for (int x = 0; x<sizeof(array); x++){
		if (array[x] == ''){
			array[x] = input;
		}
	}
}

void morseCodeToLetters(char code){
	const char *letter = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??";
	int index = 1;
	for (int i = 0; i<sizeof(morse); i++) {
		if (morse[i] == '.') {
			index = index*2;
		} else if (morse[i] == '-') {
			index = (index*2)+1;
		} else {
			inputInArray(letters,letter[index])
			index = 1;
		}
	}
}

// ----------------------------------------------------------char character[] = {'/'};
		strcat(morse, character);----------
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

	// Initialise the button"s GPIO pin.
	gpio_init(BUTTON_PIN);
	gpio_set_dir(BUTTON_PIN, GPIO_IN);
	gpio_pull_down(BUTTON_PIN); // Pull the button pin towards ground (with an internal pull-down resistor).

	while (true) {
		gettimeofday(&start, NULL);
		while (gpio_get(BUTTON_PIN)) { 
			startTime = start.tv_sec + start.tv_usec / 1000000.0;
			isPressed = true;
		} 

		if(isPressed){
			gettimeofday(&end, NULL);
			endTime = end.tv_sec + end.tv_usec / 1000000.0;
			diff = endTime-startTime;
			isPressed = false;
			checkButton(diff);
		}
	}
}

void decoder(){
    // a function to be implemented
}

void debugArray() {
	for(int i = 0; i<255; i++) {
		printf("%c \n", morse[i]);
	}
}


void checkButton(double clock){
	if (clock >= 0.4) { 
		inputInArray(morse, '/');
	} else if (clock >= 0.25) {
		inputInArray(morse, '-');
	} else {
		inputInArray(morse, '.');
	}
	//debugArray();
    // a function to be implemented
}

