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
char morse[124];
char letters[124];
bool isPressed;
struct timeval start, end;
double diff, startTime ,endTime;

void clearArray(char array[]) {
	for (int x = 0; x<sizeof(array), x++){
		array[x] = '';
	}
}

void inputInArray(char array[],char input) {
	for (int x = 0; x<sizeof(array); x++){
		if (array[x] == ''){
			array[x] = input;
		}
	}
}

int countItemsInArray(char array[]) {
	int count = 0;
	for (int x = 0; x<sizeof(array); x++){
		if (array[x] != '' || array[x] != '/'){
			count++;
		}
	}
	return count;
}

void morseCodeToLetters(){
	const char *letter = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??";
	int index = 1;
	if (countItemsInArray(morse) < 1) {
		clearArray(morse);
		//red for invalid, green for valid rgb
		//play negative buzzer sound
	} else {
		for (int i = 0; i<sizeof(morse); i++) {
			if (morse[i] == '.') {
				index = index*2;
			} else if (morse[i] == '-') {
				index = (index*2)+1;
			} else {
				inputInArray(letters,letter[index])
				displayLetter(index);
				index = 1;
				//change rgb to green here
			}
		}
	}
}

void displayLetter(int index) {
	seven_segment_off();
	seven_segment_show(index);
	sleep_ms(500);
}

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

	//clear the arrays
	clearArray(morse);
	clearArray(letters);

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

void debugArray(char array[]) {
	for(int i = 0; i<sizeof(array); i++) {
		printf("%c \n", array[i]);
	}
}

void displayAllItemsInArray(char array[]) {
	for(int i = 0; i<sizeof(array); i++){
		printf("%c", array[i]);
	}
	printf("\n");
}

void checkButton(double clock){
	if ((countItemsInArray(letters) % 4) == 0) {
		displayAllItemsInArray(letters);
		//play short tune

		//Your program should count how many correct letters have been put in, ignore any 
		//incorrect inputs, if the number of correct letters reaches four, the buzzer plays a 
		//short tune, the program displays a decoded message on the console. The program 
		//then prompts the user to decide whether they want to continue or exit the program.
		//a.
		//Left button = “Yes” to reset all components and continue;
		//b.
		//Right button = “No” to turn off all components and terminate the program;
		//c.
		//The RBG LED lights up briefly when the user is making the choice (red = 
		//terminate, green = continue).
	} else {
		if (countItemsInArray(morse) < 5) {
			if (clock > 4) { //potentiometer input
				printf("Deez nuts"); //make buzzer stuff
			//make the rgb red
			} else if (clock >= 0.4) { 
				inputInArray(morse, '/');
				morseCodeToLetters();
			} else if (clock >= 0.25) {
				inputInArray(morse, '-');
			} else {
				inputInArray(morse, '.');
			}
		} else {
			clearArray(morse);
			//scream at user irl
		}
	}
	//debugArray();
    // a function to be implemented
}

