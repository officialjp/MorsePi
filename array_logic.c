#include "includes/array_logic.h"
#include <stdio.h>
void clearArray(char array[]) {
  	//fills the array with empty characters
	for (int x = 0; x<16; x++){
		array[x] = '\0';
	}
}

void displayAllItemsInArray(char array[]) {
  	//displays all the items in the array
	for(int i = 0; i<16; i++){
		printf("%c", array[i]);
	}
	printf("\n");
}

void inputInArray(char array[],char input) {
  	//inputs an item on the next empty input in a character array
	for (int x = 0; x<16; x++){
		if (array[x] == '\0'){
			array[x] = input;
			break;
		}
	}
}

int countItemsInArray(char array[]) {
  	//counts the number of valid characters in an array (not counting / for obvious reasons)
	int count = 0;
	for (int x = 0; x<16; x++){
		if(array[x] != '\0' && array[x] != '/') {
			count++;
		}
	}
	return count;
}