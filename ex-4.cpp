#include <iostream>
#include <cctype>
#include <cstdlib>

using namespace std;

class Parser {
private:
    string expression;
    int index;

    char peek() {
        return expression[index];
    }

    char get() {
        return expression[index++];
    }

    double number() {
        double result = 0;
        while (isdigit(peek())) {
            result = result * 10 + (get() - '0');
        }
        if (peek() == '.') {
            get();
            double fraction = 1;
            while (isdigit(peek())) {
                fraction /= 10;
                result += (get() - '0') * fraction;
            }
        }
        return result;
    }

    double factor() {
        if (peek() == '(') {
            get(); // consume '('
            double result = expressionParser();
            get(); // consume ')'
            return result;
        } else {
            return number();
        }
    }

    double term() {
        double result = factor();
        while (peek() == '*' || peek() == '/') {
            if (get() == '*') result *= factor();
            else result /= factor();
        }
        return result;
    }

    double expressionParser() {
        double result = term();
        while (peek() == '+' || peek() == '-') {
            if (get() == '+') result += term();
            else result -= term();
        }
        return result;
    }

public:
    double parse(string expr) {
        expression = expr;
        index = 0;
        return expressionParser();
    }
};

int main() {
    Parser parser;
    string input;

    cout << "Enter an arithmetic expression (or type 'exit' to quit):" << endl;
    while (true) {
        cout << "> ";
        getline(cin, input);
        if (input == "exit") break;
        try {
            double result = parser.parse(input);
            cout << "Result: " << result << endl;
        } catch (...) {
            cout << "Error parsing expression!" << endl;
        }
    }
    return 0;
}
