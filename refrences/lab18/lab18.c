/* CS 2110 Lab 18
 * YOUR NAME HERE: Joshua Sterling
 */

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// TODO 1: write a function here that will swap two ints

	void swapFunction(int* a1, int* b1);



int main() {

	int a = 5;
	int b = 8;

	printf("--------------------------------\n");
	printf("Value of a: %d\nValue of b: %d\n", a, b);

	// TODO 2: call your swap function with a and b. They should swap
	swapFunction(&a, &b);



	printf("Swapped a: %d\nSwapped b: %d\n", a, b);
	printf("--------------------------------\n\n");

	const unsigned char data[10] = {
		0x4C, 0x37, 0x71, 0x19, 0xF5, 0x29, 0x08, 0xC6, 0x2B, 0x8D
	};
	unsigned short c = 0x0000;

	printf("--------------------------------\n");
	printf("Short value at data + 5: 0x0829\n");

	// TODO 3: set c to the short value starting at offset 5 in data

	c = *(unsigned short*) (data + 5);



	printf("Value of c: 0x%04X\n", c);
	printf("--------------------------------\n\n");

	char buffer[50];
	strcpy(buffer, "CS 2110 is awesome");

	printf("--------------------------------\n");
	printf("Original buffer: \"%s\"\n", buffer);

	// TODO 4: capitalize the buffer using toupper

	for (int i = 0; i < 50; i++) {
		buffer[i] = toupper(buffer[i]);
	}



	printf("Capitalized buffer: \"%s\"\n", buffer);
	printf("--------------------------------\n\n");

	const char const *string = "I dont always start assignments early";
	const char *ptr = string;

	printf("--------------------------------\n");
	printf("Original string: \"%s\"\n", string);

	// TODO 5: set "ptr" to the address of the first 'a' in string

	for (int i = 0; *ptr != 'a' && *ptr; i++) {
		ptr = string + i;
	}




	printf("ptr points to: \"%s\"\n", ptr);
	printf("--------------------------------\n\n");

	// Assertions to verify your solution. Do not modify!
	assert(a == 8 && b == 5);
	assert(c == 0x0829);
	assert(!strcmp(buffer, "CS 2110 IS AWESOME"));
	assert(!strcmp(ptr, "always start assignments early"));
	printf("Passed the tests!\n");
	return 0;
}

void swapFunction(int* a1, int* b1) {
	int c = 0;
	c = *a1;
	*a1 = *b1;
	*b1 = c;
}
