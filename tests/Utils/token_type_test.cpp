#include <define.hpp>

#include <cstring>

int main(int argc, char **argv) {
	if (argc < 3) {
		return 1;
	}
	
	int result = -1;
	int multiplier = 1;
	
	char * result_str = nullptr;
	if (argv[2][0] != '-') {
		result_str = argv[2];
	} else {
		int size = std::strlen(argv[2]) - 1;
		result_str = new char[size];
		std::memcpy(result_str, argv[2] + 1, size);
		multiplier = -1;
	}
	
	try {
		result = std::stoi(result_str);
	} catch (std::exception) {
		return 1;
	}
	
	result *= multiplier;
	
	return get_token_type(argv[1]) == static_cast<token_t>(result) ? 0 : 1;
}
