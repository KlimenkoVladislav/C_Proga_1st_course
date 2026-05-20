#include "head.hpp"
#include <typeinfo>
#include <math.h>

void calculation(std::stack<float> &digits, std::stack<char> &operations){
    char operation = operations.top();
    operations.pop();

    if ((operation == 'r') or (operation == 's') or (operation == 'c')){
        float a = digits.top(); digits.pop();

        if (operation == 'r'){ digits.push(std::sqrt(a)); }
        else if (operation == 's'){ digits.push(std::sin(a)); }
        else if (operation == 'c'){ digits.push(std::cos(a)); }
    }
    else {
        float b = digits.top(); digits.pop();
        float a = digits.top(); digits.pop();

        if (operation == '+'){ digits.push(a + b); }
        else if (operation == '-'){ digits.push(a - b); }
        else if (operation == '*'){ digits.push(a * b); }
        else if (operation == '/'){ digits.push(a/b); }
        else if (operation == '^'){ digits.push(std::pow(a, b)); }
    }
}