#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int data[] =
{ 75,
95,64,
17,47,82,
18,35,87,10,
20,04,82,47,65,
19,01,23,75,03,34,
88,02,77,73,07,63,67,
99,65,04,28,06,16,70,92,
41,41,26,56,83,40,80,70,33,
41,48,72,33,47,32,37,16,94,29,
53,71,44,65,25,43,91,52,97,51,14,
70,11,33,28,77,73,17,78,39,68,17,57,
91,71,52,38,17,14,91,43,58,50,27,29,48,
63,66,04,68,89,53,67,30,73,16,69,87,40,31,
04,62,98,27,23,9,70,98,73,93,38,53,60,04,23 };

int data_length = 120;

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

void main() {

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

	printf("%d\n", data[0]);
}
