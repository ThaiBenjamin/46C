#include "../include/Bag.hpp"
#include <iostream>

/**
 * main ... test program when Bag is run as Application
 */

int main() {
    const int DEFAULT_TOKENS = 10;
    Bag example(DEFAULT_TOKENS);

    // test firstToken ... to print the first Token
    example.firstToken();
    std::cout << std::endl;

    // test allTokens ... to print all Tokens
    example.allTokens();
    std::cout << std::endl;

    // test allTokensWhile ... to print all Tokens using a while loop
    example.allTokensWhile();
    std::cout << std::endl;

    // test addTokens ... to print the sum of values of all Tokens
    std::cout << example.addTokens() << std::endl;

    // test highValueTokens ... to count the high value Tokens
    std::cout << example.highValueTokens() << std::endl;

    // test firstGreen ... to find the first green Token
    std::cout << example.firstGreen() << std::endl;

    return 0;
}