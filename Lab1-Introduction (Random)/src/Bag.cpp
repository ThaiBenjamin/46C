#include "../include/Bag.hpp"
#include <iostream>

/**
 * A Bag is a collection of Tokens (chips) that supports
 * functions that work by enumerating the contents.
 *
 * @author: Benjamin Thai
 */

Bag::Bag(int numTokens) : contents(numTokens) {}

void Bag::firstToken() const {
    if (!contents.empty())
        std::cout << contents[0].toString() << std::endl;
}

void Bag::allTokens() const {
    for (const auto& token : contents) {
        // TODO: print out the currently chosen Token
        std::cout << token.toString() << std::endl;
    }
}

void Bag::allTokensWhile() const {
    size_t i = 0;
    // TODO: turn this into a while loop that enumerates and
    // prints all of the tokens in the bag
    while (i < contents.size()) {
        std::cout << contents[i].toString() << std::endl;
        i+= 1;
    }
}

int Bag::addTokens() const {
    int i = 0;
    // TODO: write a loop that enumerates the entire bag
	// and sums the total of all of the Token values
    for(const auto& token : contents){
        i += token.getValue();
    }    

    return i;
}

int Bag::highValueTokens() const {
    // TODO: write a loop that enumerates the entire bag
    // and returns the number of high value Tokens
    int i = 0;
    // TODO: write a loop that enumerates the entire bag
	// and sums the total of all of the Token values
    for(const auto& token : contents){
        if(token.isHighValue()){
            i += 1;
        }
       
    }    
    return i;
}

int Bag::firstGreen() const {
    // TODO: search bag for a green Token, if found, return its index
    for(int i = 0; i < contents.size(); ++i){
        if(contents[i].getColor() == "Green"){
            return i;
        }
    }
    
    return -1;
}