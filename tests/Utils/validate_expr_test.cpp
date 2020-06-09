#include <define.hpp>

int main(int argc, char **argv) {
	if (argc < 3) {
		return 1;
	}
	
	const std::string & INPUT(argv[1]);
	const std::string & OUTPUT(argv[2]);
	
	return validate_expression(INPUT) != OUTPUT;
}
