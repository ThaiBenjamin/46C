#include "../include/Token.hpp"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <random>

const unsigned int SEED = 46;
std::default_random_engine engine{SEED};

const int Token::MAX_VALUE = 10;
const std::vector<std::string> Token::colors = {"Green", "Blue", "Yellow", "Red"};

Token::Token(const std::string& color, int value) : color(color), value(value) {}

/**
* Creates a Token with randomly chosen color and value
* ask student to implement random implementation
*/

Token::Token() {

    // Define distributions for value and color
    static std::uniform_int_distribution<int> value_dist(0, MAX_VALUE);
    static std::uniform_int_distribution<size_t> color_dist(0, colors.size() - 1);

    // Use the engine to generate random values
    color = colors[color_dist(engine)];
    value = value_dist(engine);
}


std::string Token::getColor() const {
    return color;
}

int Token::getValue() const {
    // TODO: Have this function return the value of this Token
    return value;
}

void Token::setColor(const std::string& color) {
    // TODO: Have this function change the color of this Token
    this->color = color;
}

void Token::setValue(int value) {
    // TODO: Have this function change the value of this Token
    this->value = value;
}

bool Token::isMax() const {
    return value == MAX_VALUE;
}

bool Token::isHighValue() const {
    // TODO write this function so that it returns true if the value is greater than half the maximum value
    if(value > (MAX_VALUE/2)){
        return true;
    }
    else{
        return false;
    }
}

std::string Token::toString() const {
    // TODO: Complete this line of code so that it will also print the value of the token
	return std::string("Token's color is ") + color + " and has value " + std::to_string(value);
}