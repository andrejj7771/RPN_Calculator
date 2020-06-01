#include <Solver/Solver.hpp>

#include <cstdio>

int main(int argc, char **argv) {
	if (argc < 3) {
		return 1;
	}
	
	const std::string & INPUT(argv[1]);
	const float OUTPUT = std::stof(argv[2]);
	
	Solver::solver solver(INPUT);
	float result = 0;
	
	if (!solver.calculate(result)) {
		return 1;
	}
	
	return result == OUTPUT ? 0 : 1;
}
