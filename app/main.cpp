#include <iostream>
#include <cstring>

#include <RPN/RPN_Converter.hpp>
#include <Solver/Solver.hpp>

void show_help() {
	std::cout << "-s | --solve [expression ...] - solve an expression" << std::endl;
	std::cout << "-c | --convert [exression ...] - convet an expression to RNP" << std::endl;
	std::cout << "-h | --help - show help" << std::endl;
}

void check_args(int argc, char ** argv) {
	if (std::memcmp(argv[1], "-h", 2) == 0 || std::memcmp(argv[1], "--help", 6) == 0) {
		show_help();
	} else if (std::memcmp(argv[1], "-s", 2) == 0 || std::memcmp(argv[1], "--solve", 7) == 0) {
		Solver::solver_ptr solver = std::make_shared<Solver::solver>();
		
		for (int i = 2; i < argc; ++i) {
			std::string expr(argv[i]);
			float result = 0;
			
			if (!solver->calculate(expr, result)) {
				std::cout << "\"" + expr + "\" cannot be solved" << std::endl;
				continue;
			}
			
			std::cout << expr << "=" << result << std::endl;
		}
	} else if (std::memcmp(argv[1], "-c", 2) == 0 || std::memcmp(argv[1], "--convert", 9) == 0) {
		RPN::converter_ptr converter = std::make_shared<RPN::converter>();
		
		for (int i = 2; i < argc; ++i) {
			std::string expr(argv[i]);
			converter->set_expression(expr);
			converter->convert();
			std::cout << converter->converted_expression() << std::endl;
		}
	} else {
		std::cout << "unkown command" << std::endl;
		show_help();
	}
}

int main(int argc, char **argv) {
	if (argc > 1) {
		check_args(argc, argv);
		return 0;
	}
	
	show_help();
	return 0;
}
