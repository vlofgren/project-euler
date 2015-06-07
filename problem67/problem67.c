#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int *data = NULL;
int data_length = 0;

/** This is found from solving
 * i = N*(N+1) / 2 for N
 */
int row_from_index(int idx) {
	return sqrt(2*idx + 0.25) - 0.5;
}

void print() {
	int row = 0;
	for (int i = 0; i < data_length; i++) {
		if (row_from_index(i) != row) {
			printf("\n"); row++;
		}
		printf("%d ", data[i]);
	}
	printf("\n -- \n");
}

void read_file(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Could not read file '%s'", filename);
		exit(EXIT_FAILURE);
	}

	int lines = 0;

	for (;;) {
		int nextc = fgetc(file);
		if (nextc == '\n') {
			lines++;
		}
		else if (nextc == EOF) {
			break;
		}
	}

	rewind(file);

	data_length = lines*(lines+1)/2;
	printf("Found %d lines, allocating for triangular buffer of size %d\n", lines, data_length);
	data = calloc(sizeof(int), data_length);

	for (int i = 0; i < data_length; i++) {
		if (fscanf(file, "%d", data+i) != 1) {
			printf("Failed to read number index %d", i);
		}
	}

	fclose(file);
}

void main() {
	read_file("p067_triangle.txt");

	for (int i = data_length - 1; i > 0; --i) {
		int row = row_from_index(i);
		int row_start = row*(row+1) / 2;
		int row_index = i - row_start;

		if (row_index == 0) {
			continue;
		}

		int largest_value = data[i] > data[i-1] ? data[i] : data[i-1];
		int previous_row_start = row*(row-1) / 2;
		data[previous_row_start + row_index - 1] += largest_value;
	}

	printf("Max path = %d\n", data[0]);
}
