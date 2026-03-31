#pragma once
#include "Token.hpp"
#include <vector>

class Bag {
public:
    explicit Bag(int numTokens);

    void firstToken() const;
    void allTokens() const;
    void allTokensWhile() const;
    int addTokens() const;
    int highValueTokens() const;
    int firstGreen() const;

private:
    std::vector<Token> contents;
};