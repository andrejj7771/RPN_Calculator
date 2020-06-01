#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <memory>
#include <string>

namespace RPN {
class converter;
	typedef std::shared_ptr<converter> converter_ptr;
}

typedef std::string token;

namespace Solver {
	
	class solver {
		
		RPN::converter_ptr m_converter;
		std::string m_expression;
		
	public:
		
		solver(const std::string & expression = "");
		~solver() = default;
		
		bool calculate(float & result);
		bool calculate(const std::string & expression, float & result);
		
	private:
		
		float solve(float operand,
					const token & sign) const;
		
		float solve(float operand_1,
					float operand_2,
					const token & sign) const;
		
		float add(float a, float b) const;
		float sub(float a, float b) const;
		float mul(float a, float b) const;
		float div(float a, float b) const;
		float pow(float a, float d) const;
		
	};
	
	typedef std::shared_ptr<solver> solver_ptr;
}

#endif //SOLVER_HPP
