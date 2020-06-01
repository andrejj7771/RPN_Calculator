#include "Solver/Solver.hpp"
#include "RPN/RPN_Converter.hpp"

#include <cmath>
#include <exception>
#include <stack>

namespace Solver {

solver::solver(const std::string & expression) :
	m_converter(std::make_shared<RPN::converter>(expression)),
	m_expression(expression) {}

bool solver::calculate(float & result) {
	if (m_expression.empty()) {
		return false;
	}
	
	std::vector<token> token_list = m_converter->convert();
	std::stack<float> operand_stack;
	std::stack<token> operation_stack;
	
	for (size_t i = 0; i < token_list.size(); ++i) {
		const token & t = token_list.at(i);
		token_t type = get_token_type(t);
		
		switch (type) {
		case token_t::NUMBER: {
			float number = std::stof(t);
			if (operand_stack.empty() && !operation_stack.empty()) {
				number = solve(number, operation_stack.top());
				operation_stack.pop();
				
			}
			
			operand_stack.push(number);
			break;
		}
		case token_t::OPERATION: {
			switch (operand_stack.size()) {
			case 0: {
				operation_stack.push(t);
				break;
			}
			case 1: {
				float operand = operand_stack.top();
				operand_stack.pop();
				
				float number = solve(operand, t);
				operand_stack.push(number);
				
				if (operand_stack.size() == 1) {
					break;
				}
			}
			default: {
				float operand_1 = operand_stack.top();
				operand_stack.pop();
				
				float operand_2 = operand_stack.top();
				operand_stack.pop();
				
				float number = solve(operand_1, operand_2, t);
				operand_stack.push(number);
				break;
			}
			}
		}
		default:
			break;
		}
	}
	
	result = operand_stack.top();
	operand_stack.pop();
	
	return true;
}

bool solver::calculate(const std::string & expression, float & result) {
	if (expression.empty()) {
		return false;
	}
	
	if (m_expression != expression) {
		m_expression = expression;
		m_converter->set_expression(expression);
	}
	
	std::vector<token> token_list = m_converter->convert();
	std::stack<float> operand_stack;
	std::stack<token> operation_stack;
	
	for (size_t i = 0; i < token_list.size(); ++i) {
		const token & t = token_list.at(i);
		token_t type = get_token_type(t);
		
		switch (type) {
		case token_t::NUMBER: {
			float number = std::stof(t);
			if (operand_stack.empty() && !operation_stack.empty()) {
				number = solve(number, operation_stack.top());
				operation_stack.pop();
				
			}
			
			operand_stack.push(number);
			break;
		}
		case token_t::OPERATION: {
			switch (operand_stack.size()) {
			case 0: {
				operation_stack.push(t);
				break;
			}
			case 1: {
				float operand = operand_stack.top();
				operand_stack.pop();
				
				float number = solve(operand, t);
				operand_stack.push(number);
				
				if (operand_stack.size() == 1) {
					break;
				}
			}
			default: {
				float operand_1 = operand_stack.top();
				operand_stack.pop();
				
				float operand_2 = operand_stack.top();
				operand_stack.pop();
				
				float number = solve(operand_1, operand_2, t);
				operand_stack.push(number);
				break;
			}
			}
		}
		default:
			break;
		}
	}
	
	result = operand_stack.top();
	operand_stack.pop();
	
	return true;
}

float solver::solve(float operand,
					const token & sign) const
{
	if (sign == "-") {
		return operand * -1;
	}
	
	return operand;
}

float solver::solve(float operand_1,
					float operand_2,
					const token & sign) const
{
	if (sign == "+") {
		return add(operand_1, operand_2);
	} else if (sign == "-") {
		return sub(operand_2, operand_1);
	} else if (sign == "*") {
		return mul(operand_1, operand_2);
	} else if (sign == "/") {
		return div(operand_2, operand_1);
	} else {
		return pow(operand_2, operand_1);
	}
}

float solver::add(float a, float b) const {
	return a + b;
}

float solver::sub(float a, float b) const {
	return a - b;
}

float solver::mul(float a, float b) const {
	return a * b;
}

float solver::div(float a, float b) const {
	if (b == 0) {
		throw(std::invalid_argument("division by 0"));
	}
	
	return a / b;
}

float solver::pow(float a, float d) const {
	return std::pow(a, d);
}

}
