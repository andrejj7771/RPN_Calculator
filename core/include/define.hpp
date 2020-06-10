#ifndef DEFINE_H
#define DEFINE_H

#include <cstdint>
#include <string>
#include <vector>
#include <limits>

typedef std::string token;

///
/// \brief The token_t enum - token type
/// The token is an unit of expression.
/// Tt may be an operation sign, a number, a bracket
///
enum class token_t : int8_t {
	UNDEFINED = -1,
	NUMBER = 0,
	OPERATION = 1,
	BRACKET = 2
};

///
/// \brief The priority_t enum - operation priority sign
///
enum class priority_t : int8_t {
	UNDEFINED = -1,
	VERY_LOW = 0,
	LOW = 1,
	MEDIUM = 2,
	HIGH = 3
};

///
/// \brief is_digit - check that the symbol is a digit in range [0-9]
/// \param s - symbol to check
/// \return true - symbol is digit, otherwise - false
///
inline bool is_digit(const char s) {
	return s >= '0' && s <= '9';
}

///
/// \brief is_number - check that the expression token is a number
/// \note A negative number is not valid, because the minus sign in frot of 
/// the number is a sign of an unary operation
/// \param t - expression token
/// \return true - token is a number, otherwise - false
///
inline bool is_number(const token & t) {
	try {
		std::stof(t);
	} catch(const std::exception &) {
		return false;
	}
	
	return true;
}

///
/// \brief is_operation - check that the symbol is an operation sign
/// \param s - the symbol to check
/// \return true - the symbol is an operation sign, otherwise - false
///
inline bool is_operation(const char s) {
	return s == '+' || s == '-' ||
			s == '*' || s == '/' ||
			s == '^';
}

///
/// \brief is_bracket - check that the symbol is a bracket ('(' or ')')
/// \param s - the symbol to check
/// \return true - the symbol is a bracket, otherwise - false
///
inline bool is_bracket(const char s) {
	return s == '(' || s == ')';
}

///
/// \brief get_token_type - get type of an expression token
/// \param t - expression token
/// \return OPERATION - token is an operation (+,-, etc.)
///			NUMBER - token is an operand
///			BRACKET - token is a bracket
///			UNDEFINED - an empty token or wrong value
///
inline token_t get_token_type(const token & t) {
	const size_t token_size = t.size();
	if (token_size == 0) {
		return token_t::UNDEFINED;
	} else if (token_size == 1) {
		const char _t = t[0];
		
		if (is_operation(_t)) {
			return token_t::OPERATION;
		} else if (is_digit(_t)) {
			return token_t::NUMBER;
		} else if (is_bracket(_t)) {
			return token_t::BRACKET;
		} else {
			return token_t::UNDEFINED;
		}
	} else {
		return is_number(t) ? token_t::NUMBER : token_t::UNDEFINED;
	}
	
	return token_t::UNDEFINED;
}

///
/// \brief get_priority - get a priority of the operation sign
/// \param t - expression token
/// \return UNDEFIND - undefined token, other value depends
///			on the operation sign
///
inline priority_t get_priority(const token & t) {
	if (t.size() > 1) {
		return priority_t::UNDEFINED;
	}
	
	const char _t = t[0];
	switch (_t)
	{
	case '(':
	case ')':
		return priority_t::VERY_LOW;
	case '+':
	case '-':
		return priority_t::LOW;
	case '*':
	case '/':
		return priority_t::MEDIUM;
	case '^':
		return priority_t::HIGH;
	default:
		return priority_t::UNDEFINED;
	}
}

///
/// \brief is_valid_expression - check the expression is valid
/// \param expression - math expression
/// \return true - expression is valid, otherwise - false
///
inline std::string validate_expression(const std::string & expr) {
	std::string copy = expr;
	std::vector<size_t> open_brackets;
	
	//remove excess operations before an expression
	auto it = copy.begin();
	bool has_minus = false;
	while(is_operation(*it)) {
		if (*it == '-' && !has_minus) {
			has_minus = true;
			++it;
			continue;
		}
		
		copy.erase(it);
	}
	
	char last_symbol = '\0';
	int dot_counter = 0;
	for (size_t i = 0; i < copy.size(); ++i) {
		bool set_last = true;
		char & current_symbol = copy.at(i);
		
		switch (current_symbol) {
			case '(': {
				dot_counter = 0;
				if (is_digit(last_symbol)) {
					copy.insert(i, 1, '*');
					++i;
				}
				
				open_brackets.push_back(i);
				break;
			}
			case ')': {
				dot_counter = 0;
				if (open_brackets.empty()) {
					copy.erase(i, 1);
					--i;
				} else if (i != copy.size() - 1 &&
						   (is_digit(copy.at(i + 1)) || copy.at(i + 1) == '('))
				{
					copy.insert(i + 1, 1, '*');
					open_brackets.pop_back();
					++i;
				} else {
					if (last_symbol == '(') {
						// there are an empty brackets
						open_brackets.pop_back();
						copy.erase(i - 1, 2);
						i -= 2;
					} else {
						// there is a pair of brackets
						open_brackets.pop_back();
					}
				}
				
				break;
			}
			case ',': {
				current_symbol = '.';
			}
			case '.': {
				if (!is_digit(last_symbol)) {
					copy.insert(i, 1, '0');
					++i;
				}
				
				++dot_counter;
				if (dot_counter > 1 ||
						(i != copy.size() - 1 && !is_digit(copy.at(i + 1))))
				{
					copy.erase(i, 1);
					--dot_counter;
					--i;
				}
				break;
			}
			default: {
				if (is_digit(current_symbol)) {
					break;
				} else if (is_operation(current_symbol)) {
					dot_counter = 0;
					break;
				}
				
				copy.erase(i, 1);
				--i;
				
				set_last = false;
				break;
			}
		}
		
		if (i != std::numeric_limits<size_t>().max() && set_last) {
			last_symbol = copy.at(i);
		}
	}
	
	//remove unlosed brackets
	while(!open_brackets.empty()) {
		copy.erase(*(open_brackets.end() - 1), 1);
		open_brackets.pop_back();
	}
	
	//remove excess operations after an expression
	while(is_operation(*(copy.end() - 1))) {
		copy.erase(copy.end() - 1);
	}
	
	return copy;
}

#endif //DEFINE_H
