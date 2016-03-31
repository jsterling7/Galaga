// bmptoc.c
// Name: Joshua Sterling

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

// This is the array into which you will load the raw data from the file
// You don't have to use this array if you don't want to, but you will be responsible
// for any errors caused by erroneously using the stack or malloc if you do it a
// different way, incorrectly!
char data_arr[0x36 + 240 * 160 * 4];

int main(int argc, __attribute__((unused)) char *argv[]) {

	// 1. Make sure the user passed in the correct number of arguments
	if (argc != 2) {
		printf("You have given %d argument/s and there should be exactly 2.\n", argc);
		return 0;
	}

	// 2. Open the file. If it doesn't exist, tell the user and then exit
	FILE *myFile = fopen(argv[1], "r");
	if (myFile == NULL) {
		printf("The file, '%s' does not exist.", argv[1]);
		return 0;
	}

	// 3. Read the file into the buffer then close it when you are done
	int bytes_read = fread(data_arr, 1, 0xFFFFFF, myFile);
	bytes_read = bytes_read;
	fclose(myFile);

	// 4. Get the width and height of the image
	int width = *(int*) (data_arr + 0x12);
	int height = *(int*) (data_arr + 0x16);


	// 5. Create header file, and write header contents. Close it
	char fileNameH[100];
	strcpy(fileNameH, argv[1]);
	char current = 'f';
	int length = 0;
	while (current != '\0') {
		current = fileNameH[length];
		length++;
	}
	fileNameH[length - 3] = '\0';
	fileNameH[length - 4] = 'h';


	FILE *header = fopen(fileNameH, "w");
	fileNameH[length - 5] = '\0';
	for (int i = 0; i < length; i++) {
		fileNameH[i] = toupper(fileNameH[i]);
	}
	char lines[1000];
	sprintf(lines, "#define %s_WIDTH %d\n#define %s_HEIGHT %d\nconst unsigned short data[%d];\n", fileNameH, width, fileNameH, height, (width*height));

	fprintf(header, "%s", lines);

	fclose(header);


	// 6. Create C file, and write pixel data. Close it
	char fileNameC[100];
	strcpy(fileNameC, argv[1]);
	char current2 = 'f';
	int length2 = 0;
	while (current2 != '\0') {
		current2 = fileNameC[length2];
		length2++;
	}
	fileNameC[length2 - 3] = '\0';
	fileNameC[length2 - 4] = 'c';

	FILE *dataFile = fopen(fileNameC, "w");
	fprintf(dataFile, "const unsigned short data[%d] = {\n", (height * width));
	for (int i = (height - 1); i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			char* spot = data_arr + (0x36 + 4 * (width * i + j));
			short blue = *(char*) (spot) & 0xFF;
			short green = *(char*) (spot + 1) & 0xFF;
			short red = *(char*) (spot + 2) & 0xFF;
			blue = blue / 8;
			blue = blue << 10;
			green = green / 8;
			green = green << 5;
			red = red / 8;
			unsigned short final = red | green | blue;
			fprintf(dataFile, "0x%x,\n", final);
		}
	}
	fprintf(dataFile, "};\n");
	fclose(dataFile);

	return 0;
}
