#include "RPN/RPN_Converter.hpp"

#include <cassert>
#include <stack>

namespace RPN {

converter::converter(const std::string & expression) :
	m_expression(expression)
{
	m_need_corvert = !m_expression.empty(); 
}

void converter::set_expression(const std::string & expression) {
	if (m_expression == expression) {
		return;
	}
	
	m_expression = expression;
	m_need_corvert = true;
}

const std::string & converter::expression() const {
	return m_expression;
}

std::string converter::converted_expression() {
	const std::vector<token> & exp = get_tokenized_expression();
	
	std::string result;
	for (const token & t : exp) {
		result += t + " ";
	}
	
	result.pop_back();
	return result;
}

const std::vector<token> & converter::get_tokenized_expression() {
	if (m_need_corvert == true) {
		return convert();
	}
	
	return m_converted;
}

const std::vector<token> & converter::convert() {
	if (m_need_corvert == false) {
		return m_converted;
	}
	
	m_converted.clear();
	std::vector<token> token_list = tokenize_expression();
	std::stack<token> exp_stack;
	
	for (size_t i = 0; i < token_list.size(); ++i) {
		const token & t = token_list.at(i);
		token_t type = get_token_type(t);
		
		switch (type)
		{
		case token_t::NUMBER: {
			m_converted.push_back(t);
			break;
		}
		case token_t::BRACKET: {
			if (t == "(") {
				exp_stack.push(t);
			} else {
				while (exp_stack.top() != "(" && !exp_stack.empty()) 
				{
					m_converted.push_back(exp_stack.top());
					exp_stack.pop();
				}
				
				exp_stack.pop();
			}
			break;
		}
		case token_t::OPERATION: {
			while(!exp_stack.empty() && get_priority(exp_stack.top()) >= get_priority(t)) {
				m_converted.push_back(exp_stack.top());
				exp_stack.pop();
			}
			
			exp_stack.push(t);
			break;
		}
		default:
			assert(type != token_t::UNDEFINED);
		}
	}
	
	while(!exp_stack.empty()) {
		m_converted.push_back(exp_stack.top());
		exp_stack.pop();
	}
	
	m_need_corvert = false;
	return m_converted;
}

std::vector<token> converter::tokenize_expression() const {
	std::vector<token> token_list;
	std::string current_number;
	
	char prev_s = '\0';
	for (auto it = m_expression.begin(); it != m_expression.end(); ++it) {
		char s = *it;
		if (s == '.') {
			if (is_digit(prev_s)) {
				current_number += s;
			} else continue;
		} else if (is_digit(s)) {
			current_number += s;
		} else {
			if (!current_number.empty()) {
				token_list.push_back(current_number);
				current_number.clear();
			}
			
			if (s != ' ') {
				token_list.push_back(std::string(&s, 1));
			}
		}
		
		prev_s = s;
	}
	
	if (!current_number.empty()) {
		token_list.push_back(current_number);
	}
	
	return token_list;
}

}
