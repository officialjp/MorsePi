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
#include "includes/potentiometer.h"
#include "includes/buzzer.h"

#define BUTTON_PIN			16	// Pin 21 (GPIO 16)

// declare global variables e.g., the time when the button is pressed 
char morse[124];
char letters[124];
int mcdonalds[] = {262,294,330,466,523};
bool isPressed;
struct timeval start, end;
double diff, startTime ,endTime;

void clearArray(char array[]) {
	for (int x = 0; x<124; x++){
		array[x] = '\0';
	}
}

void playMcDonalds() {
	buzzer_enable(mcdonalds[0],0.1);
	sleep_ms(20);
	buzzer_enable(mcdonalds[1],0.1);
	sleep_ms(40);
	buzzer_enable(mcdonalds[2],0.1);
	sleep_ms(40);
	buzzer_enable(mcdonalds[3],0.1);
	sleep_ms(5);
	buzzer_enable(mcdonalds[4],0.1);
	sleep_ms(40);
	buzzer_enable(mcdonalds[3],0.1);
	sleep_ms(180);
	buzzer_enable(0,0);
}

void inputInArray(char array[],char input) {
	for (int x = 0; x<124; x++){
		if (array[x] == '\0'){
			array[x] = input;
			break;
		}
	}
}

int countItemsInArray(char array[]) {
	int count = 0;
	for (int x = 0; x<124; x++){
		if(array[x] != '\0' && array[x] != '/') {
			count++;
		}
	}
	return count;
}

int displayLetter(int index) {
	seven_segment_off();
	seven_segment_show(index);
	clearArray(morse);
	sleep_ms(500);
	return 0;
}

void morseCodeToLetters(){
	const char *letter = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??";
	int index = 1;
	if (countItemsInArray(morse) < 1) {
		clearArray(morse);
		//red for invalid, green for valid rgb
		//play negative buzzer sound
	} else {
		for (int i = 0; i<124; i++) {
			if (morse[i] == '.') {
				index = index*2;
			} else if (morse[i] == '-') {
				index = (index*2)+1;
			} else {
				inputInArray(letters,letter[index]);
				printf("%c", letter[index]);
				displayLetter(index);
				index = 1;
				break;
				//change rgb to green here
			}
		}
	}
}

void checkButton(double clock){
	if (clock >= 0.4) { 
		printf("/");
		inputInArray(morse, '/');
		if (countItemsInArray(morse) < 5) {
			morseCodeToLetters();
		} else {
			printf("Error! Too many morse values!\n");
			clearArray(morse);
			buzzer_enable(1250,0.1);
			show_rgb(255,0,0,50);
			sleep_ms(2000);
			show_rgb(0,255,0,50);
			buzzer_enable(0,0);
			sleep_ms(1000);
			show_rgb(0,0,0,0);
		}
	} else if (clock >= 0.3) {
		printf("-");
		buzzer_enable(220,0.1);
		sleep_ms(100);
		buzzer_enable(0,0);
		inputInArray(morse, '-');
	} else {
		printf(".");
		buzzer_enable(440,0.1);
		sleep_ms(100);
		buzzer_enable(0,0);
		inputInArray(morse, '.');
	}
}

void debugArray(char array[]) {
	for(int i = 0; i<124; i++) {
		printf("%c \n", array[i]);
	}
}

void displayAllItemsInArray(char array[]) {
	for(int i = 0; i<124; i++){
		printf("%c", array[i]);
	}
	printf("\n");
}

int main() {
	timer_hw->dbgpause = 0;
	stdio_init_all();

	// Initialise the seven segment display.
	seven_segment_init();
	seven_segment_off();

	//setting up all the components
	buzzer_init();
	playMcDonalds();
	setup_rgb();
	//potentiometer_init();
	show_rgb(0,255,0,50);
	sleep_ms(2000);
	show_rgb(0,0,0,0);

	//Displays the number 8 and a welcome message then clears the display
	seven_segment_show(8);
	printf("Welcome to MorsePi\n");
	sleep_ms(1000);
	seven_segment_off();

	//clear the arrays
	// clearArray(morse);
	// clearArray(letters);

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
<<<<<<< HEAD
=======
}

void debugArray(char array[]) {
	for(int i = 0; i<124; i++) {
		printf("%c \n", array[i]);
	}
}

void displayAllItemsInArray(char array[]) {
	for(int i = 0; i<124; i++){
		printf("%c", array[i]);
	}
	printf("\n");
}

void checkButton(double clock){
	if (clock >= 0.7) { 
		printf("/");
		inputInArray(morse, '/');
		if (countItemsInArray(morse) < 5) {
			morseCodeToLetters();
		} else {
			printf("Error! Too many morse values!\n");
			clearArray(morse);
			buzzer_enable(1250,0.1);
			show_rgb(255,0,0,50);
			sleep_ms(2000);
			show_rgb(0,255,0,50);
			buzzer_enable(0,0);
			sleep_ms(1000);
			show_rgb(0,0,0,0);
		}
	} else if (clock >= 0.3) {
		printf("-");
		buzzer_enable(220,0.1);
		sleep_ms(100);
		buzzer_enable(0,0);
		inputInArray(morse, '-');
	} else {
		printf(".");
		buzzer_enable(440,0.1);
		sleep_ms(100);
		buzzer_enable(0,0);
		inputInArray(morse, '.');
	}
>>>>>>> refs/remotes/origin/main
}