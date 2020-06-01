#ifndef DEFINE_H
#define DEFINE_H

#include <cstdint>
#include <string>

typedef std::string token;

enum class token_t : int8_t {
    UNDEFINED = -1,
    NUMBER = 0,
    OPERATION = 1,
    BRACKET = 2
};

enum class priority_t : int8_t {
    UNDEFINED = -1,
    VERY_LOW = 0,
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
};

inline bool is_digit(const char s) {
    return s >= '0' && s <= '9';
}

inline bool is_number(const token & t) {
    for (const char s : t) {
        if (!is_digit(s)) {
            return false;
        }
    }

    return true;
}

inline bool is_operation(const char s) {
    return s == '+' || s == '-' ||
            s == '*' || s == '/' ||
            s == '^';
}

inline bool is_bracket(const char s) {
    return s == '(' || s == ')';
}

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

#endif //DEFINE_H