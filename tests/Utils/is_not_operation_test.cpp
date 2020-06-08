#include <define.hpp>

int main(int argc, char **argv) {
	if (argc < 3) {
		return 1;
	}
	
	try {
		int size = std::stoi(argv[1]) + 2;
		for (int i = 2; i < size; ++i) {
			if (is_operation(argv[i][0]) == true) {
				return 1;
			}
		}
		
		return 0;
	} catch (std::exception) {
		return 1;
	}
}
