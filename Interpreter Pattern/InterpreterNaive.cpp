#include <iostream>
#include <string>
#include <sstream>

// Naive Approach: Direct string parsing and sequential calculation from left to right
// Limitations: Hard to handle operator precedence (*, / vs +, -), parentheses, or variable context cleanly.
int evaluateNaive(const std::string& expression) {
    std::stringstream ss(expression);
    int result = 0;
    int number = 0;
    char op = '+';

    while (ss >> number) {
        if (op == '+') {
            result += number;
        } else if (op == '-') {
            result -= number;
        } else if (op == '*') {
            result *= number;
        }
        
        // Read next operator if available
        if (!(ss >> op)) {
            break;
        }
    }
    return result;
}

int main() {
    std::cout << "===========================================" << std::endl;
    std::cout << "  NAIVE SOLUTION: EXPRESSION EVALUATOR     " << std::endl;
    std::cout << "===========================================" << std::endl;

    std::string expr1 = "3 + 5 - 2";
    std::cout << "Evaluating '" << expr1 << "' -> Result: " << evaluateNaive(expr1) << std::endl;

    std::string expr2 = "10 - 4 + 6";
    std::cout << "Evaluating '" << expr2 << "' -> Result: " << evaluateNaive(expr2) << std::endl;

    return 0;
}