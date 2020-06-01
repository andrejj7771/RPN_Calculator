#include <RPN/RPN_Converter.hpp>

#include <cstdio>

int main(int argc, char **argv) {
	if (argc < 3) {
		return 1;
	}
	
	const std::string INPUT(argv[1]);
	const std::string OUTPUT(argv[2]);
	
	RPN::converter converter(INPUT);
	converter.convert();
	
	const std::string & result = converter.converted_expression();
	
	return result == OUTPUT ? 0 : 1;
}
