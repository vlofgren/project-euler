#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	ifstream input("p059_cipher.txt");
	vector<int> data;
	vector<int> out;

	int num = 0;
	while (!input.eof()) {
		int next = input.get();

		if (next == '\n' || next == ',') {
			data.push_back(num);
			num = 0;
			continue;
		}
		if (next < '0') {
			continue;
		}

		num = num * 10 + (next - '0');
	}

	input.close();

	int len = data.size();
	out.resize(len);

	int maxalpha = -1;
	long sum = 0;

	for (char a = 'a'; a <= 'z'; a++) {
		for (char b = 'a'; b <= 'z'; b++) {
			for (char c = 'a'; c <= 'z'; c++) {
				out.clear();
				for (int idx = 0; idx < len; idx++) {
					if (idx % 3 == 0) {
						out.push_back((data[idx] ^ a) & 0xFF);
					}
					else if (idx % 3 == 1) {
						out.push_back((data[idx] ^ b) & 0xFF);
					}
					else if (idx % 3 == 2) {
						out.push_back((data[idx] ^ c) & 0xFF);
					}
				}

				int alphaness = 0;

				for_each(out.begin(), out.end(), [&](int val) { if (isalpha(val)) { alphaness ++; } });

				if (alphaness > maxalpha) {
					sum = 0;
					maxalpha = alphaness;
					
					for_each(out.begin(), out.end(), [&](int val) { printf("%c", val); sum += val; });

					printf("\n\nKeyphrase = %c %c %c, sum of ascii = %ld\n\n", a,b,c, sum);
				}

			}
		}
	}

}
