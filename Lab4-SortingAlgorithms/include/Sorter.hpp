#pragma once

#include <vector>
#include <string>

// Abstract base class
// Defines common interface for sorting algorithms

template<typename T>
class Sorter {
public:
    virtual ~Sorter() = default;

    // Sort the data in-place
    virtual void sort(std::vector<T>& data) = 0;

    // Name of the sorter (for reporting)
    virtual std::string name() const = 0;
};
