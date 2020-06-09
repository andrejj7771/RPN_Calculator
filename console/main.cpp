#include <iostream>
#include <cstring>

#include <RPN/RPN_Converter.hpp>
#include <Solver/Solver.hpp>

void show_help() {
	std::cout << "show help: --help | -h\n";
	std::cout << "solve expressions: --solve | -s"
				 " [a string with expressions separated by semicolons]\n";
}

std::vector<std::string> split(const std::string & string,
							   char separator)
{
	std::vector<std::string> splitted;
	
	size_t pos = 0;
	size_t index = 0;
	while(index != std::string::npos) {
		index = string.find_first_of(separator, pos);
		
		splitted.push_back(string.substr(pos, index - pos));
		pos = index + 1;
	}
	
	if (*(splitted.end() - 1) == "") {
		splitted.pop_back();
	}
	
	return splitted;
}

void solve_args_expressions(const Solver::solver_ptr & solver,
							const std::string & exprs)
{
	std::vector<std::string> expressions = split(exprs, ';');
	
	float result = 0;
	for (const std::string & expr : expressions) {
		std::string tmp_expr = validate_expression(expr);
		std::cout << "Expression was converted to: " << tmp_expr << std::endl;
		
		if (!solver->calculate(tmp_expr, result)) {
			std::cout << "Error:can't solve the expression: " <<
				tmp_expr << std::endl << "Check the expression\n";
			
			continue;
		}
		
		std::cout << "Result: " << result << std::endl << std::endl;
	}
}

int main(int argc, char **argv) {
	std::string expression;
	std::string error_message;
	float result = 0;
	
	auto solver = std::make_shared<Solver::solver>();
	
	if (argc > 1) {
		if (std::strcmp(argv[1], "--help") == 0 ||
			std::strcmp(argv[1], "-h") == 0)
		{
			show_help();
			return 0;
		} else if ((std::strcmp(argv[1], "--solve") ||
					std::strcmp(argv[1], "-s")) && argc == 3)
		{
			solve_args_expressions(solver, argv[2]);
		}
	}
	
	bool loop_flag = true;
	while (loop_flag) {
		std::cout << "Enter the expression to solve: ";
		std::cin >> expression;
		
		expression = validate_expression(expression);
		std::cout << "Expression was converted to: " << expression << std::endl;
		
		if (!solver->calculate(expression, result)) {
			std::cout << "Error:can't solve the expression: " <<
				expression << std::endl << "Check the expression\n";
			
			continue;
		}
		
		std::cout << "Result: " << result << std::endl;
		std::cout << "Do you want to continue? (Y/n)" << std::endl;
		
		char answer = '\0';
		std::cin >> answer;
		
		if (answer == 'Y' || answer == 'y' || answer == '1') {
			continue;
		}
		
		loop_flag = false;
	}
	
	return 0;
}
