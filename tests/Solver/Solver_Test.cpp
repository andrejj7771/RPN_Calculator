#include <Solver/Solver.hpp>

#include <cmath>
#include <cstring>

int main(int argc, char **argv) {
	if (argc < 3) {
		return 1;
	}
	
	const std::string & INPUT(argv[1]);
	
	float OUTPUT = 0;
	
	if (argv[2][0] == '-') {
		char * a =  new char [std::strlen(argv[2]) - 1];
		std::memcpy(a, (argv[2] + 1), std::strlen(argv[2] + 1));
		OUTPUT = std::stof(a) * (-1);
	} else {
		OUTPUT = std::stof(argv[2]);
	}
	
	Solver::solver solver(INPUT);
	float result = 0;
	
	if (!solver.calculate(result)) {
		return 1;
	}
	
	return fabs(OUTPUT - result) < 0.00001 ? 0 : 1;
}
