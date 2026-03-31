#pragma once
#include <string>
#include <vector>

class Token {
public:
    static const int MAX_VALUE;
    Token(const std::string& color, int value);
    Token();

    std::string getColor() const;
    int getValue() const;
    void setColor(const std::string& color);
    void setValue(int value);
    bool isMax() const;
    bool isHighValue() const;
    std::string toString() const;

private:
    std::string color;
    int value;
    static const std::vector<std::string> colors;
};