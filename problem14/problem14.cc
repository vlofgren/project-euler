#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdint>

typedef uint32_t num_t; // signed int is too small it seems

inline num_t collNext(num_t n) {
	return (n & 1)
		? (3*n + 1)
		: (n >> 1);
}

int main() {
	// std::map makes this code run about twice as slow
	std::unordered_map<num_t, num_t> collKnown;
	collKnown.reserve(3000000);
	// about 3kk appears to be the point of diminishing returns for
	// pre-reserving capacity for the hash map

	std::vector<num_t> collUnknown;
	collUnknown.reserve(800);

	collKnown[1] = 0;
	std::pair<num_t, num_t> result = {1, 0};

	for (int v = 2; v < 1000000; v++) {

		for (num_t i = v;; i = collNext(i)) {
			auto iter = collKnown.find(i);
			if (iter == collKnown.end()) {
				collUnknown.push_back(i);
			}
			else {
				num_t res = iter->second;
				std::for_each(collUnknown.rbegin(), collUnknown.rend(), 
						[&](num_t k) { collKnown[k] = ++res; });

				num_t candidate = collKnown[v];
				if (result.second < candidate) {
					result = { v, candidate };
				}
				break;
			}

		}
		
		collUnknown.clear();
	}

	std::cout << result.first << ", " << result.second << std::endl;
	return EXIT_SUCCESS;
}


