#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP

#include <vector>
#include <string>

#include "Sorter.hpp"

// Simple in-place insertion sort (ascending)
template<typename T>
class InsertionSort : public Sorter<T> {
public:
    InsertionSort() = default; // Default constructor
    void sort(std::vector<T>& data) override;
    std::string name() const override { return "InsertionSort"; }
};

#include "InsertionSort.tpp"
#endif // INSERTIONSORT_HPP
