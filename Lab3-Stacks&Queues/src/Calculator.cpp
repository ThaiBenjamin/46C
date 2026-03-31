#include "Calculator.hpp"
#include <iostream>
#include <stdexcept>

// Constructor
Calculator::Calculator() : memory() {}

// Method to perform operations
int Calculator::performOperation(char op, int first, int second) {
    // TODO: implement performOperation
    switch(op) {
        case '+':
            return first + second;
        case '-':
            return first - second;
        case '*':
            return first * second;
        case '/':
            if(second == 0) {
                throw std::domain_error("Division by zero");
            }
            return first/second;  
        default:
            throw std::invalid_argument("Invalid operator");
    }
}

// Main run method
void Calculator::run() {
    std::string line;

    std::cout << "Enter a number or operator: ";
    if (!std::getline(std::cin, line)) return;

    while (!line.empty()) {
        try {
            size_t idx = 0;
            int number = std::stoi(line, &idx);
            if (idx == line.size()) {
                memory.push(number);
            } else {
                throw std::invalid_argument("not a pure number");
            }
        } catch (const std::invalid_argument&) {
            if (line == "quit") {
                break;
            } else if (line == "pop") {
                if (memory.isEmpty()) {
                    std::cout << "Error: pop requires one argument" << std::endl;
                } else {
                    std::cout << "Answer: " << memory.pop() << std::endl;
                }
            } else if (line.size() == 1 && (line[0] == '+' || line[0] == '-' || line[0] == '*' || line[0] == '/')) {
                processOperation(line);
            } else {
                std::cout << "Error: expected number or operator" << std::endl;
            }
        } catch (const std::out_of_range&) {
            std::cout << "Error: expected number or operator" << std::endl;
        }

        std::cout << std::endl;
        std::cout << "Memory contents: " << std::endl;
        std::cout << memory.toString();
        std::cout << "Enter a number or operator: ";
        if (!std::getline(std::cin, line)) return;
    }
}

// Helper method to process operations
void Calculator::processOperation(const std::string& line) {
    // TODO: implement processOperation
    char op = line[0];
    
    if(memory.isEmpty()){
        std::cout << "Error: operator requires two arguments" << std::endl;
        return;
    }

    int secondElement = memory.pop();

    if(memory.isEmpty()){
        std::cout << "Error: operator requires two arguments" << std::endl;
        memory.push(secondElement);
        return;
    }

    int firstElement = memory.pop();

    try {
        int result = performOperation(op, firstElement, secondElement);
        memory.push(result);  

        std::cout << "Answer: " << result << std::endl;
    }

    catch(const std::domain_error& e) {
        std::cout << "Error: divide by zero" << std::endl;
        memory.push(firstElement);   
        memory.push(secondElement);
    }

    catch(const std::invalid_argument& e) {
        std::cout << "Error: invalid operator" << std::endl;
        memory.push(firstElement);   
        memory.push(secondElement);
    }
}