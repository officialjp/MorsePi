#include <stdio.h>
#include <time.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"
#include "includes/potentiometer.h"
#include "includes/buzzer.h"
#include "includes/rgb.h"
#include <stdlib.h>
#include <sys/time.h>
#include "includes/array_logic.h"

//declares the values for the right and left button pins
#define BUTTON_PIN			16	// Pin 21 (GPIO 16)
#define RIGHT_PIN			22

// declare global variables e.g., the time when the button is pressed 
char morse[16];
char letters[16];
bool isPressed;
struct timeval start, end;
double diff, startTime, endTime;
unsigned int timeLimit = 4;

int displayLetter(int index) {
  	//displays a letter given a certain index
	seven_segment_off();
	seven_segment_show(index);
	clearArray(morse);
	sleep_ms(500);
	return 0;
}

void generalError() {
	//this function is just a general error that will play a buzzer, show a red light and show an error on the seven segment display
	seven_segment_show(24);
	show_rgb(255,0,0,50);
    buzzer_enable(1250,0.1);
    sleep_ms(150);
    buzzer_enable(0,0);
	show_rgb(0,0,0,0);
	seven_segment_off();
}

void morseCodeToLetters(){
  	//searches the tree for the correct letter given a morse code
	const char *letter = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??";
	int index = 1;
    //if the array is invalid and has less than 1 morse character run an error
	if (countItemsInArray(morse) < 1) {
		clearArray(morse);
		generalError();
	} else {
        //add the letter into an array of letters depending on which morse inputs it was given
		for (int i = 0; i<16; i++) {
			if (morse[i] == '.') {
				index = index*2;
			} else if (morse[i] == '-') {
				index = (index*2)+1;
			} else {
                //if the morse is not invalid add the letter to the array and display a green rgb
                if (letter[index] != '?') {
                	inputInArray(letters,letter[index]);
                	printf("%c", letter[index]);
                	displayLetter(index);
					printf("\n");
                	index = 1;
                	show_rgb(0,255,0,50);
					sleep_ms(250);
					show_rgb(0,0,0,0);
                	break;
                //if the morse is invalid don't and call generalError
                } else {
                	generalError();
                    printf("Invalid morse code!");
                    clearArray(morse);
                    break;
                }
			}
		}
	}
}

void promptUser() {
  	//prompts the user if they would like to continue the program or not, displays all the letters.
	show_rgb(0,0,255,50);
    buzzer_enable(1250,0.1);
    sleep_ms(500);
    buzzer_enable(0,0);
    displayAllItemsInArray(letters);
	playMcDonalds();
	printf("Would you like to continue? Left = yes, Right = no!\n");
	//check if button is pressed
	while(true) {
		//if button pressed is the no button, exit the program and turn off all components
		if(gpio_get(RIGHT_PIN)) {
            show_rgb(255,0,0,50);
            printf("Exiting! the program");
			sleep_ms(2500);
			show_rgb(0,0,0,0);
			seven_segment_off();
			buzzer_disable();
            exit(1);
        }
		//if the button pressed is the yes button, continue running the morse decode algorithm
        if(gpio_get(BUTTON_PIN)) {
          	show_rgb(0,255,0,50);
            printf("Continuing! the program\n");
			sleep_ms(250);
			show_rgb(0,0,0,0);
			clearArray(letters);
            break;
		}
    }
}

void checkButtonErrors() {
  	//an error function that will play if the code runs into an error
	clearArray(morse);
	buzzer_enable(1250,0.1);
	seven_segment_show(24);
	show_rgb(255,0,0,50);
	sleep_ms(1000);
	show_rgb(0,255,0,50);
	buzzer_enable(0,0);
	sleep_ms(500);
	show_rgb(0,0,0,0);
	seven_segment_off();
}

void checkButton(double clock){
    //checks the different clock times and does each action respectively i.e adding a dot or a dash
    if (clock > timeLimit) {
        printf("Error! You took too long!\n");
        checkButtonErrors();
    } else if (clock >= 0.3) {
    	printf("-");
    	buzzer_enable(220,0.1);
    	sleep_ms(250);
    	buzzer_enable(0,0);
    	inputInArray(morse, '-');
    } else {
    	printf(".");
    	buzzer_enable(220,0.1);
        sleep_ms(100);
    	buzzer_enable(0,0);
    	inputInArray(morse, '.');
    }
}

void promptPotentiometer() { 
	//changes the time limit of a letter by a given potentiometer input
	show_rgb(0,0,255,50);
	//asks the user if they would like this change
	printf("Change overall time limit per letter? Left = yes, Right = no!\n");
	while(true) {
		if(gpio_get(RIGHT_PIN)) {
            printf("Time limit is 4 seconds\n");
            break;
        }
        if(gpio_get(BUTTON_PIN)) {
			timeLimit = potentiometer_read(3) + 1; //should allow between 1 and 4
            printf("Time limit is %d\n", timeLimit);
            break;
		}
    }
	show_rgb(0,0,0,0);
}

int main() {
	timer_hw->dbgpause = 0;
	stdio_init_all();

	// Initialise the seven segment display.
	seven_segment_init();
	seven_segment_off();

	//setting up all the components
	buzzer_init();
	setup_rgb();
	potentiometer_init();

	//Displays the number 8 and a welcome message then clears the display
	show_rgb(0,255,0,50);
	seven_segment_show(24);
	printf("Welcome to MorsePi\n");
	sleep_ms(1000);
	seven_segment_off();
	show_rgb(0,0,0,0);

	//Prompt for time in the potentiometer
	promptPotentiometer();
	sleep_ms(250);

	// Initialise the buttons GPIO pins.
    gpio_init(RIGHT_PIN);
	gpio_init(BUTTON_PIN);
	gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_set_dir(RIGHT_PIN, GPIO_IN);
	gpio_pull_down(BUTTON_PIN); // Pull the button pin towards ground (with an internal pull-down resistor).
    gpio_pull_down(RIGHT_PIN);

    //While loop for left button
	while (true) {
		//checks the time using the computer clock
		gettimeofday(&start, NULL);
		gettimeofday(&end, NULL);
		endTime = end.tv_sec + end.tv_usec / 1000000.0;
		diff = endTime-startTime;
		//if the time is above a certain inter-signal time it will decode the morse
		if(diff > 0.7 && countItemsInArray(morse) > 0) {
			//prints a "/" for clarity between letters and morse
			printf("/");
    		inputInArray(morse, '/');
    		if (countItemsInArray(morse) < 5) {
    			morseCodeToLetters();
    		} else {
    			printf("Error! Too many morse values!\n");
    			checkButtonErrors();
    		}
		}
        //Gets the time of when the button has started being held
		while (gpio_get(BUTTON_PIN)) { 
			startTime = start.tv_sec + start.tv_usec / 1000000.0;
			isPressed = true;
		}
		//if there are 4 letters in the array prompt the user whether they would like to continue or not
		if (countItemsInArray(letters) == 4) {
        	//if they have, prompt the user with the left button being continue and the right button being stop
			promptUser();
		}
		//Uses that time and passes it into a function
		if(isPressed){
			gettimeofday(&end, NULL);
			endTime = end.tv_sec + end.tv_usec / 1000000.0;
			diff = endTime-startTime;
			isPressed = false;
			checkButton(diff);
		}
	}
}