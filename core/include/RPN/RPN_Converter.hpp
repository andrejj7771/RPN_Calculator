#ifndef RNP_CONVERTER_H
#define RNP_CONVERTER_H

#include "define.hpp"

#include <string>
#include <vector>

namespace RPN {
	
	class converter {
		
		std::string m_expression;
		std::vector<token> m_converted;
		
		bool m_need_corvert;
		
	public:
		
		converter(const std::string & expression = "");
		~converter() = default;
		
		void set_expression(const std::string & expression);
		const std::string & expression() const;
		
		std::string converted_expression();
		const std::vector<token> & get_tokenized_expression();
		
		const std::vector<token> & convert();
		
	private:
		
		std::vector<token> tokenize_expression() const;
		
	};
	
}

#endif //RNP_CONVERTER
